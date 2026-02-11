#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL.h>

extern const unsigned int window_width;
extern const unsigned int window_height;

extern SDL_Window* window;
extern SDL_GLContext gl_context;
extern bool keep_running;

int create_window();
void update_window();
void destroy_window();

#endif // WINDOW_H
