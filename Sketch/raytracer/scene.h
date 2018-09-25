#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "object.h"
#include "light.h"


//base object represents
class Scene{
public:
	Scene();
	void addLight(std::shared_ptr<Light>  light);
	void addObject(std::shared_ptr<Object>  object);

	inline const std::vector<std::shared_ptr<Object> > & objects() const {return _objects;}
	inline const std::vector<std::shared_ptr<Light> > & lights()const  {return _lights;}

private:
	std::vector<std::shared_ptr<Object> >  _objects;
	std::vector<std::shared_ptr<Light> >  _lights;
};



#endif