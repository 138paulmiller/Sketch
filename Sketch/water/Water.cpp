#include <water/Water.h>


//https://developer.nvidia.com/gpugems/GPUGems/gpugems_ch01.html
//Grid
///texture width/height
Water::Water(int width, int height, float scale,float tessalation)
{
	_scale = scale;
	Parent::setDrawMode(GL_TRIANGLE_STRIP);
	Parent::setDrawMode(GL_TRIANGLES);
	//Parent::setWireframe(true);
	_shader.load("water/water");
	//init verts/indices
	float halfWidthN = 0.5 ;
	float halfHeightN = 0.5;
	float x, y;
	int j = 0;
	auto addVertex = [&](float x, float y, float u, float v)
	{
		x *= width;
		y *= height;
		_vertices.push_back(Texture2dVertex({ x,0,y }, { 0,1,0 }, { u,v }));
		_indices.push_back(_vertices.size() - 1);
	};
	for (float v = 0; v < 1; v += tessalation)
	{
		y = v - halfHeightN;

	//weave left to right through grid (change direction for each row)

		for (float u = 0; u < 1; u += tessalation)
		{
			x = u - halfWidthN;
			addVertex(x, y, u, v);
			addVertex(x, y + tessalation, u, v + tessalation);
			addVertex(x + tessalation, y , u + tessalation, v );



			addVertex(x, y + tessalation, u, v + tessalation);
			addVertex(x + tessalation, y + tessalation, u + tessalation, v + tessalation);
			addVertex(x + tessalation, y, u + tessalation, v);

		}
	}


	PerlinNoise	perlinNoise(9);

	auto lambda0 = [&perlinNoise, scale](float u, float v)
	{
		const float c1 = 64 , c2 = 128, c3 = 2048;
		Color3 color =
		{
			perlinNoise.noise(u * c1,		v * c1,		1),
			perlinNoise.noise(u * c2,		v * c2,		1),
			perlinNoise.noise(u * c3,		v * c3,		1),
		};
		return color;
	};

	generateNoiseTexture(width, height, tessalation, lambda0);

	loadSkyBox("../Images/Skybox.png");

}

void Water::loadSkyBox( const std::string &filename)
{
	_skybox.load(filename, TEXTURE_RGBA);
	
}

void Water::generateNoiseTexture(int width, int height, float tessalation, const std::function<Color3(float u, float v)> & perVertex)
{
	
	float u, v;
	for (int j = 0; j < height; j++)
	{

		v = (float)j / (float)height;
		for (int i = 0; i < width; i++)
		{
			u = (float)i / (float)width;
			_noise._color3Data.push_back(perVertex(u, v));
		}
	}

	float * data = &(_noise._color3Data[0][0]);
	_noise.load(data, width, height, TEXTURE_RGB);
	Parent::load();
}

void Water::onBind()
{
	Shader::push(&_shader);
	_noise.bind(&_shader, TEXTURE_INDEX_NOISE);
	_skybox.bind(&_shader, TEXTURE_INDEX_SKYBOX);

	Shader::current()->setUniformFloat("scale", _scale);
	//Parent::setWireframe(true);
}
void Water::onUnbind()
{
	_skybox.unbind();
	_noise.unbind();
	Shader::pop();

}

void Water::onPreRender()
{
}
void Water::onRender()
{	}

