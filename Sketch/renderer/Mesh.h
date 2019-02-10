#ifndef RENDER_ARRAY_H
#define RENDER_ARRAY_H

#include <renderer/Renderer.h>

//Create node class that contains local and parent matrices
//Add getLocalMatrix
//Add getWorldMatrix

//Create Textured

//Create AABBox min, max boxes inheriting base Mesh::Node 
//Create plane, sphere, etc classes (	glm::vec3 normal, point;	//analytic n and p)


//typedef RenderTriangle<ColorVertex, Flat>	FlatTriangle;
//typedef RenderTriangle<ColorVertex, PerVertex>	ColoredTriangle;
//typedef RenderTriangle<TextureVertex, Textured>	TexturedTriangle;


/*

Call Order
	VertexArray va
	va. load();
	while{
		va.update()
		...
		va.prerender()		//binds cur shader, pushes matrix
		...
		va.render()		//unbinds shader
	}
*/


template <typename VertexType, ShaderType shaderType>
class Mesh : public Renderable
{
protected:

	Array<VertexType> _vertices;
	Array<GLuint>	   _indices;

	void bind()		;
	void unbind()	;

private:

	glm::mat4		_transform; //local transform matrix
	VertexArray		_vertexArray;
	GLuint			_drawMode = GL_TRIANGLES;
	bool			_isWireframe = false;

public:
	Mesh(GLuint drawMode = GL_TRIANGLES);
	virtual  ~Mesh();


	/*
		calling order (prerender and render must be used as push and pop!)

		load	- loads data into buffer (intializes )
				- only required once.  If buffer is not same size or at same address, call update. 
		update	- update vertex data in buffer
				
		prerender	- push shader, updatae buffer data, uniforms etx
		render		- draw
		 
		 cleanup	- unbind stuff, pop shader

	*/
	virtual void load()					override final ;
	virtual void update(float delta)	override final ;
	virtual void preRender()					 final ;
	virtual void render()				override final ;


	inline void setScale		(const Vec3 & scalars)				{ _transform = scale		(Mat4(1), scalars);				}
	inline void setTranslate	(const Vec3 & deltas)				{ _transform = translate	(Mat4(1), deltas);				}
	inline void setRotate		(const Vec3 & axis, float angle)	{ _transform = rotate		(Mat4(1), axis, angle);			}

	inline void scaleBy			(const Vec3 & scalars)				{	_transform = scale		(_transform, scalars);			}
	inline void translateBy		(const Vec3 & deltas)				{	_transform = translate	(_transform, deltas);			}
	inline void rotateBy		(const Vec3 & axis, float angle)	{	_transform = rotate		(_transform,	axis, angle);	}

	inline Mat4 & transform()						{	return _transform;}
	inline void resetTransform()					{	_transform = Mat4(1);}

	inline void		setDrawMode(GLuint drawMode)	{ _drawMode = drawMode; }
	inline GLuint	getDrawMode()					{ return _drawMode; }
	
	inline void		setWireframe(bool isWireframe) { _isWireframe = isWireframe; }
	inline bool		isWireframe() { return _isWireframe; }

	//SuperClass API

	virtual void onBind()			{ DebugAssert(true); }	/* Mesh No Color!Superclass Must Override! use Shader::currnet()!    */
	virtual void onUnbind()			{ DebugAssert(true); }	/* Mesh No Color!Superclass Must Override! use Shader::currnet()!    */
	virtual void onRender()			{ }	/* Mesh No Color!Superclass Must Override! use Shader::currnet()!    */
	virtual void onPreRender()			{ }	/* Mesh No Color!Superclass Must Override! use Shader::currnet()!    */


};

#include <renderer/Mesh.hpp>

#endif //RENDER_ARRAY_H