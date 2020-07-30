#version 120

varying vec2 text0;

uniform sampler2D diffuse;
varying vec3 normal0;

void main()
{
	gl_FragColor = texture2D(diffuse, text0)
					*clamp(dot(-vec3(1, -1, 1), normal0), 0.0, 1.0);
}
