#ifndef MESH_H
#define MESH_H
#include <renderer/Renderable.h>
// Make Render Node PrimitiveRenderNode 
//Make PrimitiveRenderNode with Vertex Array (draws in -1,1 space)
//	PrimitveModel can use to scale 
//RenderArray?
class Mesh : Renderable
{
public:
	Mesh();
	virtual ~Mesh();
};

#endif

