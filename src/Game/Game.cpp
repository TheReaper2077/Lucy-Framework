// #include "Game.h"

// #include "../Lucy/Lucy.h"
// #include "../Lucy/Draw.h"
// #include "Components.h"

// static lf::Mesh *mesh;
// static entt::registry registry;

// void Game::Init() {
// 	mesh = lf::CreateMesh(lf::Layout::Vertex3D, lf::RenderType::TRIANGLE_INDEXED);

// 	lf::CreateCamera("cam0", lf::ProjectionMode::ORTHOGRAPHIC);
// 	lf::EnableCamera("cam0");
	
// 	lf::RegisterShader("color", "D:\\C++\\Lucy Framework\\src\\Shaders\\default.vs", "D:\\C++\\Lucy Framework\\src\\Shaders\\color.fs");
// 	lf::RegisterShader("texture", "D:\\C++\\Lucy Framework\\src\\Shaders\\default.vs", "D:\\C++\\Lucy Framework\\src\\Shaders\\texture.fs");

// 	const auto entity = registry.create();
// 	registry.emplace<Transform>(entity, Vec3(-100, 100, 100), Vec3(100, 100));
// 	registry.emplace<Texture*>(entity, Texture_LoadFile("D:\\C++\\Lucy Framework\\res\\container.png"));
// 	registry.emplace<Controllable>(entity, true);

// 	const auto entity3 = registry.create();
// 	registry.emplace<Transform>(entity3, Vec3(-100, -200, -100), Vec3(100, 100));
// 	registry.emplace<Texture*>(entity3, Texture_LoadFile("D:\\C++\\Lucy Framework\\res\\container.png"));
// 	registry.emplace<Controllable>(entity3, false);
	
// 	const auto entity2 = registry.create();
// 	registry.emplace<Transform>(entity2, Vec3(0, 0), Vec3(100, 100));
// 	registry.emplace<Texture*>(entity2, Texture_LoadFile("D:\\C++\\Lucy Framework\\res\\container.png"));
// 	registry.emplace<Controllable>(entity2, false);	
// }

// void Game::Update() {	
// 	// Update
// 	lf::ToggleWireframe(lf::IsKeyToggled(GLFW_KEY_E));
// 	lf::ClearMesh(mesh);

// 	for (auto [entity, transform, controllable]: registry.view<Transform, const Controllable>().each()) {
// 		if (controllable) {
// 			if (lf::IsKeyPressed(GLFW_KEY_W)) {
// 				transform.pos.y -= lf::GetTimeStep()*5.0f;
// 			}
// 			if (lf::IsKeyPressed(GLFW_KEY_A)) {
// 				transform.pos.x -= lf::GetTimeStep()*5.0f;
// 			}
// 			if (lf::IsKeyPressed(GLFW_KEY_S)) {
// 				transform.pos.y += lf::GetTimeStep()*5.0f;
// 			}
// 			if (lf::IsKeyPressed(GLFW_KEY_D)) {
// 				transform.pos.x += lf::GetTimeStep()*5.0f;
// 			}

// 			transform.pos *= transform.pos.normalize();
// 		}
// 	};

// 	// Render

// 	registry.view<Transform, Texture*>().each([](auto entity, auto& transform, auto* texture) {
// 		lf::TextureRect(mesh, texture, transform.pos, transform.scale);
// 	});

// 	lf::TransferMesh(mesh);
// 	lf::RenderMesh(mesh, "texture");
// }
