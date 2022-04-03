#pragma once

#include "../define.h"

class MouseListener {
private:
	MouseListener() {}

	double xpos, ypos;

	unsigned int button_state[GLFW_MOUSE_BUTTON_LAST + 1] = {GLFW_RELEASE};
	bool button_toggled[GLFW_MOUSE_BUTTON_LAST + 1] = {false};

public:
	static MouseListener *SharedInstance() {
		static MouseListener instance;
		return &instance;
	}

	static void MouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
		SharedInstance()->xpos = xpos;
		SharedInstance()->ypos = ypos;
	}

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		if (SharedInstance()->button_state[button] == GLFW_RELEASE && action == GLFW_PRESS) {
			SharedInstance()->button_toggled[button] = !SharedInstance()->button_toggled[button];
		}
		SharedInstance()->button_state[button] = action;
	}

	static bool IsButtonPressed(int button) {
		return (SharedInstance()->button_state[button] == GLFW_PRESS);
	}

	static bool IsButtonReleased(int button) {
		return (SharedInstance()->button_state[button] == GLFW_RELEASE);
	}

	static bool IsButtonToggled(int button) {
		return (SharedInstance()->button_toggled[button]);
	}

	static double GetPosX() {
		return SharedInstance()->xpos;
	}

	static double GetPosY() {
		return SharedInstance()->ypos;
	}
};
