#version 330
in vec3 fs_pos;
in vec3 fs_normal; 
in vec2 fs_uv;

//Has access to uniforms

uniform sampler2D sampler0;	//create another that has a uniform sampler array
out vec4 out_FragColor;

//determine if uv, color
void main()
{
	out_FragColor = texture(sampler0, fs_uv);
	
}
