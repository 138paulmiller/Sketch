#ifndef TEXTURE_H
#define TEXTURE_H

//#include <GL/glew.h>

//CREATE CUBMAP Texture
#include <renderer/Shader.h>
#include <typeinfo>
#include <type_traits>

//https://docs.microsoft.com/en-us/windows/desktop/direct3d11/overviews-direct3d-11-resources-textures-intro
//CREATE RNDER TARGET BASE CLASS TO BIND TO TEXTURE???
//(x,y,z)=(s,t,r)
//how texture data along s,t,r axes is mapped 

//Texture Sampling Paramters

enum TextureType : GLint
{
	TEXTURE_NONE = -1,
	TEXTURE_1D = GL_TEXTURE_1D,
	TEXTURE_2D = GL_TEXTURE_2D,
	TEXTURE_3D = GL_TEXTURE_3D,
	TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
};



enum TextureFormat : GLint
{
	TEXTURE_FORMAT_NONE = -1,
	TEXTURE_RGB = GL_RGB,
	TEXTURE_RGBA = GL_RGBA,
	TEXTURE_SRGB = GL_SRGB,
};

//edge value sampling (how to wrap image)
enum TextureWrapFlag : GLuint
{

	//modulus effect if img dimen < range
	TEXTURE_WRAP_REPEAT				= GL_REPEAT,
	//mirror along the axis, behaves like repeat, but mirrors next image raster
	TEXTURE_WRAP_MIRRORED			= GL_MIRRORED_REPEAT, 
	//clamp last pxel to fill space between pixels and range
	TEXTURE_WRAP_CLAMP_EDGE			= GL_CLAMP_TO_EDGE,
	//clamp to border to fill space between pixels and range
	TEXTURE_WRAP_CLAMP_BORDER		= GL_CLAMP_TO_BORDER,
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
	TEXTURE_FILTER_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
	TEXTURE_FILTER_MIPMAP_LINEAR   = GL_LINEAR_MIPMAP_LINEAR,
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
			TextureWrapFlag wrapS		= TEXTURE_WRAP_REPEAT,	
			TextureWrapFlag wrapT		= TEXTURE_WRAP_REPEAT,
			TextureWrapFlag wrapR		= TEXTURE_WRAP_REPEAT,
			TextureFilterFlag minimize	= TEXTURE_FILTER_LINEAR,
			TextureFilterFlag magnify	= TEXTURE_FILTER_LINEAR);
	virtual ~Texture();

	//virtual void load	(const std::string filename, TextureFormat format= TEXTURE_RGB);	
	virtual void bind(const Shader * shader, int index=0) const;
	virtual void unbind() const;

	//format is both internal and image data format
	//read file to get data
	void read(const std::string &  filename, unsigned char ** data, int &width, int &height, TextureFormat  &format);
	template <typename T>
	void load( T * data, int width, int height, TextureFormat format, int lod=0);


	//void load(T * data, int width, int height, int lod = 0,  TextureFormat format = TEXTURE_RGB);


protected:
	GLuint				m_texture;
	bool				m_mipmap;
	TextureType			m_type;
	
};

template <typename T>
void Texture::load( T * data, int width, int height, TextureFormat format, int lod)
{
	DebugAssert(data);
	DebugAssert(m_texture != -1);
	glBindTexture(m_type, m_texture);
	DebugAssert(m_texture != -1);
	if (m_type != TEXTURE_CUBE_MAP)
	{
		if (std::is_same<T, unsigned int>::value)
		{
			glTexImage2D(m_type, 0, format, width, height, 0, format, GL_UNSIGNED_INT, (void*)data);
		}
		else if (std::is_same<T, unsigned char>::value)
		{
			glTexImage2D(m_type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (void*)data);
		}
		else if (std::is_same<T, float>::value)
		{
			glTexImage2D(m_type, 0, format, width, height, 0, format, GL_FLOAT, (void*)data);
		}
		else
		{
			Debug("Texture:: Type [%s] not supported", typeid(T).name());
			DebugAssert(1);
		}
		if (m_mipmap)
			glGenerateMipmap(m_type);
	}
	else
	{
		Debug("Texture::Cube map must be loaded using loadCubeMap");
		DebugAssert(1);

	}
	glBindTexture(m_type, 0);
}


#endif //TEXTURE_H
