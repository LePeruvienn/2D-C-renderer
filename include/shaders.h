#ifndef SHADERS_H
#define SHADERS_H

#include "glad/glad.h"
#include <stddef.h>

int create_shader(char* path, GLuint type, GLuint* out);
int create_shader_program(GLuint* out, GLuint* shaders, size_t size);

#endif // SHADERS_H
