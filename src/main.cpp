#define STB_IMAGE_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL

#include "define.h"
#include "Engine.h"
#include "Sandbox.h"
#include "Game/Game.h"

int main() {
	Engine engine;

	 engine.AddLayer<Sandbox>();
	//engine.AddLayer<Game>();

	engine.Init();
	engine.Mainloop();

	return 0;
}