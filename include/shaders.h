#ifndef SHADERS_H
#define SHADERS_H

#include "glad/glad.h"
#include <stddef.h>

extern const GLuint VERTEX_ATTR_POSITION;
extern const GLuint VERTEX_ATTR_COLOR;
extern const GLuint VERTEX_ATTR_TEXTURE;
extern const GLuint VERTEX_ATTR_MODEL;
extern const GLuint VERTEX_ATTR_TRANSFORM_POSITION;
extern const GLuint VERTEX_ATTR_TRANSFORM_SCALE;
extern const GLuint VERTEX_ATTR_TRANSFORM_ROTATION;

int create_shader(char* path, GLuint type, GLuint* out);
int create_shader_program(GLuint* out, GLuint* shaders, size_t size);

#endif // SHADERS_H
