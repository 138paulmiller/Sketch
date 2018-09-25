#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <GL/glew.h>

#include <renderer/Vertex.h>
#include <renderer/Iterable.h>



//Implementations of Iterable

// --------------------------------  VertexArray ---------------------------------------
// Contains 
// Type constraints:
//		must define static void EnableVertexAttrib();
//	Iterates across the Vertex ids such that vertex i is 
class VertexArray
{
public:
	VertexArray();
	virtual  ~VertexArray();

	template <typename Vertex>
	inline void load(
		Shader * shader, 
		Vertex *vertices, 
		GLuint numVertices, 
		GLuint * indices, 
		GLuint numIndices, 
		bool dynamic = false	//
	)
	{
		bufferData(shader, vertices, numVertices, indices, numIndices, false, dynamic);
	}


	template <typename Vertex>
	inline void update(
		Shader * shader,
		Vertex *vertices,
		GLuint numVertices,
		GLuint * indices,
		GLuint numIndices
	)
	{
		bufferData(shader, vertices, numVertices, indices, numIndices, true);

	}

	void render(GLuint mode = GL_TRIANGLES) const;

private:
	template <typename Vertex>

	void bufferData(
		Shader *	shader,
		Vertex *	vertices,
		GLuint		numVertices,
		GLuint *	indices,
		GLuint		numIndices,
		bool		isUpdate = false,
		bool		dynamic = false
	);	//


	//Vertex Attributes
	//VAO		   
	GLuint m_vertexArray;
	//VBO
	GLuint m_vertexBuffer;
	//EBO
	GLuint m_elementBuffer;

	//number to draw
	GLuint m_numIndices;
	GLuint m_numVertices;
};

template <typename Vertex>
void VertexArray::bufferData(Shader * shader, Vertex *vertices, GLuint numVertices, GLuint * indices, GLuint numIndices, bool isUpdate, bool dynamic)
{

	DebugAssert(shader);
	DebugAssert(vertices);
	//bind VAO
	glBindVertexArray(m_vertexArray);

	//bind and buffer element data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
	if (isUpdate)
		///							offset, size, data
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, numIndices * sizeof(GLuint), indices);
	else
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);


	//bind and buffer the vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//dynamic, wiil vertices be updated??

	if (isUpdate)
			///							offset, size, data
		glBufferSubData(GL_ARRAY_BUFFER, 0, numVertices*sizeof(Vertex), vertices);
	else
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), vertices, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

	Vertex::EnableVertexAttrib(shader);


	//unbind all used buffers and array indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_numIndices = numIndices;
	m_numVertices = numVertices;
}


#endif //VERTEX_ARRAY_H