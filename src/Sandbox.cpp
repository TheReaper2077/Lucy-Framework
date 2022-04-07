#include "Sandbox.h"

#include "Math/Vec2.inl"
#include "Math/Vec3.inl"
#include "Math/Vec4.inl"

#include "Lucy/Lucy.h"
#include "Lucy/Draw.h"
#include "Game/Game.h"

// int x = 0, y = 0, w = 100, h = 100;

// std::vector<Vec3> vertices = {
// 	Vec3(x, y, 0), Vec3(0, 0, 0),
// 	Vec3(x, y + h, 0), Vec3(0, 1, 0),
// 	Vec3(x + w, y + h, 0), Vec3(1, 1, 0),
// 	Vec3(x + w, y + h, 0), Vec3(1, 1, 0),
// 	Vec3(x + w, y, 0), Vec3(1, 0, 0),
// 	Vec3(x, y, 0), Vec3(0, 0, 0),
	
// 	Vec3(x + 100, y, -100), Vec3(0, 0, 1),
// 	Vec3(x + 100, y + h, -100), Vec3(0, 1, 1),
// 	Vec3(x + 100 + w, y + h, -100), Vec3(1, 1, 1),
// 	Vec3(x + 100 + w, y + h, -100), Vec3(1, 1, 1),
// 	Vec3(x + 100 + w, y, -100), Vec3(1, 0, 1),
// 	Vec3(x + 100, y, -100), Vec3(0, 0, 1),
	
// 	Vec3(x + 200, y + 200, 100), Vec3(0, 0, 0),
// 	Vec3(x + 200, y + 200 + h, 100), Vec3(0, 1, 0),
// 	Vec3(x + 200 + w + 200, y + 200 + h, 100), Vec3(3, 1, 0),
// 	Vec3(x + 200 + w + 200, y + 200 + h, 100), Vec3(3, 1, 0),
// 	Vec3(x + 200 + w + 200, y + 200, 100), Vec3(3, 0, 0),
// 	Vec3(x + 200, y + 200, 100), Vec3(0, 0, 0),
// };

// Shader* shader, *tex_shader;
// UniformBuffer *ubo;
// lf::Mesh *temp;

// float fov = 0;

// Vec3 angles = Vec3(30, 150, 0);
// float scale = 1;

bool ImGuiTile(Texture *tex, const Vec2 &size, const Vec2 &tile_pos, const Vec2 &tile_size) {
	return ImGui::ImageButton((void*)tex->id, ImVec2(256, 256), ImVec2(tile_pos.x/tex->width, tile_pos.y/tex->height), ImVec2((tile_pos.x + tile_size.x)/tex->width, (tile_pos.y + tile_size.y)/tex->height));
}

void Sandbox::Init() {
	lf::CreateContext();

	// lf::CreateCamera("cam0", lf::ORTHOGRAPHIC);
	// lf::EnableCamera("cam0");
	// temp = lf::CreateMesh(lf::Vertex3D, lf::TRIANGLE_INDEXED);

	// auto* tex = Texture_LoadFile("D:\\C++\\Lucy Framework\\res\\container.png");

	// lf::TextureRect(temp, tex, Vec3(-200, -300), Vec3(100, 100));
	// lf::TextureRect(temp, tex, Vec3(-200, -200), Vec3(100, 100));
	// lf::TextureRect(temp, tex, Vec3(-300, -300), Vec3(100, 100));
	
	// lf::TransferMesh(temp);
	// lf::ClearMesh(temp);

	lf::RegisterShader("color", "D:\\C++\\Lucy Framework\\src\\Shaders\\default.vs", "D:\\C++\\Lucy Framework\\src\\Shaders\\color.fs");
	lf::RegisterShader("texture", "D:\\C++\\Lucy Framework\\src\\Shaders\\default.vs", "D:\\C++\\Lucy Framework\\src\\Shaders\\texture.fs");
	
	GameInit();
}

Vec3 mag(150, 30, 0);

void Sandbox::Update(double dt) {
	lf::Update();
	
	GameUpdate();
	
	// lf::ToggleWireframe(lf::IsKeyToggled(GLFW_KEY_E));

	if (ImGui::Begin("Camera")) {
		ImGui::SliderFloat3("x, y, z", &mag[0], 0, 360, nullptr, 1);
		lf::CameraView(mag);
	};
	ImGui::End();
	// lf::RenderMesh(temp, "texture");
}
