#ifndef RNG_HPP
#define RNG_HPP
#include <random>
typedef std::mt19937 rng_type;

class RNG{
private:
	std::uniform_real_distribution<double> dist;
	std::random_device device;          
	std::mt19937 engine;  
public:
	RNG(double lowerBound, double upperBound)
		:dist(lowerBound, upperBound),engine(device()){
	}

	inline double random(){
		return dist(engine);
	}

};
#endif