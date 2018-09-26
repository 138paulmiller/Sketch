#ifndef TEXTURE_H
#define TEXTURE_H

//#include <GL/glew.h>

//CREATE CUBMAP Texture
#include <renderer/Shader.h>
//CREATE RNDER TARGET BASE CLASS TO BIND TO TEXTURE???
//(x,y,z)=(s,t,r)
//how texture data along s,t,r axes is mapped 

//Texture Sampling Paramters

//edge value sampling (how to wrap image)
enum TextureWrapFlag : GLuint
{

	//modulus effect if img dimen < range
	TEXTURE_REPEAT				= GL_REPEAT,
	//mirror along the axis, behaves like repeat, but mirrors next image raster
	TEXTURE_MIRRORED			= GL_MIRRORED_REPEAT, 
	//clamp last pxel to fill space between pixels and range
	TEXTURE_CLAMP_EDGE			= GL_CLAMP_TO_EDGE,
	//clamp to border to fill space between pixels and range
	TEXTURE_CLAMP_BORDER		= GL_CLAMP_TO_BORDER,
};

//Texture filtering flags; controls minimize and maximize functions
//how should texture be sampled on minification and magnification
enum TextureFilterFlag : GLuint
{
	//nearest pixel value
	TEXTURE_FILTER_NEAREST			= GL_NEAREST,
	TEXTURE_FILTER_LINEAR			= GL_LINEAR,
	//linear blend of neighboring pixels 
	//MipMapped flags, same as above, except mipmapped..
	TEXTURE_MIPMAP_FILTER_NEAREST  = GL_LINEAR_MIPMAP_NEAREST,
	TEXTURE_MIPMAP_FILTER_LINEAR   = GL_LINEAR_MIPMAP_LINEAR,  
};

enum TextureType : GLint
{
	TEXTURE_TYPE_NONE = -1,
	TEXTURE_1D = GL_TEXTURE_1D,
	TEXTURE_2D = GL_TEXTURE_2D,
	TEXTURE_3D = GL_TEXTURE_3D,
};


enum TextureFormat : GLint
{
	TEXTURE_FORMAT_NONE = -1,
	TEXTURE_RGB		= GL_RGB,
	TEXTURE_RGBA	= GL_RGBA,
	TEXTURE_SRGB	= GL_SRGB,
};

//Does not own data??? Abstract make image, render target etc that manage data
// create add border take in color vec3,
//STR = xyz
//Create Texture Array?
class Texture
{
public:
	Texture(
			TextureType type			= TEXTURE_2D,
			TextureWrapFlag wrapS		= TEXTURE_REPEAT,	
			TextureWrapFlag wrapT		= TEXTURE_REPEAT,
			TextureWrapFlag wrapR		= TEXTURE_REPEAT,
			TextureFilterFlag minimize	= TEXTURE_FILTER_LINEAR,
			TextureFilterFlag magnify	= TEXTURE_FILTER_LINEAR);
	virtual ~Texture();

	void load(const std::string filename, TextureFormat format= TEXTURE_RGB);
	
	void load(unsigned char * data, int width, int height,
		TextureFormat format=TEXTURE_RGB);

	void  load(float * data, int width, int height,
		TextureFormat format = TEXTURE_RGB);


	void bind(const Shader * shader, int index=0) const;
	void unbind() const;


private:
	GLuint				m_texture;
	bool				m_mipmap;
	TextureType			m_type;
	
};


#endif //TEXTURE_H
