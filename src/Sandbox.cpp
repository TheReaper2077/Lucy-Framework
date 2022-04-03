#include "Sandbox.h"

#include "Math/Vec2.inl"
#include "Math/Vec3.inl"
#include "Math/Vec4.inl"

#include "Lucy/Lucy.h"


int x = 0, y = 0, w = 100, h = 100;

std::vector<Vec3> vertices = {
	Vec3(x, y, 0), Vec3(0, 0, 0),
	Vec3(x, y + h, 0), Vec3(0, 1, 0),
	Vec3(x + w, y + h, 0), Vec3(1, 1, 0),
	Vec3(x + w, y + h, 0), Vec3(1, 1, 0),
	Vec3(x + w, y, 0), Vec3(1, 0, 0),
	Vec3(x, y, 0), Vec3(0, 0, 0),
	
	Vec3(x + 100, y, -100), Vec3(0, 0, 1),
	Vec3(x + 100, y + h, -100), Vec3(0, 1, 1),
	Vec3(x + 100 + w, y + h, -100), Vec3(1, 1, 1),
	Vec3(x + 100 + w, y + h, -100), Vec3(1, 1, 1),
	Vec3(x + 100 + w, y, -100), Vec3(1, 0, 1),
	Vec3(x + 100, y, -100), Vec3(0, 0, 1),
	
	Vec3(x + 200, y + 200, 100), Vec3(0, 0, 0),
	Vec3(x + 200, y + 200 + h, 100), Vec3(0, 1, 0),
	Vec3(x + 200 + w + 200, y + 200 + h, 100), Vec3(3, 1, 0),
	Vec3(x + 200 + w + 200, y + 200 + h, 100), Vec3(3, 1, 0),
	Vec3(x + 200 + w + 200, y + 200, 100), Vec3(3, 0, 0),
	Vec3(x + 200, y + 200, 100), Vec3(0, 0, 0),
};

Shader* shader;
UniformBuffer *ubo;
lf::Mesh *mesh;

float fov = 0;

Vec3 angles = Vec3(30, 150, 0);
float scale = 1;

bool ImGuiTile(Texture *tex, const Vec2 &size, const Vec2 &tile_pos, const Vec2 &tile_size) {
	return ImGui::ImageButton((void*)tex->id, ImVec2(256, 256), ImVec2(tile_pos.x/tex->width, tile_pos.y/tex->height), ImVec2((tile_pos.x + tile_size.x)/tex->width, (tile_pos.y + tile_size.y)/tex->height));
}

void Sandbox::Init() {
	lf::CreateContext();

	shader = Shader_Create("D:\\C++\\Lucy Framework\\src\\Shaders\\default.vs", "D:\\C++\\Lucy Framework\\src\\Shaders\\color.fs");
	Shader_BindUniformBlock(shader, "ProjectionMatrix", 0);

	auto model = glm::mat4(1.0f);
	auto projection = glm::ortho<float>(-WIDTH/2, WIDTH/2, HEIGHT/2, -HEIGHT/2, -1000, 1000);
	auto view = glm::mat4(1.0f);
	
	lf::SetModel(model);
	lf::SetView(view);
	lf::SetProjection(projection);

	mesh = lf::CreateMesh(lf::Vertex3D, lf::RenderType::TRIANGLES);

	mesh->vertices = vertices;

	lf::TransferMesh(mesh);
}

void Sandbox::Update(double dt) {
	lf::RenderMesh(mesh, shader);
	// rendercontext->dt = dt;
	// if (ImGui::Begin("Tiles")) {
	// 	if (ImGuiTile(specular_tex, Vec2(256, 256), Vec2(102, 182), Vec2(20, 26)));
	// }
	// ImGui::End();
}
