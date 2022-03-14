#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace gfx::core
{
	class Camera
	{
	public:
		Camera(const glm::vec3& position = { 0.0f, 0.0f, 0.0f }, const glm::vec3& orientation = { 0.0, 0.0, 0.0 }) noexcept;
		Camera(const glm::vec3& position, const glm::quat quaternion) noexcept;

		Camera(const Camera& other) = default;
		Camera(Camera&& other) = default;

		Camera& operator=(const Camera & other) = default;
		Camera& operator=(Camera && other) = default;

		void setPosition(const glm::vec3& position) noexcept;
		void offsetPosition(const glm::vec3& offset) noexcept;
		glm::vec3 position() const noexcept;

		void setOrientation(float yaw, float pitch, float roll = 0.0f) noexcept;
		void setOrientation(const glm::vec3& euler_angles) noexcept;
		void setOrientation(const glm::quat& quaternion) noexcept;
		glm::mat4 orientationMatrix() const noexcept;
		glm::quat orientation() const noexcept;
		glm::vec3 orientationAngles() const noexcept;
		void offsetOrientation(const glm::vec3& euler_angles) noexcept;
		void rotateYaw(float yaw) noexcept;
		void rotatePitch(float pitch) noexcept;
		void rotateRoll(float roll) noexcept;
		float yaw() const noexcept;
		float pitch() const noexcept;
		float roll() const noexcept;

		glm::vec3 forward() const noexcept;
		glm::vec3 up() const noexcept;
		glm::vec3 right() const noexcept;

		void lookAt(const glm::vec3& position) noexcept;
		glm::mat4 viewMatrix() const noexcept;

	private:
		glm::vec3 m_position;
		glm::quat m_orientation;
	};

	class PerspectiveCamera final : public Camera
	{
	public:
		PerspectiveCamera(const glm::vec3& position = {0.0f, 0.0f, 0.0f}, const glm::vec3& orientation = {0.0, 0.0, 0.0}) noexcept;
		PerspectiveCamera(const glm::vec3& position, const glm::quat quaternion) noexcept;

		PerspectiveCamera(const PerspectiveCamera& other) = default;
		PerspectiveCamera(PerspectiveCamera&& other) = default;

		PerspectiveCamera& operator=(const PerspectiveCamera& other) = default;
		PerspectiveCamera& operator=(PerspectiveCamera&& other) = default;

		void setFov(float fov) noexcept;
		float fov() const noexcept;

		void setAspect(float width, float height) noexcept;
		void setAspect(float aspect) noexcept;
		float aspect() const noexcept;

		void setNear(float near) noexcept;
		float near() const noexcept;

		void setFar(float far) noexcept;
		float far() const noexcept;

		glm::mat4 projectionMatrix() const noexcept;

	private:

		float m_aspect = 16.0f / 9.0f;
		float m_near = 1.0f, m_far = 100.0f;
		float m_fov = 9.0f;
	};

	class OrthoCamera final : public Camera
	{
	public:
		OrthoCamera(const glm::vec3& position = { 0.0f, 0.0f, 0.0f }, const glm::vec3& orientation = { 0.0, 0.0, 0.0 }) noexcept;
		OrthoCamera(const glm::vec3& position, const glm::quat quaternion) noexcept;

		OrthoCamera(const OrthoCamera& other) = default;
		OrthoCamera(OrthoCamera && other) = default;

		OrthoCamera& operator=(const OrthoCamera & other) = default;
		OrthoCamera& operator=(OrthoCamera && other) = default;

		void setXMin(float xmin) noexcept;
		float xmin() const noexcept;

		void setYMin(float ymin) noexcept;
		float ymin() const noexcept;

		void setXMax(float xmax) noexcept;
		float xmax() const noexcept;

		void setYMax(float ymax) noexcept;
		float ymax() const noexcept;

		glm::mat4 projectionMatrix() const noexcept;

	private:

		float m_xmin = 0.0f, m_xmax = 0.0f, m_ymin = 1920.0f, m_ymax = 1080.0f;
	};
}