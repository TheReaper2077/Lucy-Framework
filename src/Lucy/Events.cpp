#include "Lucy.h"

extern std::shared_ptr<lf::Lucy> lf_context;

void lf::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	assert(lf_context->event != nullptr);

	if (lf_context->event->key_state[key] == GLFW_RELEASE && action == GLFW_PRESS) {
		lf_context->event->key_toggled[key] = !lf_context->event->key_toggled[key];
	}
	lf_context->event->key_state[key] = action;
}

bool lf::IsKeyPressed(int key) {
	assert(lf_context->event != nullptr);

	return (lf_context->event->key_state[key] == GLFW_PRESS || lf_context->event->key_state[key] == GLFW_REPEAT);
}

bool lf::IsKeyReleased(int key) {
	assert(lf_context->event != nullptr);

	return (lf_context->event->key_state[key] == GLFW_RELEASE);
}

bool lf::IsKeyTyping(int key) {
	assert(lf_context->event != nullptr);

	return (lf_context->event->key_state[key] == GLFW_REPEAT);
}

bool lf::IsKeyToggled(int key) {
	assert(lf_context->event != nullptr);

	return lf_context->event->key_toggled[key];
}

void lf::MouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	assert(lf_context->event != nullptr);

	lf_context->event->xpos = xpos;
	lf_context->event->ypos = ypos;
}

void lf::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	assert(lf_context->event != nullptr);

	if (lf_context->event->button_state[button] == GLFW_RELEASE && action == GLFW_PRESS) {
		lf_context->event->button_toggled[button] = !lf_context->event->button_toggled[button];
	}
	lf_context->event->button_state[button] = action;
}

bool lf::IsMousePressed(int button) {
	assert(lf_context->event != nullptr);

	return (lf_context->event->button_state[button] == GLFW_PRESS);
}

bool lf::IsMouseReleased(int button) {
	assert(lf_context->event != nullptr);

	return (lf_context->event->button_state[button] == GLFW_RELEASE);
}

bool lf::IsMouseToggled(int button) {
	assert(lf_context->event != nullptr);

	return (lf_context->event->button_toggled[button]);
}

double lf::GetMousePosX() {
	assert(lf_context->event != nullptr);

	return lf_context->event->xpos;
}

double lf::GetMousePosY() {
	assert(lf_context->event != nullptr);

	return lf_context->event->ypos;
}
