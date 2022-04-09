#include "Sandbox.h"

#include "Math/Vec2.inl"
#include "Math/Vec3.inl"
#include "Math/Vec4.inl"

#include "Lucy/Lucy.h"
#include "Lucy/Draw.h"

int x = 0, y = 0, w = 100, h = 100;

std::vector<Vec3> vertices = {
	Vec3(x, y, 1), 	Vec3(0, 0, 1),
	Vec3(x, y + h, 1), Vec3(0, 1, 1),
	Vec3(x + w, y + h, 1), Vec3(1, 1, 1),
	Vec3(x + w, y + h, 1), Vec3(1, 1, 1),
	Vec3(x + w, y, 1), Vec3(1, 0, 1),
	Vec3(x, y, 1), Vec3(0, 0, 1),
};

static lf::Mesh* mesh;
static Shader* shader;

uint32_t tex;

int a[100*100*4];

void Sandbox::Init() {
	lf::CreateCamera("cam0", lf::PERSPECTIVE);
	lf::EnableCamera("cam0");

	shader = lf::RegisterShader("sprite", "D:\\C++\\Lucy Framework\\src\\Shaders\\default.vs", "D:\\C++\\Lucy Framework\\src\\Shaders\\color.fs");

	mesh = lf::CreateMesh(lf::Vertex3D, lf::RenderType::TRIANGLES);

	mesh->vertices = vertices;

	lf::TransferMesh(mesh);

	glGenTextures(1, &tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// for (int x = 0; x < 100; x++) {
	// 	for (int y = 0; y < 100; y++) {
	// 		a[x * 100 * 4 + y * 4 + 0] = 255;
	// 		a[x * 100 * 4 + y * 4 + 1] = 255;
	// 		a[x * 100 * 4 + y * 4 + 2] = 255;
	// 		a[x * 100 * 4 + y * 4 + 3] = 255;
	// 	}
	// }

	// // glTexImage3D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	// glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, 100, 100, 100, 0, GL_RGBA, GL_UNSIGNED_BYTE, a);
}

Vec3 mag(30, 30, 0);

void Sandbox::Update() {
	lf::ToggleWireframe(lf::IsKeyToggled(GLFW_KEY_E));

	// if (ImGui::Begin("Camera")) {
	// 	ImGui::SliderFloat3("x, y, z", &mag[0], 0, 360, nullptr, 1);
	// 	lf::CameraView(mag);
	// };

	// ImGui::End();
	lf::RenderMesh(mesh, shader);
}
