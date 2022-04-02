#pragma once

#include "Renderer.h"

struct Events {
	unsigned int key_state[GLFW_KEY_LAST + 1] = {GLFW_RELEASE};
	bool key_toggled[GLFW_KEY_LAST + 1] = {false};

	double xpos, ypos;
	unsigned int button_state[GLFW_MOUSE_BUTTON_LAST + 1] = {GLFW_RELEASE};
	bool button_toggled[GLFW_MOUSE_BUTTON_LAST + 1] = {false};
};

namespace Key {
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void IsPressed(int key);
	void IsReleased(int key);
	void IsTyping(int key);
	void IsToggled(int key);
}

namespace Mouse {
	void MouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	bool IsPressed(int button);
	bool IsReleased(int button);
	bool IsToggled(int button);
	double GetPosX();
	double GetPosY();
}
