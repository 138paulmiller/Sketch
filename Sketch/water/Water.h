
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
	Water(int width, int height, float scale = 1, float tessalation = 0.5);
	~Water() { }


	//must be defined for flat shaders
	void onBind() override;
	void onUnbind() override;
	void onPreRender() override;
	void onRender() override;

	inline void setTime(float time) { Shader::current()->setUniformFloat("time", time); }

private:
	enum { TEXTURE_INDEX_NOISE = 0, TEXTURE_INDEX_SKYBOX, TEXTURE_COUNT };


	struct NoiseData : Texture
	{
		Array<Color3>	_color3Data;	//vec3f of color data that represents noise data
		NoiseData() : Texture(
			TEXTURE_2D, TEXTURE_CLAMP_EDGE, TEXTURE_CLAMP_EDGE) {}
	};
	struct SkyboxData : Texture
	{
		Array<Color4u>	_image;	//vec3f of color data that represents noise data
		SkyboxData() : Texture(TEXTURE_3D, TEXTURE_CLAMP_EDGE, TEXTURE_CLAMP_EDGE) {}
	};

	void loadSkyBox(const std::string &filename);
	void generateNoiseTexture(int width, int height, float tessalation, const std::function<Color3(float u, float v)> & perVertex);

	Shader		_shader;
	NoiseData	_noise;
	SkyboxData  _skybox;
	float _scale;
};
