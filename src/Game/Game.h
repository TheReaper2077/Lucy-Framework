#pragma once

#include "../Layer.h"

class Game: public Layer {
public:
	void Init() override;
	void Update() override;
};
