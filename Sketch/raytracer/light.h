#ifndef LIGHT_HPP
#define LIGHT_HPP
#include "rng.h"
#include "color.h"
class Light{
protected:
	int _numSamples; //number of shadow ray samples to generate
	double _intensity;
	Vec3f _pos;
	//intensities
	Color _color;
public:
	Light(
		const Vec3f & position,
		const Color & color,
		const double & intensity,
		int numSamples);
	virtual ~Light();
	virtual Ray3f makeShadowRay(const Vec3f & poi,double & distance);
	const double &  intensity();
	int numSamples();
	const Vec3f & position();
	const Color & color();
};

//light is a single point in space, simplest representation
//default only single sample
class PointLight: public Light{
public:
	PointLight(
		const Vec3f & position,
		const Color & color,
		const double & intensity);
	Ray3f makeShadowRay(const Vec3f & poi, double & distance);
};


//light is a rectangle in space, used to emulate soft shadow effects
class RectangleLight: public Light{
	/*		----------
			|	.pos | h
			|		 |
			----------
				w
	*/
private:
	RNG _rng;///random number generator
	Vec3f _up, _right; //up and right, back 
	double _width, _depth, _area;
public:
	RectangleLight( 
		const Vec3f & position,	
		const Vec3f & normal,	
		const Vec3f & right,
		const Color & color,
		const double & intensity,
		const double & width, 
		const double & depth,
		int numSamples);
	//returns a random ray from the rectangle sample space
	Ray3f makeShadowRay(const Vec3f & poi, double & distance);
};


#endif	//LIGHT_HPP