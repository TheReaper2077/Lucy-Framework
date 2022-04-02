#include "Sandbox.h"

#include "Math/Vec2.inl"
#include "Math/Vec3.inl"
#include "Math/Vec4.inl"

#include "Lucy/Lucy.h"


int x = 0, y = 0, w = 100, h = 100;

struct Vertex2D {
	Vec3 pos;
	Vec3 color;
};

std::vector<Vertex2D> vertices = {
	{ Vec3(x, y, 0), Vec3(0, 0, 0) },
	{ Vec3(x, y + h, 0), Vec3(0, 1, 0) },
	{ Vec3(x + w, y + h, 0), Vec3(1, 1, 0) },
	{ Vec3(x + w, y + h, 0), Vec3(1, 1, 0) },
	{ Vec3(x + w, y, 0), Vec3(1, 0, 0) },
	{ Vec3(x, y, 0), Vec3(0, 0, 0) },
	
	{ Vec3(x + 100, y, -100), Vec3(0, 0, 1) },
	{ Vec3(x + 100, y + h, -100), Vec3(0, 1, 1) },
	{ Vec3(x + 100 + w, y + h, -100), Vec3(1, 1, 1) },
	{ Vec3(x + 100 + w, y + h, -100), Vec3(1, 1, 1) },
	{ Vec3(x + 100 + w, y, -100), Vec3(1, 0, 1) },
	{ Vec3(x + 100, y, -100), Vec3(0, 0, 1) },
	
	{ Vec3(x + 200, y + 200, 100), Vec3(0, 0, 0) },
	{ Vec3(x + 200, y + 200 + h, 100), Vec3(0, 1, 0) },
	{ Vec3(x + 200 + w + 200, y + 200 + h, 100), Vec3(3, 1, 0) },
	{ Vec3(x + 200 + w + 200, y + 200 + h, 100), Vec3(3, 1, 0) },
	{ Vec3(x + 200 + w + 200, y + 200, 100), Vec3(3, 0, 0) },
	{ Vec3(x + 200, y + 200, 100), Vec3(0, 0, 0) },
};

Shader* shader;
UniformBuffer *ubo;

void Sandbox::Init() {
	shader = Shader_Create("D:\\C++\\Lucy Framework\\src\\Shaders\\default.vs", "D:\\C++\\Lucy Framework\\src\\Shaders\\color.fs");
	Shader_BindUniformBlock(shader, "ProjectionMatrix", 0);

	ubo = UniformBuffer_Create();
}

float fov = 0;

Vec3 angles = Vec3(30, 150, 0);
float scale = 1;

bool ImGuiTile(Texture *tex, const Vec2 &size, const Vec2 &tile_pos, const Vec2 &tile_size) {
	return ImGui::ImageButton((void*)tex->id, ImVec2(256, 256), ImVec2(tile_pos.x/tex->width, tile_pos.y/tex->height), ImVec2((tile_pos.x + tile_size.x)/tex->width, (tile_pos.y + tile_size.y)/tex->height));
}

void Sandbox::Update(double dt) {	
	// rendercontext->dt = dt;
	// if (ImGui::Begin("Tiles")) {
	// 	if (ImGuiTile(specular_tex, Vec2(256, 256), Vec2(102, 182), Vec2(20, 26)));
	// }
	// ImGui::End();
}
