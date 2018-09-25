#include "image.h"

Image::Image(int width, int height){
	_pixels=0;
	resize(width,height);
}


Image::~Image(){
	delete []_pixels;
}


void Image::resize(int width, int height){
	assert(width > 0 && height > 0);
	delete []_pixels;
	_width = width;
	_height = height;
	_pixels = new Color[_width*_height];
}




void Image::exportPPM(std::string filename, const Image & img){
	
    std::ofstream ofs;
    ofs.open(filename, std::ios::out | std::ios::binary);
    ofs << "P6"				<< "\n"
        << img.width()		<< "  " << img.height()	<< "\n"
        << RGB_DEPTH		<< "\n";
   
	int i, j;
	//FILE *fp;
	//fopen_s(&fp, "first.ppm", "wb"); /* b - binary mode */
	//fprintf(fp, "P6\n%d %d\n255\n", img.width(), img.height());
	char bytes[3];
	for (j = 0; j < img.height(); ++j)
	
		for (i = 0; i < img.width(); ++i)
		{	
			Color::makeBytes(img.pixel(i, j), bytes);
			ofs.write(&bytes[0], 3);
			//ofs << bytes;
			//fwrite(bytes, 1, 3, fp);
		}
	//fclose(fp);
	ofs.close();

}
