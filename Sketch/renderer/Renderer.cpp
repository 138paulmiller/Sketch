#include <renderer/Renderable.h>
#include <vector>

namespace Renderer
{

	void init()
	{
		Shader::init();
	}
	
	void cleanup()
	{
		Shader::destroy();
	}

}