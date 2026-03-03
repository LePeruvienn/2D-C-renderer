#ifndef DEBUG_H
#define DEBUG_H

#include "glad/glad.h"

#define GL_CALL(x) \
	x; \
	check_gl_error(#x, __FILE__, __LINE__);

void init_debug();
void check_gl_error(char* expr, char* file, int line);

#endif // DEBUG_H
