#version 330 core

layout (location = 0) in vec2 aVertexPosition;
layout (location = 1) in vec4 aVertexColor;
layout (location = 2) in vec2 aVertexUV;
layout (location = 3) in vec4 aUVRect;
layout (location = 4) in vec2 aTransformPosition;
layout (location = 5) in vec2 aTransformScale;
layout (location = 6) in float aTransformRotation;

uniform vec2 uCameraPosition;
uniform float uCameraZoom;
uniform vec2 uScreenSize;

out vec2 vUV;
out vec4 vColor;

void main() {

	vec2 size = aUVRect.zw - aUVRect.xy;
    vUV = aUVRect.xy + aVertexUV * size;

	vColor = aVertexColor;

	vec2 pos = aVertexPosition + uCameraPosition + aTransformPosition;

	pos.x *= uScreenSize.y / uScreenSize.x;

	gl_Position = vec4(pos * uCameraZoom, 0.0, 1.0);
}
