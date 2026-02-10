#include "shaders.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int get_source(char* path, char** out)
{

	int fd = open(path, O_RDONLY);

	if (fd == -1)
	{
		return 1;
	}

	size_t size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);

	char* buf = malloc((size + 1) * sizeof(char));
	buf[size] = '\0';
	
	if (read(fd, buf, size) == -1)
	{
		return 1;
	}

	close(fd);

	*out = buf;

	return 0;
}

int get_shader_status(GLuint shader, GLenum pname)
{
	int  success;
	char infoLog[512];

	glGetShaderiv(shader, pname, &success);

	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("Error: Shader status failed, %s\n", infoLog);
	}

	return success;
}

int create_shader(char* path, GLuint type, GLuint* out)
{
	GLuint shader;
	shader = glCreateShader(type);

	char* buf;

	if (get_source(path, &buf) != 0)
	{
		return 1;
	}

	const char* source = buf;

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	if (!get_shader_status(shader, GL_COMPILE_STATUS))
	{
		return 2;
	}

	*out = shader;

	return 0;
}

int create_shader_program(GLuint* out, GLuint* shaders, size_t size)
{
	GLuint shader_program;
	shader_program = glCreateProgram();

	for (size_t i = 0; i < size; i++)
	{
		glAttachShader(shader_program, shaders[i]);
	}

	glLinkProgram(shader_program);

	if (!get_shader_status(shader_program, GL_LINK_STATUS))
	{
		return 1;
	}

	*out = shader_program;

	return 0;
}


