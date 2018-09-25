#version 330

uniform vec3 eye;			//Current Camera Position
uniform mat4 model;			//Model's Local Transform 
uniform mat4 view;			//Camera View Transform 
uniform mat4 projection;	//3d -> 2d 



attribute vec3 vs_pos;
attribute vec3 vs_normal;
attribute vec4 vs_color;


//smooth normals?
smooth out vec3 fs_pos;
smooth out vec3 fs_normal; 
smooth out vec4 fs_color;


void main()
{
	vec4  pos	= model * vec4(vs_pos,1);
	vec4  norm	= model * vec4(vs_normal,1);
	
	fs_pos		=	pos.xyz;
	fs_color	=	vs_color;
	fs_normal	=	normalize(norm.xyz);
	
	gl_Position = projection * view * pos;
}