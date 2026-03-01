#ifndef DEBUG_H
#define DEBUG_H

#include "glad/glad.h"
#include <stdio.h>

#define GL_CALL(x) \
	x; \
	check_gl_error(#x, __FILE__, __LINE__);

void check_gl_error(char* expr, char* file, int line);

void init_debug();

#endif // DEBUG_H
