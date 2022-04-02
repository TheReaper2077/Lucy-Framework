#include "../define.h"
#include "Camera.h"
#include "Lucy.h"

extern std::shared_ptr<lf::Context> rendercontext;

void lf::EnableCamera(std::string name) {
	assert(rendercontext != nullptr);

	rendercontext->camera = rendercontext->camera_store_map[name].get();
}

void lf::UpdateCamera() {
	assert(rendercontext->camera != nullptr);
	
	lf::SetModel(rendercontext->camera->model);
	lf::SetView(rendercontext->camera->view);
	lf::SetProjection(rendercontext->camera->model);
}

void lf::CameraMouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	if (rendercontext->camera == nullptr) return;

	auto* camera = rendercontext->camera;

	if (camera->first_mouse) {
		camera->lastX = xpos;
		camera->lastY = ypos;
		camera->first_mouse = false;
	}

    float xoffset = xpos - camera->lastX;
    float yoffset = camera->lastY - ypos;
    camera->lastX = xpos;
    camera->lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera->yaw   += xoffset;
    camera->pitch += yoffset;

    if (camera->pitch > 89.0f)
        camera->pitch = 89.0f;
    if (camera->pitch < -89.0f)
        camera->pitch = -89.0f;

    camera->Front.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
    camera->Front.y = sin(glm::radians(camera->pitch));
    camera->Front.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));

	camera->Front = glm::normalize(camera->Front);
}

void lf::CameraKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (rendercontext->camera == nullptr) return;
	
	auto* camera = rendercontext->camera;
	
	if (camera->mode == PERSPECTIVE) {
		float speed = camera->speed*rendercontext->dt;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera->Position += camera->Front * speed;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera->Position -= camera->Front * speed;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera->Position -= glm::normalize(glm::cross(camera->Front, camera->Up)) * speed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera->Position += glm::normalize(glm::cross(camera->Front, camera->Up)) * speed;
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera->Position -= camera->Up * speed;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			camera->Position += camera->Up * speed;

		camera->view = glm::lookAt(camera->Position, camera->Position + camera->Front, camera->Up);
	}

	if (camera->mode == ORTHOGRAPHIC) {	
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera->Position.y -= rendercontext->dt*5;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera->Position.y += rendercontext->dt*5;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera->Position.x -= rendercontext->dt*5;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera->Position.x += rendercontext->dt*5;

		camera->view = glm::translate(glm::mat4(1.0f), glm::vec3(camera->Position.x, camera->Position.y, 0));
	}
}
