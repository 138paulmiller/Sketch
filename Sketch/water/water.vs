#version 330
//http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.161.9102&rep=rep1&type=pdf

uniform vec3 eye;			//Current Camera Position
uniform mat4 model;			//Model's Local Transform 
uniform mat4 view;			//Camera View Transform 
uniform mat4 projection;	//3d -> 2d 


in vec3 vs_pos;
in vec3 vs_normal;
in vec2 vs_uv ;

smooth out vec3 fs_pos;
smooth out vec3 fs_normal; 
smooth out vec2 fs_uv;

uniform float time;
uniform float scale; //scale wave pos;

const int MAX_WAVE_COUNT = 10;

//uniform
 int wave_count;
struct GerstnerWave
{
	vec2	dir;		//direction of wave to travel 
	float	amplitude;	//height of wave
	float	length;    //length between crests
	float	speed;		//cycles
	float	steepness;  //crest sharpness 
	float	frequency;
} waves[MAX_WAVE_COUNT];


vec3 gerstner_wave_pos( vec2 uv, float t )
{
	vec3 pos = vec3(uv.x  ,0  ,uv.y);

	//for each wave 
	for(int i = 0; i <wave_count ; i++)
	{
		float freq  = waves[i].frequency * t;
		float phase = waves[i].speed * freq;
		float amp	= waves[i].amplitude;

		float theta = dot(waves[i].dir, uv) + freq + phase ;

		float ydelta =  amp * sin(theta);
		//set uv displacement
		float xdelta = waves[i].steepness * amp * cos(theta);
	
		pos.y += ydelta;
		pos.x += waves[i].dir.x * xdelta;
		pos.z += waves[i].dir.y * xdelta;
	}

	return pos;
	
}

vec3 gerstner_wave_normal(vec2  uv, float t )
{
	vec3 norm = vec3(0,1,0);
	//for each wave
	for(int i = 0; i <wave_count; i++)
	{
		float freq  = waves[i].frequency * t;
		float phase = waves[i].speed * freq;
		float amp	= waves[i].amplitude;

		float theta = dot(waves[i].dir, uv) + freq + phase ;


		float ampfreq = waves[i].amplitude *waves[i].frequency ;
		
		float omega = ampfreq* cos(theta);
		
		norm.y += 1-waves[i].steepness * ampfreq * sin(theta);

		norm.x -= waves[i].dir.x * omega; 
		norm.z -= waves[i].dir.y * omega;
	}
	return normalize(norm);
}

void default_waves()
{
	wave_count = 4;

	waves[0].dir		=	vec2(0.4,0);	
	waves[0].amplitude	=	0.64;
	waves[0].steepness	=	0.64;			
	waves[0].frequency	=	0.64;
	waves[0].speed		=	1.28;
	
	waves[1].dir		=	vec2(0.412,0.4);	
	waves[1].amplitude	=	0.32;
	waves[1].steepness	=	0.99;			
	waves[1].frequency	=	0.00123;
	waves[1].speed		=	0.56;

	waves[2].dir		=	vec2(0.8,0.7);	
	waves[2].amplitude	=	0.06;
	waves[2].steepness	=	1.28;			
	waves[2].frequency	=	0.77;
	waves[2].speed		=	0.64;


	waves[3].dir		=	vec2(0.03,0.4);	
	waves[3].amplitude	=	0.046;
	waves[3].steepness	=	1.0;
	waves[3].frequency	=	0.16;
	waves[3].speed		=	0.04;

}



vec3 lerp(vec3 a, vec3 b, float t)
{
	return a * t + (1-t)*b;
}

void main()
{
	default_waves();

	//TODO make uniforms
	vec3 mix			= vec3(1.89, -1.5, + 0.5);

	vec3 pos			= vs_pos;
	vec2 xz				= vs_pos.xz;	//pos on ocean plane;

	float t				= time;
	vec3 wave_pos		= gerstner_wave_pos(xz, t);
	xz					= wave_pos.xz;
	vec3 wave_normal	= gerstner_wave_normal( xz, t);


	pos					= (pos + wave_pos)*scale;
	vec3 norm			=  wave_normal;
	//update normal (rotate by angle diff between new and old pos)
	

	fs_pos		=	(model * vec4(pos,1)).xyz;
	fs_uv		=	vs_uv;
	fs_normal	=	norm;
	gl_Position =	projection * view * vec4(fs_pos,1);
}