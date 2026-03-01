#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 2) in vec2 aVertexTexture;
layout (location = 3) in vec2 aVertexTransformPosition;
layout (location = 4) in vec2 aVertexTransformScale;
layout (location = 5) in float aVertexTransformRotation;

uniform vec2 uCameraPosition;
uniform float uCameraZoom;
uniform vec2 uScreenSize;

out vec2 vTexture;

void main() {

	vTexture = aVertexTexture;

	vec2 pos = aVertexPosition + uCameraPosition + aVertexTransformPosition;

	pos.x *= uScreenSize.y / uScreenSize.x;

	gl_Position = vec4(pos * uCameraZoom, 0.0, 1.0);
}
