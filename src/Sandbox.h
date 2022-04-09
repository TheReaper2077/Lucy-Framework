#pragma once

#include "Layer.h"

class Sandbox: public Layer {
public:
	void Init() override;
	void Update() override;
};