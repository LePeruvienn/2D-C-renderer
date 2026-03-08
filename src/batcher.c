#include "batcher.h"
#include "image.h"
#include "shaders.h"
#include <stdlib.h>

#define MAX_SPRITES_AMOUNT 100

static sprite_t* sprites[MAX_SPRITES_AMOUNT];
static unsigned int sprites_amount = 0;

static mesh_t* current_mesh = NULL;
static texture_t* current_tex = NULL;
static GLuint current_shader;

static GLuint ibo;
static sprite_instance_t instances[MAX_SPRITES_AMOUNT];

void gl_init()
{
	glGenBuffers(1, &ibo);

	glBindVertexArray(current_mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, ibo);

	glEnableVertexAttribArray(SPRITE_ATTR_UVRECT);
	glEnableVertexAttribArray(TRANSFORM_ATTR_POSITION);
	glEnableVertexAttribArray(TRANSFORM_ATTR_SCALE);
	glEnableVertexAttribArray(TRANSFORM_ATTR_ROTATION);

	glVertexAttribPointer(
		SPRITE_ATTR_UVRECT,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(sprite_instance_t),
		(const void*) offsetof(sprite_instance_t, uv)
	);

	glVertexAttribPointer(
		TRANSFORM_ATTR_POSITION,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(sprite_instance_t),
		(const void*) offsetof(sprite_instance_t, trans.pos)
	);

	glVertexAttribPointer(
		TRANSFORM_ATTR_SCALE,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(sprite_instance_t),
		(const void*) offsetof(sprite_instance_t, trans.scale)
	);

	glVertexAttribPointer(
		TRANSFORM_ATTR_ROTATION,
		1,
		GL_FLOAT,
		GL_FALSE,
		sizeof(sprite_instance_t),
		(const void*) offsetof(sprite_instance_t, trans.rotation)
	);

	glVertexAttribDivisor(SPRITE_ATTR_UVRECT, 1);
	glVertexAttribDivisor(TRANSFORM_ATTR_POSITION, 1);
	glVertexAttribDivisor(TRANSFORM_ATTR_SCALE, 1);
	glVertexAttribDivisor(TRANSFORM_ATTR_ROTATION, 1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void init_draw(GLuint shader)
{
	sprites_amount = 0;
	current_shader = shader;
}

void begin_draw()
{
	sprites_amount = 0;
}

void draw(sprite_t* sprite)
{
	if(current_mesh == NULL)
	{
		current_mesh = sprite->mesh;
		gl_init();
	}

	if(current_tex == NULL)
	{
		current_tex = sprite->tex;
	}

	if (current_tex->id != sprite->tex->id)
	{
		flush_draw();
		begin_draw();
		current_tex = sprite->tex;
	}

	if (current_mesh != sprite->mesh)
	{
		flush_draw();
		begin_draw();
		current_mesh = sprite->mesh;
		gl_init();
	}

	sprites[sprites_amount] = sprite;

	instances[sprites_amount].uv = sprite->uv;
	instances[sprites_amount].trans = sprite->transform;

	sprites_amount++;
}

void flush_draw()
{
	if (sprites_amount == 0)
		return;

	glBindVertexArray(current_mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, ibo);

	glBufferData(
		GL_ARRAY_BUFFER,
		sprites_amount * sizeof(sprite_instance_t),
		instances,
		GL_DYNAMIC_DRAW
	);

	glUseProgram(current_shader);
	glBindTexture(GL_TEXTURE_2D, current_tex->id);

	glDrawElementsInstanced(
		GL_TRIANGLES,
		current_mesh->indices_amount,
		GL_UNSIGNED_INT,
		NULL,
		sprites_amount
	);

	glBindVertexArray(0);
}
