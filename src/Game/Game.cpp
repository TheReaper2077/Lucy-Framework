#include "Game.h"

#include "../Lucy/Lucy.h"
#include "Components.h"

static lf::Mesh *mesh;
static entt::registry registry;

struct Vector {
	Vec3T<uint32_t> pos;
};

void Game::Init() {
	mesh = lf::CreateMesh(lf::Layout::Vertex3D, lf::MeshType::TRIANGLE_INDEXED);

	lf::CreateCamera("cam0", lf::ProjectionMode::PERSPECTIVE);
	lf::EnableCamera("cam0");
	
	lf::RegisterShader("texture", "D:\\C++\\Lucy Framework\\src\\Shaders\\default.vs", "D:\\C++\\Lucy Framework\\src\\Shaders\\texture.fs");

	auto* tile = lf::LoadTile("D:\\C++\\Lucy Framework\\res\\blocks.png", Vec2(80, 80), Vec2(80, 80));

	const auto entity = registry.create();
	registry.emplace<Transform>(entity, Vec3(-1, 1, 0), Vec3(1, 1));
	registry.emplace<lf::TexTile*>(entity, tile);
	registry.emplace<Controllable>(entity, true);

	const auto entity3 = registry.create();
	registry.emplace<Transform>(entity3, Vec3(-1, 0, 0), Vec3(1, 1));
	registry.emplace<lf::TexTile*>(entity3, tile);
	registry.emplace<Controllable>(entity3, false);
	
	const auto entity2 = registry.create();
	registry.emplace<Transform>(entity2, Vec3(0, 0), Vec3(1, 1));
	registry.emplace<lf::TexTile*>(entity2, tile);
	registry.emplace<Controllable>(entity2, false);
}

void Game::Update() {	
	// Update
	lf::ToggleWireframe(lf::IsKeyToggled(LF_KEY_E));

	static bool toggle;

	if (lf::IsMouseToggled(LF_MOUSE_BUTTON_3) && !toggle) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		lf::GetContext()->camera->mouse_enabled = true;
		toggle = true;
	}

	if (!lf::IsMouseToggled(LF_MOUSE_BUTTON_3) && toggle) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		lf::GetContext()->camera->mouse_enabled = false;
		toggle = false;
	}

	lf::ClearMesh(mesh);

	for (auto [entity, transform, controllable]: registry.view<Transform, const Controllable>().each()) {
		if (controllable) {
			if (lf::IsKeyPressed(LF_KEY_W)) {
				transform.pos.y -= lf::GetTimeStep()*5.0f;
			}
			if (lf::IsKeyPressed(LF_KEY_A)) {
				transform.pos.x -= lf::GetTimeStep()*5.0f;
			}
			if (lf::IsKeyPressed(LF_KEY_S)) {
				transform.pos.y += lf::GetTimeStep()*5.0f;
			}
			if (lf::IsKeyPressed(LF_KEY_D)) {
				transform.pos.x += lf::GetTimeStep()*5.0f;
			}
		}
	};

	// Render

	registry.view<Transform, lf::TexTile*>().each([](auto entity, auto& transform, auto* tile) {
		lf::RenderRect(mesh, tile, transform.pos, transform.scale, true);
	});

	lf::TransferMesh(mesh);
	lf::RenderMesh(mesh, "texture");
}
