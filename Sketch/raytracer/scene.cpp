#include "scene.h"

Scene::Scene(){
	
}

void Scene::addLight(std::shared_ptr<Light>  light){
	_lights.push_back(light);
}

void Scene::addObject(std::shared_ptr<Object> object){
	_objects.push_back(object);
}
