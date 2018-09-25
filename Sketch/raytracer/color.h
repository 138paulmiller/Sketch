#ifndef COLOR_H
#define COLOR_H

#include <fstream>
#include <iostream>
#include "lamath.h"
#define RGB_DEPTH 255

using namespace lamath;

//Each color is HDR
class Color : public Vec3f
{
	//Inherit vec to allow for color arithmetic
public:
	Color(double  r = 0, double g = 0, double b = 0)
		:Vec3f({ r,g,b }) {}

	Color(const Color & other)
		:Vec3f({ other.r(),other.g(),other.b() }) {}

	Color(const Vec3f & other)
		:Vec3f(other) {}

	inline double& r() { return (*this)[0]; }
	inline double& g() { return (*this)[1]; }
	inline double& b() { return (*this)[2]; }
	inline const double& r()const { return (*this)[0]; }
	inline const double& g()const { return (*this)[1]; }
	inline const double& b()const { return (*this)[2]; }


	inline void set(double r, double g, double b) {
		(*this)[0] = r; (*this)[1] = g; (*this)[2] = b;
	}

	inline void clamp(const double & max) {
		if ((*this)[0] > max)(*this)[0] = max;
		if ((*this)[1] > max)(*this)[1] = max;
		if ((*this)[2] > max)(*this)[2] = max;
	}

	//bytes must be initialized prior!
	static void makeBytes(const Color & color, char *bytes)
	{
		bytes[0] = color[0] * RGB_DEPTH;
		bytes[1] = color[1] * RGB_DEPTH;
		bytes[2] = color[2] * RGB_DEPTH;
	}

};
#endif COLOR_H