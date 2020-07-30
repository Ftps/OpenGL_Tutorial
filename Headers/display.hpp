#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>
#include <SDL2/SDL.h>

class Display{
public:
	Display(int width, int height, const std::string& title);
	~Display();
	void Clear(float r, float g, float b, float a);
	void Update();
	bool IsClosed();
private:
	SDL_Window* main_win;
	SDL_GLContext glContext;
	bool isClosed;
};

#endif
