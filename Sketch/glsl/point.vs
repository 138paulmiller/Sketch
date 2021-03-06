#version 330

uniform vec3 eye;			//Current Camera Position
uniform mat4 model;			//Model's Local Transform 
uniform mat4 view;			//Camera View Transform 
uniform mat4 projection;	//3d -> 2d 


attribute vec3 vs_pos;
//smooth normals?
out vec3 fs_pos;


void main()
{
	fs_pos		=	vs_pos;

	gl_Position =	projection * view * model * vec4(vs_pos,1);
}