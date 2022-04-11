#include "Lucy.h"

extern std::shared_ptr<lf::Lucy> lf_context;

void lf::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	LF_ASSERT(lf_context->event != nullptr);

	if (lf_context->event->key_state[key] == LF_RELEASE && action == LF_PRESS) {
		lf_context->event->key_toggled[key] = !lf_context->event->key_toggled[key];
	}
	lf_context->event->key_state[key] = action;
}

bool lf::IsKeyPressed(int key) {
	LF_ASSERT(lf_context->event != nullptr);

	return (lf_context->event->key_state[key] == LF_PRESS || lf_context->event->key_state[key] == LF_REPEAT);
}

bool lf::IsKeyReleased(int key) {
	LF_ASSERT(lf_context->event != nullptr);

	return (lf_context->event->key_state[key] == LF_RELEASE);
}

bool lf::IsKeyTyping(int key) {
	LF_ASSERT(lf_context->event != nullptr);

	return (lf_context->event->key_state[key] == LF_REPEAT);
}

bool lf::IsKeyToggled(int key) {
	LF_ASSERT(lf_context->event != nullptr);

	return lf_context->event->key_toggled[key];
}

void lf::MouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	LF_ASSERT(lf_context->event != nullptr);

	lf_context->event->xpos = xpos;
	lf_context->event->ypos = ypos;
}

void lf::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	LF_ASSERT(lf_context->event != nullptr);

	if (lf_context->event->button_state[button] == LF_RELEASE && action == LF_PRESS) {
		lf_context->event->button_toggled[button] = !lf_context->event->button_toggled[button];
	}
	lf_context->event->button_state[button] = action;
}

bool lf::IsMousePressed(int button) {
	LF_ASSERT(lf_context->event != nullptr);

	return (lf_context->event->button_state[button] == LF_PRESS);
}

bool lf::IsMouseReleased(int button) {
	LF_ASSERT(lf_context->event != nullptr);

	return (lf_context->event->button_state[button] == LF_RELEASE);
}

bool lf::IsMouseToggled(int button) {
	LF_ASSERT(lf_context->event != nullptr);

	return (lf_context->event->button_toggled[button]);
}

double lf::GetMousePosX() {
	LF_ASSERT(lf_context->event != nullptr);

	return lf_context->event->xpos;
}

double lf::GetMousePosY() {
	LF_ASSERT(lf_context->event != nullptr);

	return lf_context->event->ypos;
}
