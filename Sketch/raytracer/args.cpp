#include "args.h"

Args::Args(int argc, char ** argv){
	//parse all strings as -key value
	//ignore first arg
	for(int i = 1; i+1 < argc; i+=2){
		_argmap[argv[i]] = argv[i+1];
	}
}

Args::~Args(){
}

long Args::getInt(std::string key, long value){
	ArgIt it = _argmap.find(key);
	return (it == _argmap.end()) ? value : std::stoi(it->second);
}
double Args::getFloat(std::string key, double value){
	ArgIt it = _argmap.find(key);
	return (it == _argmap.end()) ? value : std::stof(it->second);
}

std::string Args::getString(std::string key, std::string value){
	ArgIt it = _argmap.find(key);
	return (it == _argmap.end()) ? value : it->second;
}

void Args::getInts(std::vector<int> & vec, std::string key, char delim){
	vec.clear();
	ArgIt it = _argmap.find(key);
	std::string str;
	if(it != _argmap.end()){
		std::stringstream ss(it->second);
		while( std::getline(ss, str, delim) ){
			vec.push_back(std::stoi(str));
		}
	}
}

void Args::getFloats(std::vector<float> & vec, std::string key, char delim){
	vec.clear();
	ArgIt it = _argmap.find(key);
	std::string str;
	if(it != _argmap.end()){
		std::stringstream ss(it->second);
		while( std::getline(ss, str, delim) ){
			vec.push_back(std::stof(str));
		}
	}
}

void Args::getStrings(std::vector<std::string> & vec, std::string key, char delim){
	vec.clear();
	ArgIt it = _argmap.find(key);
	std::string str;
	if(it != _argmap.end()){
		std::stringstream ss(it->second);
		while( std::getline(ss, str, delim) ){
			vec.push_back(str);
		}
	}
}
