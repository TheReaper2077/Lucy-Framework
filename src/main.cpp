#define STB_IMAGE_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL

#include "define.h"
#include "Engine.h"
#include "Sandbox.h"

int main() {
	Engine engine;

	engine.AddLayer<Sandbox>();

	engine.Init();
	engine.Mainloop();
}