#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"
#include "shaders.h"
#include "camera.h"
#include "image.h"
#include "sprite.h"
#include "zmath.h"
#include "batcher.h"

static GLuint shader_program;
static GLint u_texture_location;

static sprite_t s1;
static sprite_t s2;
static sprite_t s3;

void bind_texture(GLuint program)
{
	glUseProgram(shader_program);
	u_texture_location = glGetUniformLocation(program, "uTexture");
	glUniform1i(u_texture_location, 0);
}

void init_shaders()
{
	GLuint vert_shader;
	GLuint frag_shader;

	create_shader("assets/shaders/vert/texture.glsl", GL_VERTEX_SHADER, &vert_shader);
	create_shader("assets/shaders/frag/texture.glsl", GL_FRAGMENT_SHADER, &frag_shader);

	GLuint shaders[] = {vert_shader, frag_shader};

	create_shader_program(&shader_program, shaders, 2);
}
void init_graphics()
{
	printf("GPU: %s\n", glGetString(GL_RENDERER));
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Version: %s\n", glGetString(GL_VERSION));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	init_shaders();
	bind_texture(shader_program);

	init_camera();
	link_camera(shader_program);

	init_draw(shader_program);

	s1.transform.pos.x = 0;
	s1.transform.pos.y = 0;
	s1.transform.scale.x = 1;
	s1.transform.scale.y = 1;
	s1.transform.rotation = 0;

	s2.transform.pos.x = 1.0;
	s2.transform.pos.y = 1.0;
	s2.transform.scale.x = 1;
	s2.transform.scale.y = 1;
	s2.transform.rotation = 0;

	s3.transform.pos.x = 0;
	s3.transform.pos.y = 1.0;
	s3.transform.scale.x = 1;
	s3.transform.scale.y = 1;
	s3.transform.rotation = 0;

	GLenum err = glGetError();

	if (err != GL_NO_ERROR) {
		printf("OpenGL Error: %x\n", err);
	}
}

void update_graphics()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader_program);
	update_camera();

	begin_draw();

	draw(&s1);
	draw(&s2);
	draw(&s3);

	flush_draw();
}
