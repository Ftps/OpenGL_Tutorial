#include "display.hpp"
#include <iostream>
#include <GL/glew.h>

Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING); 		// initializes SDL

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);			//
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);			// buffers for color and alpha
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);			//
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);			//
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);		//
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	// double buffer for it has two images allocated
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);		//

	main_win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(main_win);		// < does something ^ creates the window

	GLenum status = glewInit();		// initializes GLEW
	if(status != GLEW_OK){
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	isClosed = false;	// states the window is open
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Display::~Display() 	// remember to use reverse order when freeing
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(main_win);
	SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);		// clears the screen and fills with a color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// performs it
}

void Display::Update()
{
	SDL_Event e;

	SDL_GL_SwapWindow(main_win);	// swaps between the two windows

	while(SDL_PollEvent(&e)){		// event handler
		if(e.type == SDL_QUIT){		// if windows is closed
			isClosed = true;
		}
	}
}

bool Display::IsClosed()
{
	return isClosed;
}
