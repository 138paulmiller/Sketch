#ifndef CAMERA_H
#define CAMERA_H


#include <renderer/Shader.h>





class Camera
{
public:
	Camera(
		const Vec3 & pos, 
		const Vec3 &dir, 
		const Vec3 & up)
		:
		_pos	(pos),
		_dir	(dir),
		_up		(up	),
		_view	(lookAt(_pos, pos + dir, up)){}
	virtual ~Camera() {}

	inline void setTarget	(const Vec3 & target)
		{	_dir = target-_pos; _view = lookAt(_pos, target, _up);	}
		
	inline void setPos		(const Vec3&  pos)
		{	_pos = pos;	_view = lookAt(_pos, _pos + _dir, _up);}



	inline  const Mat4 & getView()			const	{ return _view; }
	inline  const Mat4 & getProjection()	const	{ return _projection; }
	inline  const Vec3 & getPos()			const	{ return _pos; }
	inline  const Vec3 & getDirection()		const { return _dir; }
	inline  const Vec3 & getRight()			const	{ return cross(_up, _pos); }
	inline  const Vec3 & getUp()			const	{ return _up; }

	void bind();



protected:
	inline void setProjection(const Mat4 & projection) 
		{	_projection = projection;	}

private:

	//position of camera in space
	Vec3 _pos;
	//direction to look
	Vec3 _dir;
	//vector pointing up
	Vec3 _up;
	//view transform, camera to scene 
	Mat4 _view;
	//Projection transform
	Mat4 _projection;

};
//Create base camera class
class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(
		float res, 
		Vec3 pos, Vec3 dir, Vec3 up,

		float near = 0.1,
		float far = 100000);

	~PerspectiveCamera() {}

private:
	//near and far planes
	float _near, _far;

};


#endif
