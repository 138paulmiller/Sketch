#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <typeinfo>
#include <stdexcept>
#include <string>
#include "color.h"
//RBG expected
class Image{
public:
	Image(int width, int height);
	~Image();
	void resize(int width, int height);
	inline Color * Image::pixels() const {
		return _pixels;
	}
	inline Color & Image::pixel(int x, int y) const {
		int i = y*_height + x;
		assert(i>=0 && i < _height*_width);
		return _pixels[i];
	}

	inline int width() const { return _width; }
	inline int height() const { return _height; }
	
	inline const char * makeBytes(int numComponents = 3) const {
		int size = _width*_height*(numComponents);
		char * bytes = new char[size];
		int i =0;
		Color c = 0;
		for (int x = _width-1;		x>0;	x--)
			for(int y = _height-1;	y>0;	y--)
			{
				i = y*_height + x;
		
				bytes[i++] = _pixels[i][0];
				bytes[i++] = _pixels[i][1];
				bytes[i++] = _pixels[i][2];
			}
		return bytes;
	}
	static void exportPPM(std::string filename, const Image& img);
private:
	Color * _pixels;
	int _width, _height;
};
#endif