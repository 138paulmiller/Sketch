#include "camera.h"

Camera::Camera(Vec3f eye, Vec3f up, Vec3f dir){
  _eye = eye;
  _w = -dir.normal();
  _u = up.cross(_w).normal();
  _v = _w.cross(_u);
}


const Vec3f & Camera::eye()const{
	return _eye;
}
const Vec3f & Camera::u()const{
	return _u;
}
const Vec3f & Camera::v()const{
	return _v;
}
const Vec3f & Camera::w()const{
	return _w;
}

Viewport::Viewport(	int xResolution, int yResolution, 
					double left, double right, double top, double bottom)
	:_left(left), _right(right), _top(top), _bottom(bottom),
	 _xResolution(xResolution), _yResolution(yResolution){
}

void Viewport::uv(double& u, double& v, int i, int j){
	u=_left+(_right -_left)*(i + 0.5)/_xResolution;
	v=_bottom+(_top - _bottom)*(j + 0.5)/_yResolution;
}

void OrthographicProjection::getViewRay(Ray3f &viewRay, const Camera& camera, double u, double v) const{
	viewRay.setOrigin(camera.eye() + camera.u()*u + camera.v()*v);
	viewRay.setDirection(-camera.w());

}

PerspectiveProjection::PerspectiveProjection(double focalLength)
	:_focalLength(focalLength){}

void PerspectiveProjection::getViewRay(Ray3f &viewRay,const Camera& camera, double u, double v) const{
	viewRay.setOrigin(camera.eye());
	viewRay.setDirection((-camera.w() * _focalLength + camera.u()*u + camera.v()*v).normal() ) ;
}
