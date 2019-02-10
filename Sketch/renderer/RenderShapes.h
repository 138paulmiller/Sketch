#ifndef RENDER_SHAPES_H
#define RENDER_SHAPES_H

#include <renderer/Renderable.h>
#include <renderer/Texture.h>
#include <renderer/Mesh.h>

//Create node class that contains local and parent matrices
//Add getLocalMatrix
//Add getWorldMatrix

//Create Textured

//Create AABBox min, max boxes inheriting base Mesh::Node 
//Create plane, sphere, etc classes (	glm::vec3 normal, point;	//analytic n and p)



class FlatTriangle : public Mesh<NormalVertex, ShaderType_Flat>
{
public:
	FlatTriangle(const Color4 & color = { 1,1,1,1 });

	//must be defined for flat shaders
	void onBind()	 override { Shader::current()->setUniformVec4(Shader::Uniform_Color, _color); }
	void onUnbind()  override { }

private:
	Color4 _color;
};

class PhongColorTriangle : public Mesh<ColorVertex, ShaderType_PhongColor>
{
public:
	PhongColorTriangle(const Color4 colors[3]);
private:
	void onBind()	 override { }
	void onUnbind()  override { }
};

class TextureTriangle : public Mesh<Texture2dVertex, ShaderType_FlatTexture2d>
{
public:
	TextureTriangle(Texture * texture);
private:
	Texture * _texture;
	void onBind()		{ _texture->bind(Shader::current()); }	/* Mesh No Color!Superclass Must Override! if super has any textures!"); */
	void onUnbind() 	{ _texture->unbind(); }	/* Mesh No Color!Superclass Must Override! if super has any textures!"); */

};




//Grid
class FlatGrid : public Mesh<NormalVertex, ShaderType_Flat>
{
public:
	FlatGrid(float width, float height, float tessalation = 0.5, const Color4 &color = { 0,0,0,0 });
	//must be defined for flat shaders
	void onBind()	 { Shader::current()->setUniformVec4(Shader::Uniform_Color, _color); }
	void onUnbind()  override { }

private:
	Color4 _color;
};




//Unit Cube
//VertexCallback() called for each (x,y,z), uv of cube
//typedef ()(const Vec3&, const Vec3&, const Vec2&) VertexCallback; //pos, norm, uv
template <typename VertexCallback>
class Cube : public Mesh<ColorVertex, ShaderType_Custom>
{
public:
	Cube();
private:
	void onBind()	 override {  }
	void onUnbind()  override {  }
};

class PhongColorCube : public Mesh<ColorVertex, ShaderType_PhongColor>
{
public:
	PhongColorCube(const Color4 colors[8]);
private:
	void onBind()	 override {  }
	void onUnbind()  override { }
};

//Unit Sphere
class PointSphere : public  Mesh<PointVertex, ShaderType_Point>
{
public:
	using SphereVertex = ColorVertex;
	PointSphere(float tessalation = 0.5, const Color4 & color = {0,0,0,0});
	//must be defined for flat shaders
	void onBind()	 override { Shader::current()->setUniformVec4(Shader::Uniform_Color, _color); }
	void onUnbind()  override { }
	virtual void onRender()	 override
	{
		int sz;
		glGetIntegerv(GL_POINT_SIZE, &sz);
		glPointSize(5);
		Mesh<PointVertex, ShaderType_Point>::render();
		glPointSize((float)sz);
	}

	virtual void onPreRender() override final
	{ }

private:
	Color4 _color;
};


//Unit Sphere
class PhongColorSphere : public  Mesh<ColorVertex, ShaderType_PhongColor>
{
public:
	using SphereVertex = ColorVertex;
	PhongColorSphere(float tessalation = 0.05, const Color4 & color = { 0,0,0,0 });
	//must be defined for flat shaders
	void onBind()	 override final {	Shader::current()->setUniformVec4(Shader::Uniform_Color, _color); }
	void onUnbind()  override final {	 }
	virtual void onRender()	 override final
	{
	
	}
	virtual void onPreRender()	override final
	{
		//wireframe
	 }
	private:
	Color4 _color;
};

#include <renderer/RenderShapes.hpp>
#endif // RENDER_SHAPES_H