#ifndef SHADER_H
#define SHADER_H
#include "image.h"
#include "camera.h"
#include "scene.h"

class Shader{
protected:
	Color _globalLight;
public:
	Shader():_globalLight(1){}
	inline void setGlobalLight(Color globalLight){_globalLight = globalLight;}
	//assumes shade is called on a valid intersection
	virtual void shade( Color & color, 
						const Camera& camera, const Scene& scene, 
						const Intersection & intersection,
						const Material * material)=0;
};

class FlatShader : public Shader{
public:
	void shade(Color & color, 
				const Camera& camera, 
				const Scene& scene, 
				const Intersection & intersection,
				const Material * material);
};

class BlinnPhongShader : public Shader{
public:
	void shade(Color & color, 
				const Camera& camera, 
				const Scene& scene, 
				const Intersection & intersection,
				const Material * material);
};



#endif