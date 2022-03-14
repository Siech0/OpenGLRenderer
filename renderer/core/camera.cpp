#include <renderer/core/camera.hpp>

#include <glm/gtx/quaternion.hpp>

namespace gfx::core
{
	// Camera Base
	Camera::Camera(const glm::vec3& position, const glm::vec3& orientation) noexcept :
		m_position(position),
		m_orientation(orientation)
	{}
	Camera::Camera(const glm::vec3& position, const glm::quat quaternion) noexcept :
		m_position(position),
		m_orientation(quaternion)
	{}

	void Camera::setPosition(const glm::vec3& position) noexcept { m_position = position; }
	void Camera::offsetPosition(const glm::vec3& offset) noexcept { m_position += offset; }
	glm::vec3 Camera::position() const noexcept { return m_position;  }


	void Camera::setOrientation(float yaw, float pitch, float roll) noexcept { setOrientation(glm::vec3(pitch, yaw, roll)); }
	void Camera::setOrientation(const glm::vec3& euler_angles) noexcept { m_orientation = glm::quat(euler_angles); }
	void Camera::setOrientation(const glm::quat& quaternion) noexcept { m_orientation = quaternion; }
	glm::mat4 Camera::orientationMatrix() const noexcept { return glm::mat4_cast(m_orientation); }
	glm::quat Camera::orientation() const noexcept { return m_orientation; }
	glm::vec3 Camera::orientationAngles() const noexcept { return glm::eulerAngles(m_orientation); }
	void Camera::offsetOrientation(const glm::vec3& euler_angles) noexcept
	{
		glm::quat rotation = glm::quat(euler_angles);
		m_orientation = rotation * m_orientation;
	}
	void Camera::rotateYaw(float yaw) noexcept
	{
		glm::quat rotation = glm::angleAxis(yaw, glm::vec3(0.0f, 1.0f, 0.0f));
		m_orientation = rotation * m_orientation;
	}
	void Camera::rotatePitch(float pitch) noexcept
	{
		glm::quat rotation = glm::angleAxis(pitch, glm::vec3(1.0f, 0.0f, 0.0f));
		m_orientation = rotation * m_orientation;
	}
	void Camera::rotateRoll(float roll) noexcept
	{
		glm::quat rotation = glm::angleAxis(roll, glm::vec3(0.0f, 0.0f, 1.0f));
		m_orientation = rotation * m_orientation;
	}
	float Camera::yaw() const noexcept { return glm::yaw(m_orientation); }
	float Camera::pitch() const noexcept { return glm::pitch(m_orientation); }
	float Camera::roll() const noexcept { return glm::roll(m_orientation); }

	glm::vec3 Camera::forward() const noexcept 
	{
		return m_orientation * glm::vec3(0.0f, 0.0f, -1.0f);
	}
	glm::vec3 Camera::up() const noexcept 
	{
		return m_orientation * glm::vec3(0.0f, 1.0f, 0.0f);
	}
	glm::vec3 Camera::right() const noexcept 
	{
		return m_orientation * glm::vec3(1.0f, 0.0f, 0.0f);
	}

	void Camera::lookAt(const glm::vec3 & position) noexcept 
	{
		if (position == m_position)
			return; // Do nothing

		glm::vec3 direction = position - m_position;
		float direction_length = glm::length(direction);	
		if (!(direction_length > 0.0001f))
			return;

		direction /= direction_length;

		if (glm::abs(glm::dot(direction, glm::vec3(0.0f, 0.0f, 0.0f))) > 0.9999f)
			m_orientation = glm::quatLookAt(direction, forward());
		else
			m_orientation = glm::quatLookAt(direction, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::mat4  Camera::viewMatrix() const noexcept 
	{
		return orientationMatrix() * glm::translate(glm::mat4(1.0f), -m_position);
	}


	// Perspective Camera
	PerspectiveCamera::PerspectiveCamera(const glm::vec3& position , const glm::vec3& orientation) noexcept :
		Camera(position, orientation)
	{}
	PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, const glm::quat quaternion) noexcept :
		Camera(position, quaternion)
	{}

	void PerspectiveCamera::setFov(float fov) noexcept { m_fov = fov; }
	float PerspectiveCamera::fov() const noexcept { return m_fov; }

	void PerspectiveCamera::setAspect(float width, float height) noexcept { setAspect(width / height); }
	void PerspectiveCamera::setAspect(float aspect) noexcept { m_aspect = aspect; }
	float PerspectiveCamera::aspect() const noexcept { return m_aspect; }

	void PerspectiveCamera::setNear(float near) noexcept { m_near = near; };
	float PerspectiveCamera::near() const noexcept { return m_near; }

	void PerspectiveCamera::setFar(float far) noexcept { m_far = far; }
	float PerspectiveCamera::far() const noexcept { return m_far; }


	glm::mat4 PerspectiveCamera::projectionMatrix() const noexcept { return glm::perspective(m_fov, m_aspect, m_near, m_far);}

	// Ortholinear Camera
	OrthoCamera::OrthoCamera(const glm::vec3& position, const glm::vec3& orientation) noexcept :
		Camera(position, orientation)
	{}
	OrthoCamera::OrthoCamera::OrthoCamera(const glm::vec3& position, const glm::quat quaternion) noexcept :
		Camera(position, quaternion)
	{}

	void OrthoCamera::setXMin(float xmin) noexcept { m_xmin = xmin; }
	float OrthoCamera::xmin() const noexcept { return m_xmin; }

	void OrthoCamera::setYMin(float ymin) noexcept { m_ymin = ymin; }
	float OrthoCamera::ymin() const noexcept { return m_ymin; }

	void OrthoCamera::setXMax(float xmax) noexcept { m_xmax = xmax; }
	float OrthoCamera::xmax() const noexcept { return m_xmax; }

	void OrthoCamera::setYMax(float ymax) noexcept { m_ymax = ymax; }
	float OrthoCamera::ymax() const noexcept { return m_ymax; }

	glm::mat4 OrthoCamera::projectionMatrix() const noexcept { return glm::ortho(m_xmin, m_xmax, m_ymin, m_ymax); }
}