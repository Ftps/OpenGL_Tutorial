#version 120

attribute vec3 position;
attribute vec2 text;
attribute vec3 normal;

varying vec2 text0;
varying vec3 normal0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1);
	text0 = text;
	normal0 = (transform * vec4(normal, 0)).xyz;
}
