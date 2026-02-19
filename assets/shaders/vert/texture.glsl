#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 2) in vec2 aVertexTexture;

uniform vec2 uCameraPosition;
uniform float uCameraZoom;
uniform vec2 uScreenSize;

out vec2 vTexture;

void main() {

	vTexture = aVertexTexture;

	vec2 pos = aVertexPosition + uCameraPosition;

	pos.x *= uScreenSize.y / uScreenSize.x;

	gl_Position = vec4(pos * uCameraZoom, 0.0, 1.0);
}
