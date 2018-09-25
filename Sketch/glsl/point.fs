#version 330
in vec3 fs_pos;

uniform vec4 color;
out vec4 out_FragColor;

//determine if uv, color
void main()
{
	out_FragColor = color;

}