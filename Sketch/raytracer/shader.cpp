#include "shader.h"


void FlatShader::shade(Color & color, 
						const Camera& camera, 
						const Scene& scene, 
						const Intersection & intersection,
						const Material * material){
	color = material->ambient;	
}


void BlinnPhongShader::shade(Color & color, 
									const Camera& camera, 
									const Scene& scene, 
									const Intersection & intersection,
									const Material * material){

	static RNG rng(-1,1);
	//L = ka Ia + SUM(1,N) [kd Ii max(0, dot(n,l_i)) + ks Ii max(0, dot(n,h_i)^p]
	//removed to speed up, used as reference
	//notice ka and light are RGB so multiply does component-wise mult for ka and light RGB values
	Color ka = material->ambient;
	if(material->type == NONDIELECTRIC){
		const NonDielectricMaterial *nonDielectricMaterial = dynamic_cast<const NonDielectricMaterial*>(material);
		Color kd = nonDielectricMaterial->diffuse;
		Color ks = nonDielectricMaterial->specular;
		double p = nonDielectricMaterial->shininess; 

		Vec3f n = intersection.normal();
		Vec3f v = (camera.eye() - intersection.poi()).normal(); //from point to camera (e-p)
		Vec3f l; //from light to point (p-l)
		Vec3f h;//half between l and v
		Vec3f lightAvg;
		double shine, diffuse;
		color.set(0.0, 0.0, 0.0);
		//color += _globalLight;
		for(auto const & light : scene.lights()){
			l =  (light->position() - intersection.poi()).normal();
			h = (l+v).normal();
			shine = n.dot(h);
			diffuse = n.dot(l);
			if(shine < 0) shine = 0;
			if(diffuse < 0) diffuse = 0;
			//add shade color
			color += (kd * diffuse) +  ks * pow(shine, p);
			lightAvg += light->color();
		}
		//lightAvg /= scene.lights().size();// avg ambient light color 
		color += ka*lightAvg;
	}
	color.clamp(1);
}
