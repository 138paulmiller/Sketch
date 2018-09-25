#pragma once

#include <renderer/Renderable.h>
//To prevent shader switch overhead
//maintains an mapping of shaders id to renderable list 
//defaults are place in indices [ 1, to ShaderType_Count)

//SINGLETON!
//TODO when binding renderable a shader call bind(id). When this class is rendered, it bind the shader. Render all renderables in the 
//					-> add a move if alreday bound to aa class. Renderable will contain a point to shader if bound!!
// What about multiple shaders per renderable?????
//	-Make multiple renderables, or use STATIC BRANCH???

//Batch by shader, texture etc...
class RenderBatch
{
public:
	RenderBatch();
	~RenderBatch();

private:

};

