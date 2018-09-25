#pragma once
#include <renderer/Shader.h>
#include <renderer/Renderable.h>
namespace Renderer
{
	//inits and cleans up renderer singletons 
	//create single stacks for binding/unbinding shaders, cameras, textures, matrices

	void		cleanup();
	void		init();
}