#include <water/Water.h>


//https://developer.nvidia.com/gpugems/GPUGems/gpugems_ch01.html
//Grid
///texture width/height
Water::Water(int width, int height, float scale,float tessalation)
{
	_scale = scale;
	Subclass::setDrawMode(GL_TRIANGLE_STRIP);
	_shader.load("water/water");

	float incW = tessalation * width;
	float incH = tessalation * height;
	bool notfloor = false;
	int a, b, c, d;
	int w = 0;
	int h = 0;
	float u = 0, v = 0;
	for (float y = 0; y <= height; y += incH)
	{
		u = 0;
		v += tessalation;
		h++;
		for (float x = 0; x <= width; x += incW)
		{
			if (y == 0)w++;
			_vertices.push_back(Texture2dVertex({ x,0, y }, {0,1,0}, { u, v }));
			u += tessalation;
		}
	}
	for (int y = 1; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			a = (y-1)*w + x;
			b = (y)*w + x;
			
			_indices.push_back(a);
			_indices.push_back(b);
		}

	Subclass::load();

	
	loadSkyBox("../Images/Skybox.png");

}

void Water::loadSkyBox( const std::string &filename)
{
	int width, height;
	TextureFormat format;

	//for each file
	_skybox.read(filename, &(_skybox.imageData), width, height, format);
	//load all 6

	_skybox.load(_skybox.imageData, width, height, format,0);

}

void Water::onBind()
{
	Shader::push(&_shader);
	_skybox.bind(&_shader, TEXTURE_INDEX_SKYBOX);

	Shader::current()->setUniformFloat("scale", _scale);
}
void Water::onUnbind()
{
	_skybox.unbind();
	Shader::pop();

}

void Water::onPreRender()
{
}
void Water::onRender()
{	}

