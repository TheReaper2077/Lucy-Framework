#pragma once

#include "../define.h"
#include "../OpenGL/OpenGL.h"

namespace lf {

	enum CameraMode {
		ORTHOGRAPHIC,
		PERSPECTIVE
	};

	struct Camera {
		glm::vec3 Up;
		glm::vec3 WorldUp;
		glm::vec3 Front;
		glm::vec3 Position;
		glm::vec3 Right;

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;

		CameraMode mode;

		UniformBuffer *ubo;
		
		bool first_mouse = true;
		double speed = 0.05;
		float yaw = -90.0, pitch = 0;
		float lastX = WIDTH/2, lastY = HEIGHT/2;
		float zoom = 0.001;
	};
	
	void EnableCamera(std::string name);

	void UpdateCamera();
	void CameraMouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	void CameraKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
}