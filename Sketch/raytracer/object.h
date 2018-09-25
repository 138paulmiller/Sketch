#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <limits>
#include "lamath.h"
#include "color.h"

using namespace lamath;
class Object;
class Material;
class Intersection;

enum MaterialType{
	NONE=0,
	DIELECTRIC, 		//transparent
	NONDIELECTRIC 		//nontransparent
};	

/*************************************** Material *******************************************/
struct Material{
	//Box for object material coefficients and colors
	// Color base;//surface color
	// Color emission;//color emitted
	//blinn-phong-phong coeff
	MaterialType type;
	Color ambient;
	Material(const Color & ambient, const MaterialType &type=NONE)
		:ambient(ambient), type(type){}
	virtual ~Material(){}
};

struct DielectricMaterial: public Material{
	double refractionIndex;
	DielectricMaterial(	const Color & base, const double & refractionIndex):
	Material(ambient, DIELECTRIC),	
	refractionIndex(refractionIndex){}
};

struct NonDielectricMaterial: public Material{
// For material blinn-phong coefficients see 
//	http://devernay.free.fr/cours/opengl/materials.html
	//Box for object material coefficients and colors
	// Color base;//surface color
	// Color emission;//color emitted
	//blinn-phong-phong coeff
	Color diffuse;
	Color specular;
	double shininess;
	double reflectivity;

	NonDielectricMaterial(	
		const Color & ambient, 	const Color & diffuse,	const Color & specular,	
		const double & shininess, const double & reflectivity):
	Material(ambient, NONDIELECTRIC),
	diffuse(diffuse), specular(specular),	
	shininess(shininess), reflectivity(reflectivity){}
};





/*************************************** Object *******************************************/
class Object{
private:
	Material* _material; //only reference, dow not delete
public:
	Object(Material * material=nullptr):_material(material) {}
	virtual ~Object(){}
	inline const Material * material() const 	{return _material;}
	//to be overriden
	virtual void checkIntersection(const Ray3f & viewRay, Intersection & intersection){}
};

/*************************************** Intersection *******************************************/
class Intersection{
	//encapsulates object intersection
private:
	double _distance; //distance, only updated when closer object intersects 
	Vec3f _poi; //opoint of intersection 
	Vec3f _normal; //opoint of intersection 
	const Object * _object; //only reference, will not delete 
	const Object * _ignoreObject; //ignores intersections with this object (used to prevent self intersection) 
public:
	Intersection();
	//checks if new intersection 
	void update(const Object * object, const Vec3f & poi, const Vec3f & normal, double distance);
	void setMaxDistance(double maxDistance);
	void setIgnoreObject(const Object * object);
	double distance();				
	Vec3f poi()const;
	Vec3f normal()const; 		
	const Material* material()const;	
	const Object* object()const;
	bool valid()const;
	void reset();
};


#endif //OBJECT_HPP