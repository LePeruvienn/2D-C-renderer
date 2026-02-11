#include "camera.h"
#include "window.h"

camera_t camera;

GLuint u_camera_pos_location;
GLuint u_camera_zoom_location;
GLuint u_camera_screen_size_location;

static const char* U_CAMERA_POS_NAME = "uCameraPosition";
static const char* U_CAMERA_ZOOM_NAME = "uCameraZoom";
static const char* U_SCREEN_SIZE_NAME = "uScreenSize";

void set_camera_pos(float x, float y)
{
	camera.position.x = x;
	camera.position.y = y;
}

void set_camera_zoom(float zoom)
{
	camera.zoom = zoom;
}

void init_camera()
{
	set_camera_pos(0.5, 0.5);
	set_camera_zoom(1);
}


void link_camera(GLuint program)
{
	u_camera_pos_location = glGetUniformLocation(program, U_CAMERA_POS_NAME);
	u_camera_zoom_location = glGetUniformLocation(program, U_CAMERA_ZOOM_NAME);
	u_camera_screen_size_location = glGetUniformLocation(program, U_SCREEN_SIZE_NAME);

	update_camera();
}

void update_camera()
{
	glUniform2f(u_camera_pos_location, camera.position.x, camera.position.y);
	glUniform1f(u_camera_zoom_location, camera.zoom);
	glUniform2f(u_camera_screen_size_location, window_width, window_height);
}
