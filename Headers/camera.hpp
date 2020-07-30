#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		perspective = glm::perspective(fov, aspect, zNear, zFar);
		position = pos;
		forward = glm::vec3(0,0,1);
		up = glm::vec3(0,1,0);
	}

	inline glm::mat4 getViewProjection() const
	{
		return perspective * glm::lookAt(position, position + forward, up);
	}
private:
	glm::mat4 perspective;
	glm::vec3 position, forward, up;
};



#endif
