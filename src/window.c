#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include "window.h"

SDL_Window* window = NULL;
SDL_GLContext gl_context = NULL;

int create_window() {

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("Test", 800, 600, SDL_WINDOW_OPENGL);

	if (!window)
	{
		SDL_Log("Erreur fenêtre: %s", SDL_GetError());
		return 1;
	}

	gl_context = SDL_GL_CreateContext(window);

	if (!gl_context) 
	{
		SDL_Log("Erreur OpenGL: %s", SDL_GetError());
		return 1;
	}

	bool keep_running = true;
	SDL_Event event;

	while (keep_running)
	{

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
				keep_running = false;
		}

		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DestroyContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	gl_context = NULL;
	window = NULL;

	return 0;
}
