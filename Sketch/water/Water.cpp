#include <water/Water.h>



//Grid
Water::Water(int width, int height, float tessalation)
{
	Parent::setDrawMode(GL_TRIANGLE_STRIP);
	//Parent::setWireframe(true);
	_shader.load("water/water");

	PerlinNoise	perlinNoise(9);

	auto lambda0 = [&perlinNoise](float u, float v)
	{
		const float c1 = 1, c2 = 2;
		Color3 color =
		{
			perlinNoise.noise(u *c1,		v * c1,		1),
			perlinNoise.noise(u* c2,		v*c2,		1),
			0,//perlinNoise.noise(u * c1 ,	v * c2,	1),
		};
		return color;
	};
	//init verts/indices
	float halfWidthN = 0.5;
	float halfHeightN = 0.5;
	float x, y;
	int j = 0;

	auto addVertex = [&](float x, float y, float u, float v)
	{
		_vertices.push_back(Texture2dVertex({ x,0,y }, { 0,1,0 }, { u,v }));
		_indices.push_back(_vertices.size() - 1);
	};
	for (float v = 0; v < 1; v += tessalation)
	{
		y = v - halfHeightN;

	//weave left to right through grid (change direction for each row)
		if ((j++) % 2)
		{
			for (float u = 1; u >= 0; u -= tessalation)
			{
				x = u - halfWidthN;
				addVertex(x, y, u, v);
				addVertex(x, y + tessalation, u, v + tessalation);
			}
		}
		else
		{
			for (float u = 0; u <= 1; u += tessalation)
			{
				x = u - halfWidthN;
				addVertex(x, y, u, v);
				addVertex(x, y + tessalation, u, v + tessalation);
			}
		}
	}


	generateNoiseTexture(NOISE_0, width, height, tessalation, lambda0);


}


void Water::generateNoiseTexture(NoiseIndex index, int width, int height, float tessalation, const std::function<Color3(float u, float v)> & perVertex)
{
	DebugAssert(index < NOISE_COUNT);
	NoiseData * noise3d = &_noise[index];

	float u, v;
	for (int j = 0; j < height; j++)
	{

		v = (float)j / (float)height;
		for (int i = 0; i < width; i++)
		{
			u = (float)i / (float)width;
			noise3d->_color3Data.push_back(perVertex(u, v));
		}
	}


	float * data = &(noise3d->_color3Data[0][0]);
	noise3d->_texture.load(data, width, height, TEXTURE_RGB);
	noise3d = 0;
	Parent::load();
}

void Water::onBind()
{
	Shader::push(&_shader);
	_noise[0]._texture.bind(&_shader);
	//Parent::setWireframe(true);
}
void Water::onUnbind()
{
	_noise[0]._texture.unbind();
	Shader::pop();

}

void Water::onPreRender()
{	}
void Water::onRender()
{	}

