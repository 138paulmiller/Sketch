#ifndef ARGS_HPP
#define ARGS_HPP
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iostream>

//args - used to parse C++ cmd line arguments in the format 
//	program -flag arg1 -l 1,2,3,4,5 
#define DEFAULT_INT 0
#define DEFAULT_FLOAT 0.0
#define DEFAULT_STRING ""
#define DEFAULT_DELIM ','

class Args{
private:

	using ArgIt = std::unordered_map<std::string, std::string>::iterator; 
	std::unordered_map<std::string, std::string> _argmap;

public:
	Args(int argc, char ** argv);
	~Args();
	// if argument cannot be parse, value=DEFAULT will be returned
	long getInt(std::string key, long value = DEFAULT_INT);
	double getFloat(std::string key, double value = DEFAULT_FLOAT);
	std::string getString(std::string key, std::string value = DEFAULT_STRING);

	void getInts(std::vector<int> & vec, std::string key, char delim=DEFAULT_DELIM);
	void getFloats(std::vector<float> & vec, std::string key, char delim=DEFAULT_DELIM);
	void getStrings(std::vector<std::string> & vec, std::string key, char delim=DEFAULT_DELIM);
};


#endif