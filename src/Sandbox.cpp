#include "Sandbox.h"

#include "Math/Vec2.inl"
#include "Math/Vec3.inl"
#include "Math/Vec4.inl"

#include "Lucy/Lucy.h"
#include "Lucy/Draw.h"

int x = 1, y = 1, w = 1, h = 1;

std::vector<Vec3> vertices = {
	Vec3(x, y, 0), 	Vec3(0, 0, 1),
	Vec3(x, y + h, 0), Vec3(0, 1, 1),
	Vec3(x + w, y + h, 0), Vec3(1, 1, 1),
	Vec3(x + w, y + h, 0), Vec3(1, 1, 1),
	Vec3(x + w, y, 0), Vec3(1, 0, 1),
	Vec3(x, y, 0), Vec3(0, 0, 1),
	
	// Vec3(x + 1, y, 1), 	Vec3(0, 0, 1),
	// Vec3(x + 1, y + h, 1), Vec3(0, 1, 1),
	// Vec3(x + 1 + w, y + h, 1), Vec3(1, 1, 1),
	// Vec3(x + 1 + w, y + h, 1), Vec3(1, 1, 1),
	// Vec3(x + 1 + w, y, 1), Vec3(1, 0, 1),
	// Vec3(x + 1, y, 1), Vec3(0, 0, 1),

	// Vec3(x + 1, y, -1), Vec3(0, 0, 1),
	// Vec3(x + 1, y + h, -1), Vec3(0, 1, 1),
	// Vec3(x + 1 + w, y + h, -1), Vec3(1, 1, 1),
	// Vec3(x + 1 + w, y + h, -1), Vec3(1, 1, 1),
	// Vec3(x + 1 + w, y, -1), Vec3(1, 0, 1),
	// Vec3(x + 1, y, -1), Vec3(0, 0, 1),
};

lf::Mesh* mesh;
static Shader* shader;

uint32_t tex;

int a[100*100*4];

void Sandbox::Init() {
	lf::CreateCamera("cam0", lf::ORTHOGRAPHIC);
	lf::EnableCamera("cam0");

	shader = lf::RegisterShader("sprite", "D:\\C++\\Lucy Framework\\src\\Shaders\\default.vs", "D:\\C++\\Lucy Framework\\src\\Shaders\\color.fs");

	mesh = lf::CreateMesh(lf::Vertex3D, lf::RenderType::TRIANGLES);

	mesh->vertices = vertices;

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

	static bool show = true;

	ImGui::ShowDemoWindow(&show);

	lf::RenderMesh(mesh, shader);
}
