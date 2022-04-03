#pragma once

#include "../define.h"

class KeyListener {
private:
	KeyListener() {}

	unsigned int key_state[GLFW_KEY_LAST + 1] = {GLFW_RELEASE};
	bool key_toggled[GLFW_KEY_LAST + 1] = {false};

public:
	static KeyListener *SharedInstance() {
		static KeyListener instance;
		return &instance;
	}

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (SharedInstance()->key_state[key] == GLFW_RELEASE && action == GLFW_PRESS) {
			SharedInstance()->key_toggled[key] = !SharedInstance()->key_toggled[key];
		}
		SharedInstance()->key_state[key] = action;
	}

	static bool IsKeyPressed(int key) {
		return (SharedInstance()->key_state[key] == GLFW_PRESS || SharedInstance()->key_state[key] == GLFW_REPEAT);
	}

	static bool IsKeyReleased(int key) {
		return (SharedInstance()->key_state[key] == GLFW_RELEASE);
	}

	static bool IsKeyTyping(int key) {
		return (SharedInstance()->key_state[key] == GLFW_REPEAT);
	}

	static bool IsKeyToggled(int key) {
		return SharedInstance()->key_toggled[key];
	}
};
