#include "light.h"

Light::Light(const Vec3f & position, const Color & color, const double & intensity, int numSamples)
:_pos(position), _color(color),_intensity(intensity),_numSamples(numSamples){
}

Light::~Light(){

}


Ray3f Light::makeShadowRay(const Vec3f & poi, double & distance){
	return{};
}

int Light::numSamples(){
	return _numSamples;
}

const Vec3f & Light::position(){
	return _pos;
}

const Color & Light::color(){
	return _color;
}
const double & Light::intensity(){
	return _intensity;
}


PointLight::PointLight(
	const Vec3f & position,
	const Color & color,
	const double & intensity)
	:Light(position,color,intensity, 1)
	{}



Ray3f PointLight::makeShadowRay(const Vec3f & poi, double & distance){
	Vec3f dir = (_pos - poi).normal();
	Vec3f origin = poi+dir*epsilon;
	distance = (_pos-poi).magnitude();

	//set the intersection distance to be between poi and light
	//poi may lay right on surface so will always intersect, move by epsilon toward light
	return Ray3f(origin,  dir);
}


RectangleLight::RectangleLight(
	const Vec3f & position,
	const Vec3f & normal,
	const Vec3f & right,
	const Color & color,
	const double & intensity,
	const double & width, 
	const double & depth,
	int numSamples)
	:Light(position,color, intensity, numSamples),
	_rng(-1,1){
		_width = width;
		_depth = depth;
		_area = width*depth;
		_right = right.normal();
		_up = normal.normal().cross(right);
}



Ray3f RectangleLight::makeShadowRay(const Vec3f & poi, double & distance){
	//offset pos
	Vec3f pos = _pos;
	//move 
	pos += _up * (_rng.random()*(_width/2.0)); 
	pos += _right * (_rng.random()*(_depth/2.0)); 
	distance = (pos-poi).magnitude();

	Vec3f dir = (pos - poi).normal();
	Vec3f origin = poi+dir;
	//set the intersection distance to be between poi and light
	//poi may lay right on surface so will always intersect, move by epsilon toward light

	return Ray3f(origin,  dir);
}

