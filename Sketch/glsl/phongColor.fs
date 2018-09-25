//see https://en.wikipedia.org/wiki/Phong_shading https://en.wikipedia.org/wiki/Blinn-Phong_shading
#version 330


uniform vec3 eye;			//Current Camera Position
//uniform mat4 model;			//Model's Local Transform 
//uniform mat4 view;			//Camera View Transform 
//uniform mat4 projection;	//3d -> 2d 

smooth in vec3 fs_pos;
smooth in vec3 fs_normal; 
smooth in vec4 fs_color;

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
	float		//coefficients
		ks,		//Specular 
		kd,		//diffuse
		ka,		//ambient
	alpha;		//shininess

	vec4 color;	//base color (texture of attrib)
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
	vec3 eye_dir	= normalize(eye - pos);
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
					+	//Specular
						mat.ks * pow(dot(norm, half_vec), mat.alpha) 
						* lights[i].color
						;
	}
	illum +=  mat.ka*intensity;
	return illum;
}
out vec4 out_FragColor;

//determine if uv, color
void main()
{
//TODO set by CPU
	lights[0].pos = eye;
	lights[0].intensity = 1.0;

	
	materials[0].ks = 0.003;
	materials[0].kd = 0.45;
	materials[0].ka = 0.15;
	materials[0].alpha = 1024;
	materials[0].color = fs_color;
	materials[0].mix = 1.0;


	vec3 illum  = phong( materials[0], fs_pos, fs_normal, eye) ;
	

	out_FragColor = vec4(illum,1) * materials[0].color;


}