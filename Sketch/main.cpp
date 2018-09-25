/*
	Sketch Framework

	call lambdas 

	TriangleMesh
	
	IndexedTriangleMesh : TriangleMesh
	////s

	setup(){}
	
	draw(){}

	HPP files files included as a way to partition source code


	//some callbacks
	https://en.cppreference.com/w/cpp/language/pimpl
*/

//Create GlobalShader access??
// Shader::use(FLAT_SHADER)??
// Shader::set(FLAT_SHADER)??

//extern int cpu_raytrace(int argv, char**);
#include <renderer/Window.h>
#include <renderer/Camera.h>
#include <renderer/RenderShapes.h>

#define TESTING 1

#if TESTING 
extern int demo_test();
extern int demo_water();
#endif
int main(int argc, char ** argv)
{

#if TESTING 
	//return demo_test();
	return demo_water();
#endif


	LogIn("log.txt");
	return 0;
}

