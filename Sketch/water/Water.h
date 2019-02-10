
#include <chrono>
#include <functional>
#include <renderer/Window.h>
#include <renderer/Camera.h>
#include <renderer/Mesh.h>
#include <renderer/CubeMap.h>
#include <noise/perlin.h>

//http://www.cs.utah.edu/~michael/water/waterPGColor.pdf//height 
//https://www.cg.tuwien.ac.at/courses/Seminar/WS2007/arbeit_fleck.pdf

//move into sperate file
class Skybox : public Texture
{
public:
	Skybox() { imageData =0 ; }
	~Skybox() { delete imageData; }
	unsigned char * imageData;	//vec3f of color data that represents noise data
};
/*
class Skybox : public CubeMap
{
public:
	Skybox() { imageData = new unsigned char*[6]; }
	~Skybox() { delete imageData; }
	unsigned char ** imageData;	//vec3f of color data that represents noise data
};
*/

//Move to water folder
class Water : public Mesh<Texture2dVertex, ShaderType_Custom>
{
	using Subclass = Mesh<Texture2dVertex, ShaderType_Custom>;
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
	enum { TEXTURE_INDEX_SKYBOX = 0 , TEXTURE_COUNT };


	void loadSkyBox(const std::string &filename);

	Shader		_shader;
	Skybox  _skybox;
	float _scale;
};
