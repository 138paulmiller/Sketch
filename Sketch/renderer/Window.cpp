#include <renderer/Window.h>

#define BUFFER_SIZE 64

Window::Window(std::string title, int width, int height)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		error("Window::SDL Failed to initialize!");
		return;
	}

	_sdlWindow = SDL_CreateWindow(title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);
	//Initialize opengl color attributes buffer size
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, BUFFER_SIZE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, BUFFER_SIZE); 
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 2);

	_glContext = SDL_GL_CreateContext(_sdlWindow);
	if (glewInit() != GLEW_OK) {
		error("Window::Glew Failed to initialize!");
		return;
	}
	_isOpen = true;
	glewExperimental = true;


	_width = width;
	_height = height;
	_mouseX = _mouseY = _pmouseX = _pmouseY = 0;
	for (int i = 0; i < KNUM; i++)
		_keymap[i] = UP;
	_time = 0;
	_prevTime = 0;
}
Window::~Window()
{
	//destroy context then window
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_sdlWindow);
	SDL_Quit();
}

void Window::getMousePosition(int& x, int& y) const
{
	x = _mouseX;
	y = _mouseY;
}

void Window::getMouseDelta(int& dx, int& dy) const
{
	dx = _pmouseX - _mouseX;
	dy = _pmouseY - _mouseY;
}
int Window::getWidth() const
{
	return _width;
}
int Window::getHeight() const
{
	return _height;
}


void Window::clear(float red, float green, float blue, float alpha)
{
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glDepthFunc(GL_LEQUAL); 
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::update()
{
	_prevTime = _time;

	//swap render and display buffers
	SDL_GL_SwapWindow(_sdlWindow);

	//Poll input events
	SDL_Event event;
	_pmouseX = _mouseX;
	_pmouseY = _mouseY;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			_isOpen = false;
		else if (event.type == SDL_MOUSEMOTION)
		{
			int x = event.motion.x, y = event.motion.y;
			if (x > 0 && x < _width)
				_mouseX = x;
			if (y > 0 && y < _height)
				_mouseY = y;
		}
		else if (event.type == SDL_KEYUP)
		{
			_keymap[event.key.keysym.sym] = UP;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			int keysym = event.key.keysym.sym;
			switch (keysym)
			{
			case SDLK_ESCAPE:
				_isOpen = false;
				break;
			default:
				//if was previously down
				if (_keymap[keysym] == DOWN)
					_keymap[event.key.keysym.sym] = HOLD;
				else
					_keymap[event.key.keysym.sym] = DOWN;
				break;
			}
		}
	}
	//delay

	_time = SDL_GetTicks() / 1000.0f;
	_timeDelta = _time - _prevTime;
	//_time += _timeDelta;
	if (_timeDelta < 1000.0f / FPS)
		SDL_Delay((int)(1000.0f / FPS - _timeDelta));
	return _isOpen;
}
