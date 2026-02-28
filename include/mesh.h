#ifndef MESH_H
#define MESH_H

#include "glad/glad.h"

typedef struct mesh
{
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

} mesh_t;

mesh_t* create_mesh_quad();

#endif // MESH_H
