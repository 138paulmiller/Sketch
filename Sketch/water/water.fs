#version 330
uniform vec3 eye;			//Current Camera Position

//uniform mat4 model;			//Model's Local Transform 
//uniform mat4 view;			//Camera View Transform 
//uniform mat4 projection;	//3d -> 2d 

smooth in vec3 fs_pos;
smooth in vec3 fs_normal; 
smooth in vec2 fs_uv;
in vec3 world_eye;

#define LIGHT_COUNT 8
#define MATERIAL_COUNT 8

struct Light
{
//TODO div intensity  by distance 
	float intensity;	//strength of intensity
	vec3 color;	//color for specular high light 
	vec3 pos;
};

struct Material
{
	vec3		//coefficients
		ka,		//ambient
		kd,		//diffuse
		ks;		//Specular 
	float alpha;		//shininess

	vec4 base;	//base color (texture of attrib)
	float mix;		//amt to mix with base color
};

//TODO SET UNIFORMS IN CPU
//uniform 
Light lights[LIGHT_COUNT];
//uniform 
Material materials[MATERIAL_COUNT];

//pos - point on surface 
//norm - normal
//refl - reflected norm 
//eye - pos 
vec3 phong(Material mat, vec3 pos, vec3 norm, vec3 eye)
{
	vec3 light_dir	;
	vec3 half_vec	;
	vec3 eye_dir	= (eye - pos);
	vec3 illum		= vec3(0);//sum of light intensity
	float intensity	= 0;
	
	//norm= normalize(norm);
	//for each light
	for(int i =0 ; i < 1; ++i)
	{

		light_dir  = normalize(lights[i].pos - pos);
		
		intensity += lights[i].intensity;
						//diffuse 
		
		//blinn 
		half_vec = normalize(light_dir + eye_dir);

		illum += 		mat.kd * dot(light_dir, norm)
						//Specular
						+ mat.ks * pow(dot(norm, half_vec), mat.alpha)  * lights[i].color
						;
	}
	illum +=  mat.ka*intensity;
	return illum;
}


uniform sampler2D sampler0;	//create another that has a uniform sampler array
out vec4 out_FragColor;
//determine if uv, color
void main()
{
	vec4 color= texture(sampler0, fs_uv);
//TODO set by CPU
	lights[0].pos = 	eye;
	lights[0].intensity = 1.0;
	lights[0].color = vec3(1.0);

 

//REF http://devernay.free.fr/cours/opengl/materials.html

	
	materials[0].ka =		vec3(0.0215	, 	0.1745	, 	0.0215	);
	materials[0].kd =		vec3(0.07568,	0.61424 ,	0.07568	);
	materials[0].ks =		vec3(1.0	,	1.0		,	1.0);
	materials[0].alpha =	0.6 * 128;
	materials[0].base = color;
	materials[0].mix = 0.5;


	vec4 illum  = vec4(
		phong( materials[0], fs_pos, fs_normal, lights[0].pos),
		1);

	out_FragColor = mix(materials[0].base,illum, materials[0].mix) ;


}