#ifndef CAMERA_H
#define CAMERA_H

#include "zmath.h"
#include "glad/glad.h"

typedef struct camera {
    vec2_t position;
    float zoom;
} camera_t;

extern camera_t camera;

extern GLuint u_camera_pos_location;
extern GLuint u_camera_zoom_location;
extern GLuint u_camera_screen_size_location;

void set_camera_pos(float x, float y);
void set_camera_zoom(float zoom);
void init_camera();
void link_camera(GLuint program);
void update_camera();

#endif // CAMERA_H
