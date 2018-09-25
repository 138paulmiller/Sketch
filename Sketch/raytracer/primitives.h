#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include "object.h"

class Sphere : public Object{
private:
	Vec3f _center;
	double _radius;
	double _radius2; //squared 
public:
	Sphere(const Vec3f & center, double radius, Material* material);
	~Sphere();
	void checkIntersection(const Ray3f & viewRay, Intersection & intersection);

};


class Plane : public Object{
private:
	Vec3f _normal;	//facing direction
	Vec3f _point; //point laying on the plane 
public:
	Plane(const Vec3f & normal, const Vec3f & point, Material* material);
	~Plane();
	void checkIntersection(const Ray3f & viewRay, Intersection & intersection);

};


#endif //PRIMITIVES_HPP

