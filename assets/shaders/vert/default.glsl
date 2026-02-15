#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

uniform vec2 uCameraPosition;
uniform float uCameraZoom;
uniform vec2 uScreenSize;

out vec3 vColor;

void main() {

	vColor = aVertexColor;
	vec2 pos = aVertexPosition + uCameraPosition;

	gl_Position = vec4(pos * uCameraZoom, 0.0, 1.0);
}
