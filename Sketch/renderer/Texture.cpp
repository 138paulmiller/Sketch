#include <renderer/Texture.h>
#include <stb_image.h>

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
		(minFilter == TEXTURE_MIPMAP_FILTER_NEAREST) ||
		(minFilter == TEXTURE_MIPMAP_FILTER_LINEAR) ||
		(magFilter == TEXTURE_MIPMAP_FILTER_NEAREST) ||
		(magFilter == TEXTURE_MIPMAP_FILTER_LINEAR)
	;

	glBindTexture(type, 0);


}


Texture::~Texture()
{
}
void Texture::load(const std::string filename, TextureFormat format)
{
	//int width, height;
	//int comp;
	//unsigned char* image = stbi_load(filename.c_str(), &width, &height, &comp, STBI_rgb_alpha);

	//if (!image)
	//	Error("Failed to load texture %s", filename.c_str());

	//load(image, width, height, format);
	//stbi_image_free(image);
}

void Texture::load(unsigned char * data, int width, int height, TextureFormat format)
{
	DebugAssert(data);
	DebugAssert(m_texture != -1);
	glBindTexture(m_type, m_texture);

	glTexImage2D(m_type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (void*)data);
	if (m_mipmap)
		glGenerateMipmap(m_type);
	
	glBindTexture(m_type, 0);
}

void Texture::load(float * data, int width, int height, TextureFormat format)
{
	DebugAssert(data);
	DebugAssert(m_texture != -1);
	glBindTexture(m_type, m_texture);
	DebugAssert(m_texture != -1);
	glTexImage2D(m_type, 0, format, width, height, 0, format, GL_FLOAT, (void*)data);
	
	if (m_mipmap)
		glGenerateMipmap(m_type);

	glBindTexture(m_type, 0);
}


void Texture::bind(const Shader * shader, int index) const
{
	DebugAssert(m_type != TEXTURE_TYPE_NONE);
	glBindTexture(m_type, m_texture);
	//set texure sampler in shader 
	DebugAssert(index >= 0 && index < SAMPLER_COUNT);
	shader->setUniformInt(Shader::Uniform_Sampler[index], index);
}

void Texture::unbind() const
{
	DebugAssert(m_type != TEXTURE_TYPE_NONE);
	glBindTexture(m_type, 0);
}