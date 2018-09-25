#version 330
//http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.161.9102&rep=rep1&type=pdf

uniform vec3 eye;			//Current Camera Position
uniform mat4 model;			//Model's Local Transform 
uniform mat4 view;			//Camera View Transform 
uniform mat4 projection;	//3d -> 2d 


attribute vec3 vs_pos;
attribute vec3 vs_normal;
attribute vec2 vs_uv ;


smooth out vec3 fs_pos;
smooth out vec3 fs_normal; 
smooth out vec2 fs_uv;
//ADD COLOR UNIFORM
uniform sampler2D sampler0;	//create another that has a uniform sampler array

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

vec3 gerstner_wave_normal(vec2  uv, float t )
{
	vec3 norm = vec3(0,1,0);
	//for each wave
	for(int i = 0; i <wave_count; i++)
	{
		float phase = waves[i].speed	* t;
		float theta = dot(	waves[i].dir,	uv) *waves[i].frequency+ phase ;
		float ampfreq = waves[i].amplitude *waves[i].frequency ;
		
		float omega = ampfreq* cos(theta);
		
		norm.y -= waves[i].steepness * ampfreq * sin(theta);

		norm.x -= waves[i].dir.x * omega; 
		norm.z -= waves[i].dir.y * omega;
	}
	return norm;
}

vec3 gerstner_wave_pos( vec2 uv, float t )
{
	vec3 pos = vec3(uv.x  ,0  ,uv.y);

	//for each wave 
	for(int i = 0; i <wave_count ; i++)
	{
		float phase = waves[i].speed * t;
		float theta = dot(waves[i].dir, uv) *waves[i].frequency + phase ;

		float ydelta =  waves[i].amplitude * sin(theta);
		//set uv displacement
		float xdelta = waves[i].steepness * waves[i].amplitude * cos(theta);
	
		pos.y += ydelta;
		pos.x += waves[i].dir.x * xdelta;
		pos.z += waves[i].dir.y * xdelta;
	}

	return pos;
	
}


void default_waves()
{
	wave_count = 3;

	waves[0].dir		=	vec2(0.4,0);	
	waves[0].amplitude	=	0.4	;
	waves[0].length		=	0.023;
	waves[0].speed		=	0.60;
	waves[0].steepness	=	0.5;			
	waves[0].frequency	=	0.030;			

	waves[1].dir		=	vec2(0,0.9);	
	waves[1].amplitude	=	0.1703	;
	waves[1].length		=	0.25;
	waves[1].speed		=	0.02;
	waves[1].steepness	=	0.8;			
	waves[1].frequency	=	0.93;			
	
	waves[2].dir		=	vec2(0.32,0.4);	
	waves[2].amplitude	=	0.7703	;
	waves[2].length		=	0.25;
	waves[2].speed		=	0.12;
	waves[2].steepness	=	0.04;			
	waves[2].frequency	=	0.93;	
}


void main()
{
	vec4 noise0 = texture(sampler0, vs_uv);
	
	//TODO make uniforms
	
	default_waves();

	vec2 uv = vs_pos.xz;//pos on ocean plane;
	float t = time;
	vec3 wave_pos = gerstner_wave_pos(uv, t);
	uv = wave_pos.xz;
	vec3 wave_normal = gerstner_wave_normal( uv, t);


	//noise
	vec3 mixer = vec3(0.259, 0.812, 0.000012);
	noise0 = noise0*vec4(mixer,1);
	//displacement
	float d =		noise0.x 
				+	noise0.y 
				;

	vec3 pos   = vec3(	vs_pos.x,vs_pos.y+d, vs_pos.z);



	pos = wave_pos*scale;
	//update normal (rotate by angle diff between new and old pos)
	

	fs_pos		=	(model * vec4(pos,1)).xyz;
	fs_uv		=	vs_uv;
	fs_normal	=	wave_normal;
	gl_Position =	projection * view * vec4(fs_pos,1);
}