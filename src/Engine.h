#pragma once

#include "define.h"
#include "Layer.h"

class Engine {
public:
	double dt;
	GLFWwindow *window = nullptr;
	std::vector<std::shared_ptr<Layer>> layers;
	bool init = false;

	void Init();
	void Mainloop();

	template <typename T>
	void AddLayer() {
		assert(!init);
		layers.push_back(std::static_pointer_cast<Layer>(std::make_shared<T>()));
	}
};