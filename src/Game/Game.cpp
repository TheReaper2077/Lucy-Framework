#include "Game.h"

#include "../Lucy/Lucy.h"
#include "../Lucy/Mesh.h"

#include "World.h"

struct Vertex {
	Vec3 position;
	Vec3 uv;
	Vec3 normals;
};

static int x = 0, y = 0, z = 0, w = 1, h = 1, d = 1;

std::vector<Vertex> vertices = {
	// near
	{ Vec3(x, y, z), Vec3(0, 0, 1), Vec3(1, 0, 0) },
	{ Vec3(x + w, y, z), Vec3(0, 0, 1), Vec3(1, 0, 0) },
	{ Vec3(x + w, y + h, z), Vec3(0, 0, 1), Vec3(1, 0, 0) },
	{ Vec3(x, y + h, z), Vec3(0, 0, 1), Vec3(1, 0, 0) },
	// far
	{ Vec3(x, y, z + d), Vec3(0, 1, 0), Vec3(1, 0, 0) },
	{ Vec3(x + w, y, z + d), Vec3(0, 1, 0), Vec3(1, 0, 0) },
	{ Vec3(x + w, y + h, z + d), Vec3(0, 1, 0), Vec3(1, 0, 0) },
	{ Vec3(x, y + h, z + d), Vec3(0, 1, 0), Vec3(1, 0, 0) },
	// top
	{ Vec3(x, y + h, z), Vec3(0, 1, 1), Vec3(1, 0, 0) },
	{ Vec3(x + w, y + h, z), Vec3(0, 1, 1), Vec3(1, 0, 0) },
	{ Vec3(x + w, y + h, z + d), Vec3(0, 1, 1), Vec3(1, 0, 0) },
	{ Vec3(x, y + h, z + d), Vec3(0, 1, 1), Vec3(1, 0, 0) },
	// bottom
	{ Vec3(x, y, z), Vec3(1, 0, 0), Vec3(1, 0, 0) },
	{ Vec3(x + w, y, z), Vec3(1, 0, 0), Vec3(1, 0, 0) },
	{ Vec3(x + w, y, z + d), Vec3(1, 0, 0), Vec3(1, 0, 0) },
	{ Vec3(x, y, z + d), Vec3(1, 0, 0), Vec3(1, 0, 0) },
	// left
	{ Vec3(x + w, y, z), Vec3(1, 0, 1), Vec3(1, 0, 0) },
	{ Vec3(x + w, y, z + d), Vec3(1, 0, 1), Vec3(1, 0, 0) },
	{ Vec3(x + w, y + h, z + d), Vec3(1, 0, 1), Vec3(1, 0, 0) },
	{ Vec3(x + w, y + h, z), Vec3(1, 0, 1), Vec3(1, 0, 0) },
	// right
	{ Vec3(x, y, z), Vec3(1, 1, 0), Vec3(1, 0, 0) },
	{ Vec3(x, y, z + d), Vec3(1, 1, 0), Vec3(1, 0, 0) },
	{ Vec3(x, y + h, z + d), Vec3(1, 1, 0), Vec3(1, 0, 0) },
	{ Vec3(x, y + h, z), Vec3(1, 1, 0), Vec3(1, 0, 0) },
};

lf::MeshT<Vertex> *mesh;
lf::MeshIndices *meshindices;

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

	meshindices = lf::CreateMeshIndices();
	mesh = lf::CreateMesh<Vertex>(lf::MeshType::TRIANGLE_INDEXED, meshindices);

	mesh->vertices = vertices;

	meshindices->indices.reserve(6*6);

	for (int i = 0; i < 6; i++) {
		meshindices->indices.emplace_back(0 + 4 * i);
		meshindices->indices.emplace_back(1 + 4 * i);
		meshindices->indices.emplace_back(2 + 4 * i);
		meshindices->indices.emplace_back(2 + 4 * i);
		meshindices->indices.emplace_back(3 + 4 * i);
		meshindices->indices.emplace_back(0 + 4 * i);
	}

	lf::TransferMesh(mesh);
	lf::TransferMeshIndices(meshindices);
}

void Game::Update() {	
	lf::ToggleWireframe(lf::IsKeyToggled(LF_KEY_E));

	lf::RenderMesh(mesh, "color");
}
