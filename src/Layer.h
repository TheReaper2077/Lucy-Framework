#pragma once

#include "define.h"

class Layer {
protected:
	GLFWwindow *window = nullptr;
public:
	void SetWindow(GLFWwindow *window) {
		this->window = window;
	}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
};