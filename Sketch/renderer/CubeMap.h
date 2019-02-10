#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <renderer/Renderable.h>
#include <renderer/Texture.h>


enum CubeMapFace : GLint
{
	TEXTURE_CUBE_MAP_RIGHT = GL_TEXTURE_CUBE_MAP_POSITIVE_X,//
	TEXTURE_CUBE_MAP_LEFT,		//
	TEXTURE_CUBE_MAP_TOP,		//
	TEXTURE_CUBE_MAP_BOTTOM,		//
	TEXTURE_CUBE_MAP_POSITIVE,	//
	TEXTURE_CUBE_MAP_NEGATIVE,	//
};

//overrides load to enable 
class CubeMap : public Texture
{
public:
	CubeMap(TextureWrapFlag wrapS = TEXTURE_WRAP_REPEAT,
		TextureWrapFlag wrapT = TEXTURE_WRAP_REPEAT,
		TextureWrapFlag wrapR = TEXTURE_WRAP_REPEAT,
		TextureFilterFlag minimize = TEXTURE_FILTER_LINEAR,
		TextureFilterFlag magnify = TEXTURE_FILTER_LINEAR)
		: Texture(TEXTURE_CUBE_MAP, wrapS, wrapT, wrapR, minimize, magnify) {}

//expecting 6 faces char* data[6]
	template <typename T>
	void load( T ** data, int width, int height, TextureFormat format, int lod = 0);
	
};




template <typename T>
void CubeMap::load( T ** data, int width, int height, TextureFormat format, int lod)
{
	DebugAssert(data);
	DebugAssert(m_texture != -1);
	glBindTexture(m_type, m_texture);
	DebugAssert(m_texture != -1);
	if (m_type == TEXTURE_CUBE_MAP)
	{
		for (int i = 0; i < 6; i++)
		{
			//GL_TEXTURE_CUBE_MAP_POSITIVE_X + i which face right, left, top bottom, forward back
			if (std::is_same<T, unsigned int>::value)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, format, width, height, 0, format, GL_UNSIGNED_INT, (void*)data);
			}
			else if (std::is_same<T, unsigned char>::value)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (void*)data);
			}
			else if (std::is_same<T, float>::value)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, format, width, height, 0, format, GL_FLOAT, (void*)data);
			}
			else
			{
				Debug("Texture:: Type [%s] not supported", typeid(T).name());
				DebugAssert(1);
			}
			if (m_mipmap)
				glGenerateMipmap(m_type);
		}
	}
	else
	{
		DebugAssert("Texture::Must be of type Cube map ");
	}
	glBindTexture(m_type, 0);
}

#endif