#include <SDL3/SDL_scancode.h>
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "camera.h"
#include "glad/glad.h"

const float speed = 0.00001;

void update_input()
{
	int num_keys;
	const bool *key_states = SDL_GetKeyboardState(&num_keys);

	if (key_states[SDL_SCANCODE_W])
	{
		camera.position.y += speed;
	}
	else if (key_states[SDL_SCANCODE_A])
	{
		camera.position.x -= speed;
	}
	else if (key_states[SDL_SCANCODE_S])
	{
		camera.position.y -= speed;
	}
	else if (key_states[SDL_SCANCODE_D])
	{
		camera.position.x += speed;
	}
	else if (key_states[SDL_SCANCODE_Q])
	{
		camera.zoom -= speed;
	}
	else if (key_states[SDL_SCANCODE_E])
	{
		camera.zoom += speed;
	}
}

int main(int argc, char** argv)
{
	if (create_window() != 0)
	{
		fprintf(stderr, "%s: Failed to create a windows.\n", argv[0]);
		exit(1);
	}

	SDL_Event event;

	while(keep_running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
				keep_running = false;
		}
		update_input();
		update_window();
	}

	destroy_window();

	return 0;
}
