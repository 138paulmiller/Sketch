#ifndef VERTEX_H
#define VERTEX_H
#include <renderer/Shader.h>
#include <cstddef>
//Create base Vertex class, vir
//struct Vertex
//{
//	
//	virtual ~Vertex()=0;
//};

//Vertex with pos, normal, color, and UV
struct PointVertex 
{
	
	//	static constexpr int stride() { return sizeof(Vertex); }
	PointVertex(
		const Vec3	& pos = { 0,0,0 }
	)
		:pos(pos)
	{}
	~PointVertex() {}
	static void EnableVertexAttrib(const Shader * shader);
	Vec3 pos;
};

//Vertex with pos, normal, color, and UV
struct NormalVertex
{

	//	static constexpr int stride() { return sizeof(Vertex); }
	NormalVertex(
		const Vec3	& pos = { 0,0,0 },
		const Vec3	& normal = { 0,0,0 }
	)
		:pos(pos)
	{}
	~NormalVertex() {}
	static void EnableVertexAttrib(const Shader * shader);
	Vec3 pos;
	Vec3 normal;
};


//Vertex with pos, normal, color, and UV
struct ColorVertex 
{
	
	ColorVertex(
		const Vec3		& pos		= { 0,0,0	},
		const Vec3		& normal	= { 0,0,0	},
		const Color4	& color		= { 0,0,0,0	})
		:pos(pos), normal(normal), color(color) 
	{}
	~ColorVertex() {}
	
	static void EnableVertexAttrib(const Shader * shader);

	Vec3 pos;
	Vec3 normal;
	Color4 color;
};


//Vertex with pos, normal, color, and UV
struct Texture2dVertex 
{ 

	Texture2dVertex(	
		const Vec3	& pos		= { 0,0,0	},
		const Vec3	& normal	= { 0,0,0	},
		const Vec2	& uv		= { 0,0		})
		:pos(pos), normal(normal), uv(uv) {}

	~Texture2dVertex() {}
	static void EnableVertexAttrib(const Shader * shader);

	Vec3 pos;
	Vec3 normal;
	Vec2 uv;
};

#endif
