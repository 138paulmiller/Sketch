#include <water/Water.h>
//http://www.cs.utah.edu/~michael/water/waterPGColor.pdf//height 
//https://www.cg.tuwien.ac.at/courses/Seminar/WS2007/arbeit_fleck.pdf


int demo_water()
{
	LogIn("log.txt");

	const char *title = "Sketch++";
	int width = 540, height = 540;

	//initalizes GL!
	Window window(title, width, height);
	//ust be called after init
	Renderer::init();

	Vec3 pos(0.5, 1.0, -0.5);
	Vec3 dir(0, 0, -1.0f);
	Vec3 up(0, 1, 0);
	PerspectiveCamera camera((float)width / height, pos, dir, up, 0.001, 50);

	float delta, time = 0;

	const int waterWidth	= 128;
	const int waterHeight	= 128;
	float scale = 20;
	float speed = 0.1;
	bool zUp= true;

	Water water(waterWidth, waterHeight, 0.005f);
	
	pos = Vec3(0.5, scale, -0.5);

	camera.setPos(pos);

	camera.setTarget({ 0,0,0 });

	while (window.isOpen())
	{

		//glCullFace(GL_FRONT);
		window.update();
		time = window.getTime();
		const float temp = cos(time / 4);
		window.clear(temp*255.0f, 0.33f, 0.01f, 1);
		delta = window.getTimeDelta();

		
		if ((window.keystate(SDLK_q) == Window::DOWN)||(window.keystate(SDLK_q) == Window::HOLD))
			pos += Vec3(0.f, -1.0* speed,0.f);
		if ((window.keystate(SDLK_e) == Window::DOWN)|| (window.keystate(SDLK_e) == Window::HOLD))
			pos += Vec3(0.f, speed, 0.f);
		if ((window.keystate(SDLK_a) == Window::DOWN) || (window.keystate(SDLK_a) == Window::HOLD))
			pos += Vec3(-1.0* speed, 0.f, 0.f);
		if ((window.keystate(SDLK_d) == Window::DOWN) || (window.keystate(SDLK_d) == Window::HOLD))
			pos += Vec3(speed, 0.f, 0.f);
		if ((window.keystate(SDLK_w) == Window::DOWN) || (window.keystate(SDLK_w) == Window::HOLD))
			pos += Vec3(0.f, 0.f, -1.0* speed);
		if ((window.keystate(SDLK_s) == Window::DOWN) || (window.keystate(SDLK_s) == Window::HOLD))
			pos += Vec3(0.f, 0.f, speed);
		if (zUp && window.keystate(SDLK_z) == Window::DOWN)
		{
			water.setWireframe(!water.isWireframe());
			zUp = false; 
		}else if (window.keystate(SDLK_z) == Window::UP)
			{
				zUp = true;
			}
		
		if (window.keystate(SDLK_ESCAPE) == Window::DOWN)
			break;

		//update renderables
		water.update(delta);

		water.scaleBy({scale,scale,scale});
		//water.translateBy(pos);
		camera.setPos(pos);
		camera.setTarget({ 0,scale,scale });
		water.preRender();camera.bind();//set uniforms
		//bind time
		water.setTime(time);
		water.render();
		water.resetTransform();
		
	}
	Renderer::cleanup();
	return 0;
}