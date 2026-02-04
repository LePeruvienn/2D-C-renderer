#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "glad/glad.h"

int main(int argc, char** argv)
{
	if (create_window() != 0)
	{
		fprintf(stderr, "%s: Failed to create a windows.\n", argv[0]);
		exit(1);
	}

	if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
	{
		fprintf(stderr, "%s: Failed to initialize GLAD\n", argv[0]);
		exit(2);
	}

	while(keep_running)
	{
		update_window();
	}

	destroy_window();
}
