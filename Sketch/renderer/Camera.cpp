#include <renderer/Camera.h>
//default vertex attribute names

void Camera::bind()
{
	Shader::current()->setUniformMat4(Shader::Uniform_Projection, _projection);
	Shader::current()->setUniformMat4(Shader::Uniform_View, _view);
	Shader::current()->setUniformVec3(Shader::Uniform_Eye, _pos );
}

PerspectiveCamera::PerspectiveCamera(float res, Vec3 pos, Vec3 dir, Vec3 up, float near, float far)
	:Camera(pos, dir, up)
{
	_near = near;
	_far = far;
	Camera::setProjection(glm::perspective(glm::radians(90.0f), res, _near,_far));

}

