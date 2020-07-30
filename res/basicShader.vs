#version 120

attribute vec3 position;
attribute vec2 text;

varying vec2 text0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1);
	text0 = text;
}
