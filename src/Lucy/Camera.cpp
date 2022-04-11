#include "Lucy.h"

extern std::shared_ptr<lf::Lucy> lf_context;

lf::Camera* lf::CreateCamera(std::string name, ProjectionMode mode) {
	assert(lf_context != nullptr);

	LF_DISABLE_ASSERT(mode != lf::PERSPECTIVE);

	auto camera = std::make_shared<lf::Camera>();

	if (mode == lf::ORTHOGRAPHIC) {
		camera->projection = glm::ortho<float>(-WIDTH/2, WIDTH/2, HEIGHT/2, -HEIGHT/2, -1000, 1000);
		camera->view = glm::mat4(1.0f);
		camera->model = glm::mat4(1.0f);
		camera->speed = 5.0f;
	}
	if (mode == lf::PERSPECTIVE) {
		camera->projection = glm::perspective(glm::radians(45.0f), (float)WIDTH/HEIGHT, 0.001f, 1000.0f);
		camera->view = glm::mat4(1.0f);
		camera->model = glm::mat4(1.0f);
		camera->speed = 0.05f;
	}

	camera->mode = mode;
	camera->name = name;

	lf_context->camera_map[name] = camera;

	return camera.get();
}

void lf::CameraView(const Vec3 &mag) {
	assert(lf_context->camera != nullptr);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(mag.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(mag.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(mag.z), glm::vec3(0, 0, 1));

	lf_context->camera->model = model;
}

lf::Camera* lf::GetCamera(std::string name) {
	assert(lf_context != nullptr);

	return lf_context->camera_map[name].get();
}

void lf::EnableCamera(std::string name) {
	assert(lf_context != nullptr);

	lf_context->camera = lf_context->camera_map[name].get();
}


void CameraMouseCallback() {
	if (lf_context->camera == nullptr) return;

	float xpos = lf::GetMousePosX();
	float ypos = lf::GetMousePosY();

	auto* camera = lf_context->camera;

	if (!lf_context->camera->mouse_enabled) {
		camera->first_mouse = true;
		return;
	};

	if (camera->mode == lf::ProjectionMode::PERSPECTIVE) {
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

		camera->yaw += xoffset;
		camera->pitch += yoffset;

		if (camera->pitch > 89.0f)
			camera->pitch = 89.0f;
		if (camera->pitch < -89.0f)
			camera->pitch = -89.0f;

		camera->Front.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
		camera->Front.y = sin(glm::radians(camera->pitch));
		camera->Front.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));

		camera->Front = glm::normalize(camera->Front);
		camera->Right = glm::normalize(glm::cross(camera->Front, camera->WorldUp));
        camera->Up = glm::normalize(glm::cross(camera->Right, camera->Front));
	}
}

void lf::CameraUpdate() {
	assert(lf_context->camera != nullptr);
	
	auto* camera = lf_context->camera;
	
	float speed = (float)camera->speed*lf_context->dt;

	CameraMouseCallback();

	if (camera->mode == lf::PERSPECTIVE) {
		if (!lf_context->camera->keyboard_enabled) return;

		if (lf::IsKeyPressed(GLFW_KEY_W)) {
			camera->Position += camera->Front * speed;
		}
		if (lf::IsKeyPressed(GLFW_KEY_S)) {
			camera->Position -= camera->Front * speed;
		}
		if (lf::IsKeyPressed(GLFW_KEY_A)) {
			camera->Position -= glm::normalize(glm::cross(camera->Front, camera->Up)) * speed;
		}
		if (lf::IsKeyPressed(GLFW_KEY_D)) {
			camera->Position += glm::normalize(glm::cross(camera->Front, camera->Up)) * speed;
		}
		if (lf::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
			camera->Position -= camera->Up * speed;
		}
		if (lf::IsKeyPressed(GLFW_KEY_SPACE)) {
			camera->Position += camera->Up * speed;
		}

		camera->view = glm::lookAt(camera->Position, camera->Position + camera->Front, camera->Up);
	}

	if (camera->mode == lf::ORTHOGRAPHIC) {	
		if (!lf_context->camera->keyboard_enabled) return;

		// if (lf::IsKeyPressed(GLFW_KEY_W)) {
		// 	camera->Position.y -= speed;
		// }
		// if (lf::IsKeyPressed(GLFW_KEY_S)) {
		// 	camera->Position.y += speed;
		// }
		// if (lf::IsKeyPressed(GLFW_KEY_A)) {
		// 	camera->Position.x -= speed;
		// }
		// if (lf::IsKeyPressed(GLFW_KEY_D)) {
		// 	camera->Position.x += speed;
		// }

		camera->view = glm::translate(glm::mat4(1.0f), glm::vec3(camera->Position.x, camera->Position.y, 0));
	}
}