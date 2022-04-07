#include "Game.h"

std::shared_ptr<Game> game;

float speed = 5.0f;

uint8_t map[20][20] = {
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void update(entt::registry &registry) {
	

	
}

void GameInit() {
	assert(game == nullptr);

	game = std::make_shared<Game>();

	game->mesh = lf::CreateMesh(lf::Layout::Vertex3D, lf::RenderType::TRIANGLE_INDEXED);

	lf::CreateCamera("cam0", lf::ProjectionMode::ORTHOGRAPHIC);
	lf::EnableCamera("cam0");

	const auto entity = game->registry.create();
	game->registry.emplace<Transform>(entity, Vec3(-100, 100, 100), Vec3(100, 100));
	game->registry.emplace<Texture*>(entity, Texture_LoadFile("D:\\C++\\Lucy Framework\\res\\container.png"));
	game->registry.emplace<Controllable>(entity, true);
	
	const auto entity3 = game->registry.create();
	game->registry.emplace<Transform>(entity3, Vec3(-100, -200, -100), Vec3(100, 100));
	game->registry.emplace<Texture*>(entity3, Texture_LoadFile("D:\\C++\\Lucy Framework\\res\\container.png"));
	game->registry.emplace<Controllable>(entity3, false);
	
	const auto entity2 = game->registry.create();
	game->registry.emplace<Transform>(entity2, Vec3(0, 0), Vec3(100, 100));
	game->registry.emplace<Texture*>(entity2, Texture_LoadFile("D:\\C++\\Lucy Framework\\res\\container.png"));
	game->registry.emplace<Controllable>(entity2, false);
}

void GameUpdate() {	
	// Update
	lf::ToggleWireframe(lf::IsKeyToggled(GLFW_KEY_E));
	lf::ClearMesh(game->mesh);

	for (auto entity: game->registry.view<Transform, const Controllable, Texture*>()) {
		const auto& controllable = game->registry.get<Controllable>(entity);
		auto& transform = game->registry.get<Transform>(entity);
		auto* texture = game->registry.get<Texture*>(entity);

		if (controllable) {
			if (lf::IsKeyPressed(GLFW_KEY_W)) {
				transform.pos.y -= lf::GetTimeStep()*speed;
			}
			if (lf::IsKeyPressed(GLFW_KEY_A)) {
				transform.pos.x -= lf::GetTimeStep()*speed;
			}
			if (lf::IsKeyPressed(GLFW_KEY_S)) {
				transform.pos.y += lf::GetTimeStep()*speed;
			}
			if (lf::IsKeyPressed(GLFW_KEY_D)) {
				transform.pos.x += lf::GetTimeStep()*speed;
			}

			transform.pos.z = transform.pos.y;

			// transform.pos = transform.pos.normalize();
		}

		lf::TextureRect(game->mesh, texture, transform.pos, transform.scale);
	}

	// Render

	// for (auto entity: game->registry.view<Transform, Texture*>()) {
	// 	auto* texture = game->registry.get<Texture*>(entity);
	// 	auto transform = game->registry.get<Transform>(entity);

	// 	lf::TextureRect(game->mesh, texture, transform.pos, transform.scale);
	// }

	lf::TransferMesh(game->mesh);
	lf::RenderMesh(game->mesh, "texture");
}
