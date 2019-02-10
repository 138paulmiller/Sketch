/*
Sketch Framework

call lambdas

TriangleMesh

IndexedTriangleMesh : TriangleMesh
////s

setup(){}

draw(){}

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
#include <renderer/Renderer.h>


int demo_test()
{


	LogIn("log.txt");

	const char *title = "Sketch++";
	int width = 540, height = 540;

	//initalizes GL!
	Window window(title, width, height);
	//ust be called after init
	Renderer::init();

	Vec3 pos(0, 0, 2.0021f);
	Vec3 dir(0, 0, -1.0f);
	Vec3 up(0, 1, 0);
	PerspectiveCamera camera((float)width / height, pos, dir, up);

	float delta, time = 0;

	Color4 rainbow[8] =
	{
		{ 0,0,0,1 },
		{ 1,0,0,1 },
		{ 0,1,0,1 },
		{ 1,1,0,1 },
		{ 0,0,1,1 },
		{ 1,0,1,1 },
		{ 1,1,1,1 },
		{ 0,1,1,1 }
	};

	PhongColorCube cube	(&rainbow[0]);
	FlatGrid grid		(1, 1, 0.5f, { 1,0.02,0.2,1 });
	PhongColorSphere sphere	(0.005f, { 1,0,0.5,1.0 });


	Texture texture;
	const int textureWidth = 50;
	const int textureHeight = 50;
	const float c = (textureHeight+textureWidth) / 2;
	Color4 img[textureHeight*textureWidth];
	for (int i = 0; i < textureHeight; i++)
		for (int j = 0; j < textureWidth; j++)
		{
			img[i*textureHeight + j] = { 
					fabs(sin(i+c))	,
					fabs(cos(j+c))	,
					fabs(j),
					1
			};
		}
	texture.load(&img[0][0], textureWidth, textureHeight, TEXTURE_RGBA, 0);

	TextureTriangle tri(&texture);
	while (window.isOpen())
	{

		//glCullFace(GL_FRONT);
		window.update();
		time = window.getTime();
		const float temp = cos(time / 4);
		camera.setPos({sin(temp), cos(temp),sin(temp)*sin(temp)-2});
		camera.setTarget({ 0,0,1.1 });
		window.clear(temp*255.0f, 0.33f, 0.01f, 1);
		delta = window.getTimeDelta();


		//update renderables
		tri.update(delta);
		cube.update(delta);
		grid.update(delta);

		//// front-scene
		//glClearDepth(1.0);
		glDepthFunc(GL_LESS);
		glClear(GL_DEPTH_BUFFER_BIT);
		//// back-scene 
		//glClearDepth(0.0);
		//glDepthFunc(GL_GREATER);
		//glClear(GL_DEPTH_BUFFER_BIT);

		tri.setRotate({ 0,1,0 }, sin(temp));
		tri.setTranslate({ -0.5,0,0 });
		tri.preRender();	/*<- move bind into (use Camera::current())*/
		camera.bind();//set uniforms
		tri.render();

		////
		cube.rotateBy({ 0,1,0 }, temp);
		cube.translateBy({ -1,0,0 });
		cube.preRender();
		camera.bind();//set uniforms
		cube.render();
		cube.resetTransform();

		///
		grid.rotateBy({ 0,1,1 }, temp);
		grid.preRender();
		camera.bind();//set uniforms
		grid.render();
		grid.resetTransform();

		sphere.rotateBy({ 0,1,1 }, temp);
		sphere.preRender();
		camera.bind();//set uniforms
		sphere.render();
		sphere.resetTransform();

	}
	Renderer::cleanup();
	return 0;
}

