#include "Sandbox.h"

#include "Math/Vec2.inl"
#include "Math/Vec3.inl"
#include "Math/Vec4.inl"

#include "Lucy/Lucy.h"

int x = 0, y = 0, w = 200, h = 200;

std::vector<Vec3> vertices = {
	Vec3(x, y, 0), 	Vec3(0, 0, 0),
	Vec3(x, y + h, 0), Vec3(0, 1, 0),
	Vec3(x + w, y + h, 0), Vec3(1, 1, 0),
	Vec3(x + w, y + h, 0), Vec3(1, 1, 0),
	Vec3(x + w, y, 0), Vec3(1, 0, 0),
	Vec3(x, y, 0), Vec3(0, 0, 0),
};

lf::Mesh* mesh;
static Shader* shader;

SpriteAtlas *atlas;

void Sandbox::Init() {
	lf::CreateCamera("cam0", lf::ORTHOGRAPHIC);
	lf::EnableCamera("cam0");

	shader = lf::RegisterShader("sprite", "D:\\C++\\Lucy Framework\\src\\Shaders\\default.vs", "D:\\C++\\Lucy Framework\\src\\Shaders\\texture.fs");

	mesh = lf::CreateMesh(lf::Vertex3D, lf::MeshType::TRIANGLES);

	auto* tex = Texture_LoadFile("D:\\C++\\Lucy Framework\\res\\container.png");

	lf::RenderRect(mesh, tex, Vec3(0, 0, 0), Vec3(100, 100), Vec2(0, 0), Vec2(1, 1), true);

	lf::TransferMesh(mesh);
}

void Sandbox::Update() {
	lf::ToggleWireframe(lf::IsKeyToggled(GLFW_KEY_E));

	static bool toggle;

	if (lf::IsMouseToggled(GLFW_MOUSE_BUTTON_3) && !toggle) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		lf::GetContext()->camera->mouse_enabled = true;
		toggle = true;
	}

	if (!lf::IsMouseToggled(GLFW_MOUSE_BUTTON_3) && toggle) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		lf::GetContext()->camera->mouse_enabled = false;
		toggle = false;
	}

	lf::RenderMesh(mesh, shader);
}
