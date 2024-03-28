#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

enum Camera_Movement
{
	FORWARD, BACKWARD, LEFT, RIGHT
};

// 默认相机值
const float YAW = -90.0f;		// 偏航角
const float PITCH = 0.0f;		// 俯仰角
const float SPEED = 2.5f;		// 速度
const float SENSITIVITY = 0.05f;	// 精准度
const float ZOOM = 45.0f;		// 缩放视角fov

class Camera
{
private:
	// 相机属性
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	// 欧拉角
	float m_Yaw;
	float m_Pitch;

	float m_MovementSpeed;
	float m_MouseSensitivity;
	float m_Zoom;

public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) :
		m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch),
		m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM),
		m_Front(glm::vec3(0.0f, 0.0f, -1.0f))
	{
		updateCameraVectors();
	}

	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
		m_Position(glm::vec3(posX, posY, posZ)),
		m_WorldUp(glm::vec3(upX, upY, upZ)),
		m_Yaw(yaw), m_Pitch(pitch),
		m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM),
		m_Front(glm::vec3(0.0f, 0.0f, -1.0f))
	{
		updateCameraVectors();
	}

	void UpdatePosition(Camera_Movement direction, float deltaTime);

	void ProcessMouseScroll(float yoffset);

	void UpdateCameraYawAndPitch(float xoffset, float yoffset);

	glm::mat4 GetViewMatrix() const;

	glm::vec3 GetPosition() const { return m_Position; }
	glm::vec3 GetFront() const { return m_Front; }
	glm::vec3 GetUp() const { return m_Up; }
	float GetYaw() const { return m_Yaw; }
	float GetPitch() const { return m_Pitch; }
	float GetZoom() const { return m_Zoom; }

private:
	void updateCameraVectors()
	{
		// calculate the new Front vector
		glm::vec3 front{};
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);
		// also re-calculate the Right and Up vector
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
};

