#ifndef RENDERABLE_H
#define RENDERABLE_H
//Create a Rendering Engine that will only render 
#include <renderer/Camera.h>
#include <renderer/VertexArray.h>

enum RenderFlags 
{

	Render_None	=0,		//if retruend by update, will not be drawn next frame
	Render_Dirty,		//if returned by update, will be drawn next frame
	Render_Immediate,	//if returned by update, will be drawn immediately
};
//Update gets called each frame (prerender)
class Renderable //inherit by mesh, poitn cloud etc
{
public:
	virtual ~Renderable();
	
	//Call in order
	// load <- if data changes
	//	update	
	//		prerender
	//		render
	//	cleanup
	virtual void load();		
	virtual void update(float delta);
	virtual void preRender() ;
	virtual void render( ) ;
	//Volume * getVolume(); //Volum is an abstract base class as well
private:

	float timestamp;
	bool isDirty;
};

//Create ModelClass that encapsulates a renderable and transforms
//Create RenderNode (volume encapsulated) for OcTree!, maybe add this base by adding an opaque Volume pointer
#endif