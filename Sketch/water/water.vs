#version 330
//http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.161.9102&rep=rep1&type=pdf

uniform vec3 eye;			//Current Camera Position
uniform mat4 model;			//Model's Local Transform 
uniform mat4 view;			//Camera View Transform 
uniform mat4 projection;	//3d -> 2d 

out vec3 world_eye;

attribute vec3 vs_pos;
attribute vec3 vs_normal;
attribute vec2 vs_uv ;


smooth out vec3 fs_pos;
smooth out vec3 fs_normal; 
smooth out vec2 fs_uv;
//ADD COLOR UNIFORM
uniform sampler2D sampler0;	//create another that has a uniform sampler array

uniform float time;

void main()
{
	float t = normalize(time);
	vec4 noise0 = texture(sampler0, vs_uv);
	vec3 mixer = vec3(0.259, 0.812, 0.000012);
	noise0 = noise0*vec4(mixer,1);
	//displacement
	float d =		noise0.x 
				+	noise0.y 
				;

	//make uniform
	vec3 pos   = vec3(	vs_pos.x,
						vs_pos.y+d,
						vs_pos.z);
	//update normal (rotate by angle diff betewwenn new and old pos)
	vec3 norm = normalize(pos-vs_pos);


	fs_pos		=	(model * vec4(pos,1)).xyz;
	fs_uv		=	vs_uv;
	fs_normal	=	vs_normal;//norm;
	gl_Position =	projection * view * vec4(fs_pos,1);
	world_eye	=	(view * vec4(eye,1)).xyz;
}