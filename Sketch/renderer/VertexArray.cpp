
#include	<renderer/VertexArray.h>
VertexArray::VertexArray()
{
	//create 1 VAO
	glGenVertexArrays(1, &m_vertexArray);
	//create the buffers
	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_elementBuffer);
}



VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_elementBuffer);

}

//bind to use
void VertexArray::render(GLuint mode) const
{

	//bind the VAO and its element buffer
	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
	glDrawElements(mode, m_numIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

