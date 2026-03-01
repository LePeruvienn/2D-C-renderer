#include <stddef.h>
#include <stdint.h>
#include "graphics.h"
#include "shaders.h"
#include "camera.h"
#include "sprite.h"
#include "zmath.h"
#include "batcher.h"
#include "debug.h"

static GLuint shader_program;
static GLint u_texture_location;

static sprite_t* s1;
static sprite_t* s2;
static sprite_t* s3;

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
	init_debug();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GL_CALL(init_shaders());
	bind_texture(shader_program);

	init_camera();
	link_camera(shader_program);

	GL_CALL(init_draw(shader_program));

	image_t* img1 = create_image("assets/img/brotabro.png");
	image_t* img2 = create_image("assets/img/brotato.png");

	load_image(img1);
	load_image(img2);

	texture_t* tex1 = create_texture(img1);
	texture_t* tex2 = create_texture(img2);
	free_image(img1);
	free_image(img2);

	mesh_t* mesh = create_mesh_quad();

	s1 = create_sprite(mesh, tex1);
	s2 = create_sprite(mesh, tex1);
	s3 = create_sprite(mesh, tex2);

	set_sprite_pos(s1, (vec2_t) {0.0, 0.0});
	set_sprite_pos(s2, (vec2_t) {1.0, 0.0});
	set_sprite_pos(s3, (vec2_t) {0.0, 1.0});
}

void update_graphics()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader_program);
	update_camera();

	begin_draw();

	draw(s1);
	draw(s2);
	draw(s3);

	flush_draw();
}
