
#include "primitives.h"

/************************************* Sphere *****************************/
Sphere::Sphere(const Vec3f & center, double radius, Material * material)
	:Object(material),
	_center(center),
	_radius (radius){
	_radius2 = pow(radius, 2);
}

Sphere::~Sphere(){
}

void Sphere::checkIntersection(const Ray3f & viewRay, Intersection & intersection){
	float t, t0, t1; 
	Vec3f look = _center - viewRay.origin();
	float tca = look.dot(viewRay.direction());
	// if (tca < 0) return false;
	float d = look.dot(look) - tca * tca;
	if (d > _radius2) 
		return;
	float thc = sqrt(_radius2 - d);
	t0 = tca - thc;
	t1 = tca + thc;
	t =  t0 < t1? t0 : t1;
	if (t < 0) {
		t = t1; // if t0 is negative, let's use t1 instead
		if (t < 0) 
			return; // both t0 and t1 are negative
	}
	//set poi and normal
	Vec3f poi = viewRay.point(t);
	Vec3f normal = (poi-_center).normal();
	intersection.update(this, poi, normal, t); 
}

/************************************* Plane *****************************/
Plane::Plane(const Vec3f & normal, const Vec3f & point, Material* material)
	:Object(material),
	_normal(normal),
	_point(point){

}
Plane::~Plane(){

}

void Plane::checkIntersection(const Ray3f & viewRay, Intersection & intersection){
	//if the dot product between the normal less than or equal to 0, then eye views at or under plane 
	double look_proj = _normal.dot(viewRay.direction());
	if(almost_equal(look_proj,0.0))
		return; //no intersection
	
	Vec3f l = _point - viewRay.origin();
	double t  = _normal.dot(l) / look_proj;
	if(t < 0.0) return;
	Vec3f poi = viewRay.point(t);
	intersection.update(this, poi, _normal, t); 
	
}