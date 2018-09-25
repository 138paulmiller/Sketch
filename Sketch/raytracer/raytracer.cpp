#include "raytracer.h"

RayTracer::RayTracer(
		Camera* camera,
		Viewport* viewport,
		Projection* projection,
		Shader* shader)
	:_camera(camera), 
	_viewport(viewport), 
	_projection(projection), 
	_shader(shader){
}

void RayTracer::setBackgroundColor(const Color & backgroundColor){
	_backgroundColor = backgroundColor;
}

void RayTracer::setCamera(Camera* camera){
	_camera = camera;
}

void RayTracer::setViewport(Viewport* viewport){
	_viewport = viewport;
}
void RayTracer::setProjection(Projection* projection){
	_projection = projection;
}

void RayTracer::setShader(Shader* shader){
	_shader = shader;
}


bool RayTracer::valid(){
	return _shader != nullptr 
		&& _projection != nullptr 
		&& _camera != nullptr 
		&& _viewport != nullptr;
}

void RayTracer::render(const Scene& scene, Image & image, int depth ){
	if(!valid()) return;
	Intersection intersection;
	Ray3f viewRay; 
	Color color;
	double u,v;
	for(int j = 0; j < image.height(); ++j ){	
		for(int i = 0; i < image.width(); ++i ){
			intersection.reset();
			_viewport->uv(u,v, i,j);
			_projection->getViewRay(viewRay, *_camera, u,v);
			color = trace(viewRay, scene, intersection, depth);
			image.pixel(i,j) = color;
		}
	}
}

void RayTracer::castRay(const Ray3f & ray, const Scene & scene, Intersection& intersection){
	for( auto const & object : scene.objects()){
		object->checkIntersection(ray, intersection);
	}
}

Color RayTracer::trace(const Ray3f & ray, const Scene & scene, Intersection& intersection, int depth){
	//traces the ray !
	//recursively follow the ray
	//if hit
	Color color(_backgroundColor);
	castRay(ray, scene, intersection);
	if(intersection.valid()){
		//trace the shadow, reflect and refract rays depending on material
		//shadow ray is from poi to light, if any lights produce shadow 
		_shader->shade(color, *_camera, scene, intersection, intersection.object()->material());
		if(depth > 0 ){
			switch(intersection.object()->material()->type)
			{
				case NONDIELECTRIC:
				{
					const NonDielectricMaterial * material = dynamic_cast<const NonDielectricMaterial*>(intersection.object()->material());
					double refl = material->reflectivity;
					// only get the shadow color
					//if relfective
					if(! almost_equal(0.0, refl)){
						Ray3f reflectRay;
						Intersection reflectIntersection;
						reflectRay.setOrigin(intersection.poi() - intersection.normal()*BIAS);
						reflectRay.setDirection(reflect(ray.direction(), intersection.normal()).normal());
						reflectIntersection.setIgnoreObject(intersection.object()); //prevent self intersection
						Color reflectColor = trace(reflectRay, scene, reflectIntersection, depth-1);
						color = color * (1-refl) + reflectColor*refl;
					}
					break;
				}

				case DIELECTRIC:
				{
					Ray3f refractRay;
					Intersection refractIntersection;
					Ray3f reflectRay;
					Intersection reflectIntersection;
					Color reflectColor(0), refractColor(0);
					const DielectricMaterial * material = dynamic_cast<const DielectricMaterial*>(intersection.object()->material());

					double index = material->refractionIndex;
					float kr = fresnel(ray.direction(), intersection.normal(), index);
					// compute refraction if it is not a case of total internal reflection
					bool isOut = ray.direction().dot(intersection.normal()) < 0;
					if (kr < 1) 
					{
						//if any between orig and normal is less than zero, ray is cast inside object
						if(isOut)
							refractRay.setOrigin(intersection.poi() - intersection.normal()*BIAS);
						else
							refractRay.setOrigin(intersection.poi() + intersection.normal()*BIAS);
						refractRay.setDirection(refract(ray.direction(), intersection.normal(), index).normal());
						//compute reflect ray and retrace!, grab the color
						refractColor = trace(refractRay, scene, refractIntersection, depth-1);	
					}
					if(isOut)
						reflectRay.setOrigin(intersection.poi() + intersection.normal()*BIAS);
					else
						reflectRay.setOrigin(intersection.poi() - intersection.normal()*BIAS);
					reflectRay.setDirection(reflect(ray.direction(), intersection.normal()).normal());
					reflectIntersection.setIgnoreObject(intersection.object()); //prevent self intersection
					reflectColor = trace(reflectRay, scene, reflectIntersection, depth-1);
					
					color += reflectColor * kr + refractColor * (1-kr);  

					break;
				}
				default: break;
			}
		} //end recursion
		computeShadowColor(color, ray, scene, intersection, 0); //not recursive		
	}
	color.clamp(1);
	return color;
}

Vec3f  RayTracer::reflect(const Vec3f & dir, const Vec3f & normal){
	return dir - normal * 2 * dir.dot(normal);
}


void RayTracer::computeShadowColor(Color & color, const Ray3f & ray, const Scene & scene, Intersection& intersection, int depth){
	// SEE : https://www.cs.unc.edu/~dm/UNC/COMP236/LECTURES/SoftShadows.pdf
	Ray3f shadowRay;
	Intersection shadowIntersection;
	Color totalColor(color);//default not change
	double numSamples = 0;
	double distance = 0;
	int  totalNumSamples = 0;
	for(auto const & light : scene.lights() ){
		//shadowColor=_backgroundColor;//default not change
		//set intersection distance to be between light and poi
		for(int i = 0; i < light->numSamples(); ++i){
			shadowIntersection.reset();
			shadowIntersection.setIgnoreObject(intersection.object());//prevent intersection of shadow ray with current intersecting object
			//if soft shadow, gather multiple samples and set color to the average of intersection ambient and background
			shadowRay = light->makeShadowRay(intersection.poi()+intersection.normal()*BIAS, distance);
			shadowIntersection.setMaxDistance(distance);
			//only run once (depth = 1)
			castRay(shadowRay,scene, shadowIntersection);
			//if no intersection, increase color amount
			if(! shadowIntersection.valid()){
				//inverse square law 
				totalColor += (color*light->intensity()/pow(distance,2));
			}
		}
		totalNumSamples += light->numSamples();
	}
	//avg 
	color = color*0.5+(totalColor/totalNumSamples)*0.5;// * totalIntensity/totalNumSamples ;
	//mix shadow and color 50/50
	//color = (totalColor/totalNumSamples);// * totalIntensity/totalNumSamples ;
}
Vec3f RayTracer::refract(const Vec3f &dir, const Vec3f &normal, const double &index){
	//Credit to scratchapixel.com
	double cosi = dir.dot(normal);
	if(cosi < -1) cosi = -1;
	else if(cosi > 1) cosi = 1;
	float etai,etat;
	Vec3f n = normal;
	if (cosi < 0) { 
		cosi = -cosi; 
		etai = 1;
		etat = index;
	} else{ 
		etai = index;
		etat = 1;
		n= -normal; 
	}
	

	float eta = etai / etat;
	float k = 1 - eta * eta * (1 - cosi * cosi);
	return k < 0 ? 0 : ( dir * eta) + n*(eta * cosi - sqrt(k)); 
}

double RayTracer::fresnel(const Vec3f &dir, const Vec3f &normal, const double &index)
{
	double kr = 0;
	double cosi = dir.dot(normal);
	if(cosi < -1) cosi = -1;
	else if(cosi > 1) cosi = 1;

	double etai, etat;
	if (cosi > 0) { 
		etai = index;
		etat = 1;
	}else{
		etai = 1;
		etat = index;

	}
	// Compute sini using Snell's law
	double sint = 1 - cosi * cosi;
	if(sint< 0) sint  = 0;
	sint = etai / etat * sqrt(sint);
	// Total internal reflection
	if (sint >= 1) {
		kr = 1;
	}
	else {
		double cost =  1 - sint * sint;
		if(cost < 0) cost = 0;
		cost = sqrt(cost);
		cosi = fabs(cosi);
		double Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		double Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		kr = (Rs * Rs + Rp * Rp) / 2;
	} 
	return kr;
} 
