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
void free_mesh(mesh_t* mesh);

#endif // MESH_H
