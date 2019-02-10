#include <renderer/Texture.h>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

Texture::Texture(	
			TextureType		  type,
			TextureWrapFlag   wrapS,
			TextureWrapFlag   wrapT,
			TextureWrapFlag   wrapR,
			TextureFilterFlag minFilter,
			TextureFilterFlag magFilter)
{
	m_texture = -1;
	glGenTextures(1, &m_texture);
	m_type = type;
	glBindTexture(type, m_texture);

	glTexParameteri(type, GL_TEXTURE_WRAP_S,		wrapS);
	glTexParameteri(type, GL_TEXTURE_WRAP_T,		wrapT);
	glTexParameteri(type, GL_TEXTURE_WRAP_R,		wrapR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER,	minFilter);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER,	magFilter);
	m_mipmap =
		(minFilter == TEXTURE_FILTER_MIPMAP_NEAREST) ||
		(minFilter == TEXTURE_FILTER_MIPMAP_LINEAR) ||
		(magFilter == TEXTURE_FILTER_MIPMAP_NEAREST) ||
		(magFilter == TEXTURE_FILTER_MIPMAP_LINEAR)
	;

	glBindTexture(type, 0);


}


Texture::~Texture()
{
}


void Texture::read(const std::string &  filename, unsigned char ** data, int &width, int &height, TextureFormat &format)
{
	int comp; //number of channels
	*data = stbi_load(filename.c_str(), &width, &height, &comp, 0);
	switch (comp)
	{
	case 3: format = TEXTURE_RGB; break;
	case 4: format = TEXTURE_RGBA; break;
	default: break;
	}
	Debug("%d", comp);
}

void Texture::bind(const Shader * shader, int index) const
{
	DebugAssert(m_type != TEXTURE_NONE);
	DebugAssert(index >= 0 && index < SAMPLER_COUNT);

	glActiveTexture(GL_TEXTURE0+index); 
	glBindTexture(m_type, m_texture);
	//set texure sampler in shader 
	shader->setUniformInt(Shader::Uniform_Sampler[index],  index);
}

void Texture::unbind() const
{
	DebugAssert(m_type != TEXTURE_NONE);
	glBindTexture(m_type, 0);
}