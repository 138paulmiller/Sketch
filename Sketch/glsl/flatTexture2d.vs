#version 330

uniform vec3 eye;			//Current Camera Position
uniform mat4 model;			//Model's Local Transform 
uniform mat4 view;			//Camera View Transform 
uniform mat4 projection;	//3d -> 2d 



attribute vec3 vs_pos;
attribute vec3 vs_normal;
attribute vec2 vs_uv ;


//smooth normals?
out vec3 fs_pos;
out vec3 fs_normal; 
out vec2 fs_uv;
//ADD COLOR UNIFORM


void main()
{
	fs_pos	=	vs_pos;
	fs_uv	=	vs_uv;
	fs_normal	=	vs_normal;
	gl_Position = projection * view * model * vec4(vs_pos,1);
}