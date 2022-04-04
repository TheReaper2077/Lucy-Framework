#include "Draw.h"

void lf::DrawRect(lf::Mesh *mesh, float v0x, float v0y, float v1x, float v1y, const Vec3& color, const int& thickness) {
	assert(mesh->type == lf::RenderType::LINES);
	assert(mesh->layout == lf::Layout::Vertex3D);

	mesh->vertices.reserve(8 + 8 + mesh->vertices.size());

	mesh->vertices.emplace_back(Vec3(v0x, v0y));
	mesh->vertices.emplace_back(color);
	mesh->vertices.emplace_back(Vec3(v0x, v1y));
	mesh->vertices.emplace_back(color);
	mesh->vertices.emplace_back(Vec3(v0x, v1y));
	mesh->vertices.emplace_back(color);
	mesh->vertices.emplace_back(Vec3(v1x, v1y));
	mesh->vertices.emplace_back(color);
	mesh->vertices.emplace_back(Vec3(v1x, v1y));
	mesh->vertices.emplace_back(color);
	mesh->vertices.emplace_back(Vec3(v1x, v0y));
	mesh->vertices.emplace_back(color);
	mesh->vertices.emplace_back(Vec3(v1x, v0y));
	mesh->vertices.emplace_back(color);
	mesh->vertices.emplace_back(Vec3(v0x, v0y));
	mesh->vertices.emplace_back(color);
}

void lf::FillRect(lf::Mesh *mesh, float v0x, float v0y, float v1x, float v1y, const Vec3& color) {
	assert(mesh->layout == lf::Layout::Vertex3D);

	if (mesh->type == lf::RenderType::TRIANGLES) {
		mesh->vertices.reserve(6 + 6 + mesh->vertices.size());

		mesh->vertices.emplace_back(Vec3(v0x, v0y));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(v0x, v1y));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(v1x, v1y));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(v1x, v1y));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(v1x, v0y));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(v0x, v0y));
		mesh->vertices.emplace_back(color);

		mesh->vertexcount += 6;
	}
	if (mesh->type == lf::RenderType::TRIANGLE_INDEXED) {
		mesh->vertices.reserve(4 + 4 + mesh->vertices.size());

		mesh->vertices.emplace_back(Vec3(v0x, v0y));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(v0x, v1y));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(v1x, v1y));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(v1x, v0y));
		mesh->vertices.emplace_back(color);

		mesh->vertexcount += 4;

		if (mesh->vertexcount * 1.5 > mesh->meshindices->indexcount) {
			mesh->meshindices->indices.reserve(6 + mesh->meshindices->indices.size());

			mesh->meshindices->indices.emplace_back(0);
			mesh->meshindices->indices.emplace_back(1);
			mesh->meshindices->indices.emplace_back(2);
			mesh->meshindices->indices.emplace_back(2);
			mesh->meshindices->indices.emplace_back(3);
			mesh->meshindices->indices.emplace_back(0);

			mesh->meshindices->indexcount += 6;
		}
	}
}

void lf::DrawRect(lf::Mesh *mesh, const Vec3& pos, const Vec3& scale, const Vec3& color, const int& thickness) {
	lf::DrawRect(mesh, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y, color, thickness);
}

void lf::FillRect(lf::Mesh *mesh, const Vec3& pos, const Vec3& scale, const Vec3& color) {
	lf::FillRect(mesh, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y, color);
}
