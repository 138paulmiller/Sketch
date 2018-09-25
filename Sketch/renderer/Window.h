#ifndef WINDOW_H
#define WINDOW_H
#define GLEW_STATIC

#include <renderer/Defs.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <string>
#include <cstdio>

/*

move to chrno?
using SystemClock = std::chrono::system_clock;
using SystemClockType = std::chrono::time_point<std::chrono::system_clock>;

inline int getTime() {
clock = SystemClock::now();
auto ctime = std::chrono::system_clock::to_time_t(clock);
std::ctime(&ctime);
return ctime;
}
SystemClockType clock;

*/


#define error(msg, ...) printf("ERROR in %s at %d:", __FILE__, __LINE__); printf(msg, __VA_ARGS__)

#define debug(msg, ...) printf(msg, __VA_ARGS__)


class Window
{
public:
	Window(std::string title, int width, int height);
	virtual ~Window();

	enum KeyState { UP=0, DOWN, HOLD};
	typedef int KeyId;

	inline	KeyState	keystate(KeyId id) { DebugAssert(id > -1 && id < KNUM);  return _keymap[id]; }


	//Accessors
	inline bool		isOpen()		const { return _isOpen; }
	inline float	getTimeDelta()	const { return _timeDelta; }
	inline float	getTime()		const { return _time ; }


	void	getMousePosition(int& x, int& y)	const;
	void	getMouseDelta	(int& dx, int& dy)	const;
	int		getHeight() const;
	int		getWidth()	const;
	bool update();
	void clear(float red, float green, float blue, float alpha);
	//Possible key states
private:
	//Number of possible keys
	static const int KNUM = 512;
	//Frames per second caps
	static const int FPS = 60;

	//if window is open
	bool          _isOpen;


	//if window is dirty
	bool          _isDirtyR;

	//each sdlkey is mapped to a keystate
	KeyState _keymap[KNUM];

	//total seconds passed
	float _time;
	// previous time before event poll
	float		_prevTime;

	// milliseconds between window updates
	float _timeDelta;

	// mouse positions and previous positions
	int _mouseX, _mouseY, _pmouseX, _pmouseY;

	// window dimensions
	int _width, _height;

	//  Handle to SDL window to query opengl and OS events
	SDL_Window*     _sdlWindow;

	//  Handle to SDL events, member to reduce reallocating on call stack
	SDL_Event*      _sdlEvent;

	// OpengGL Context that will handle drawing to the screen
	SDL_GLContext  _glContext;
};

#endif // WINDOW_H