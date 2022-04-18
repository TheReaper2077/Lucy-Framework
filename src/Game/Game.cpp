#include "Game.h"

#include "../Lucy/Lucy.h"
#include "../Lucy/Mesh.h"

#include "World.h"


void Game::Init() {
	lf::CreateCamera("cam0", lf::PERSPECTIVE);
	lf::EnableCamera("cam0");

	lf::RegisterShader("texture", "D:\\C++\\Lucy Framework\\src\\Shaders\\default.vs", "D:\\C++\\Lucy Framework\\src\\Shaders\\texture.fs");
	lf::RegisterShader("color", "D:\\C++\\Lucy Framework\\src\\Shaders\\default.vs", "D:\\C++\\Lucy Framework\\src\\Shaders\\color.fs");

	lf::LoadTileset("tileset", "D:\\C++\\Lucy Framework\\res\\Tileset.json", true);

	lf::DisableCursor();

	lf::RegisterLayout<Vertex>({
		{0, 3, GL_FLOAT},
		{1, 3, GL_FLOAT},
		{2, 3, GL_FLOAT},
	});
}

void Game::Update() {	
	lf::ToggleWireframe(lf::IsKeyToggled(LF_KEY_E));
	
}
