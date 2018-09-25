
#include <chrono>
#include <functional>
#include <renderer/Window.h>
#include <renderer/Camera.h>
#include <renderer/RenderArray.h>
#include <renderer/Texture.h>
#include <noise/perlin.h>

//http://www.cs.utah.edu/~michael/water/waterPGColor.pdf//height 
//https://www.cg.tuwien.ac.at/courses/Seminar/WS2007/arbeit_fleck.pdf


//Move to water folder
class Water : public RenderArray<Texture2dVertex, ShaderType_Custom>
{
	using Parent = RenderArray<Texture2dVertex, ShaderType_Custom>;
public:
	Water(int width, int height, float scale =1, float tessalation = 0.5);
	~Water() { }

	struct NoiseData
	{
		Texture			_texture;		//RGB texture of 3 noise coefficients
		Array<Color3>	_color3Data;	//vec3f of color data that represents noise data
		NoiseData() : _texture(
			TEXTURE_2D
			, TEXTURE_CLAMP_EDGE, TEXTURE_CLAMP_EDGE
		) {}

	};
	enum NoiseIndex : unsigned int
	{
		NOISE_0 = 0,
		NOISE_1,
		NOISE_2,
		NOISE_3,
		NOISE_COUNT
	};
	//must be defined for flat shaders
	void onBind() override;
	void onUnbind() override;
	void onPreRender() override;
	void onRender() override;

	inline void setTime(float time) { Shader::current()->setUniformFloat("time", time); }

private:
	void generateNoiseTexture(NoiseIndex index, int width, int height, float tessalation, const std::function<Color3(float u, float v)> & perVertex);

	Shader		_shader;
	NoiseData	_noise[NOISE_COUNT];

	float _scale;
};
