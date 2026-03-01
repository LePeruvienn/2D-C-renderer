#include "debug.h"

void check_gl_error(char* expr, char* file, int line)
{
	GLenum err;

	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("OpenGL error %x | %s | %s:%d\n", err, expr, file, line);
	}
}

void init_debug()
{
	printf("GPU: %s\n", glGetString(GL_RENDERER));
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Version: %s\n", glGetString(GL_VERSION));
}
