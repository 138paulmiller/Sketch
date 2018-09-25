#include <renderer/Vertex.h>

void PointVertex::EnableVertexAttrib(const Shader * shader)
{

	const int & posId = shader->getAttribLocation(Shader::Attrib_Position);
	glVertexAttribPointer(posId,		3, GL_FLOAT, GL_FALSE, sizeof(PointVertex), (GLvoid*)(0));
	glEnableVertexAttribArray(posId);
}

void NormalVertex::EnableVertexAttrib(const Shader * shader)
{

	const int & posId = shader->getAttribLocation(Shader::Attrib_Position);
	const int & normalId = shader->getAttribLocation(Shader::Attrib_Normal);

	const int compSize = sizeof(GL_FLOAT);
	const int stride = sizeof(NormalVertex);

	glVertexAttribPointer(posId,	3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(0));
	glVertexAttribPointer(normalId, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(compSize * 3));
	glEnableVertexAttribArray(posId);
	glEnableVertexAttribArray(normalId);
}


void ColorVertex::EnableVertexAttrib(const Shader * shader)
{
	const int & posId		= shader->getAttribLocation(Shader::Attrib_Position);
	const int & normalId	= shader->getAttribLocation(Shader::Attrib_Normal);
	const int & colorId		= shader->getAttribLocation(Shader::Attrib_Color);

	const int compSize =  sizeof(GL_FLOAT);
	const int stride = sizeof(ColorVertex);

	glVertexAttribPointer(posId,	3,		GL_FLOAT, GL_FALSE, stride, (GLvoid*)( 0));
	glVertexAttribPointer(normalId,	3,		GL_FLOAT, GL_FALSE, stride, (GLvoid*)(compSize * 3 ));
	glVertexAttribPointer(colorId,	4,		GL_FLOAT, GL_FALSE, stride, (GLvoid*)(compSize * 6 ));

	glEnableVertexAttribArray(posId);
	glEnableVertexAttribArray(normalId);
	glEnableVertexAttribArray(colorId);
}

void Texture2dVertex::EnableVertexAttrib(const Shader * shader)
{
	const int & posId		= shader->getAttribLocation(Shader::Attrib_Position);
	const int & normalId	= shader->getAttribLocation(Shader::Attrib_Normal);
	const int & uvId		= shader->getAttribLocation(Shader::Attrib_UV);

	const int compSize = sizeof(GL_FLOAT);
	const int stride = sizeof(Texture2dVertex);
	glVertexAttribPointer(posId,	3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(0));
	glVertexAttribPointer(normalId, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(compSize * 3));
	glVertexAttribPointer(uvId,		2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(compSize * 6));

	glEnableVertexAttribArray(posId);
	glEnableVertexAttribArray(normalId);
	glEnableVertexAttribArray(uvId);
}