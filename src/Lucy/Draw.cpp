#include "Draw.h"

static void ConstructRect(lf::DrawType type, lf::Mesh *mesh, Texture *texture, const float &v0x, const float &v0y, const float &v1x, const float &v1y, const Vec2& uv0, const Vec2& uv1, const float &index = 0) {
	assert(mesh->layout == lf::Layout::Vertex3D);

	if (mesh->type == lf::RenderType::LINES) {
		assert(type == lf::DrawType::DRAW);

		mesh->vertices.reserve(8 + 8 + mesh->vertices.size());

		mesh->vertices.emplace_back(Vec3(v0x, v0y));
		mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
		mesh->vertices.emplace_back(Vec3(v0x, v1y));
		mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
		mesh->vertices.emplace_back(Vec3(v0x, v1y));
		mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
		mesh->vertices.emplace_back(Vec3(v1x, v1y));
		mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
		mesh->vertices.emplace_back(Vec3(v1x, v1y));
		mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
		mesh->vertices.emplace_back(Vec3(v1x, v0y));
		mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
		mesh->vertices.emplace_back(Vec3(v1x, v0y));
		mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
		mesh->vertices.emplace_back(Vec3(v0x, v0y));
		mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
	}
	if (mesh->type == lf::RenderType::TRIANGLES) {
		assert(type != lf::DrawType::DRAW);

		mesh->vertices.reserve(6 + 6 + mesh->vertices.size());

		if (type == lf::DrawType::TEXTURE) {
			assert(mesh->textures.size() < 8);
			if (mesh->textures.find(texture) == mesh->textures.end()) mesh->textures.insert(texture);
			mesh->vertices.emplace_back(Vec3(v0x, v0y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, index));
			mesh->vertices.emplace_back(Vec3(v0x, v1y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv1.y, index));
			mesh->vertices.emplace_back(Vec3(v1x, v1y));
			mesh->vertices.emplace_back(Vec3(uv1.x, uv1.y, index));
			mesh->vertices.emplace_back(Vec3(v1x, v1y));
			mesh->vertices.emplace_back(Vec3(uv1.x, uv1.y, index));
			mesh->vertices.emplace_back(Vec3(v1x, v0y));
			mesh->vertices.emplace_back(Vec3(uv1.x, uv0.y, index));
			mesh->vertices.emplace_back(Vec3(v0x, v0y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, index));
		}
		if (type == lf::DrawType::FILL) {
			mesh->vertices.emplace_back(Vec3(v0x, v0y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
			mesh->vertices.emplace_back(Vec3(v0x, v1y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
			mesh->vertices.emplace_back(Vec3(v1x, v1y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
			mesh->vertices.emplace_back(Vec3(v1x, v1y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
			mesh->vertices.emplace_back(Vec3(v1x, v0y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
			mesh->vertices.emplace_back(Vec3(v0x, v0y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
		}

		mesh->vertexcount += 6;
	}
	if (mesh->type == lf::RenderType::TRIANGLE_INDEXED) {
		assert(type != lf::DrawType::DRAW);

		mesh->vertices.reserve(4 + 4 + mesh->vertices.size());

		if (type == lf::DrawType::TEXTURE) {
			assert(mesh->textures.size() < 8);
			if (mesh->textures.find(texture) == mesh->textures.end()) mesh->textures.insert(texture);
			mesh->vertices.emplace_back(Vec3(v0x, v0y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, index));
			mesh->vertices.emplace_back(Vec3(v0x, v1y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv1.y, index));
			mesh->vertices.emplace_back(Vec3(v1x, v1y));
			mesh->vertices.emplace_back(Vec3(uv1.x, uv1.y, index));
			mesh->vertices.emplace_back(Vec3(v1x, v0y));
			mesh->vertices.emplace_back(Vec3(uv1.x, uv0.y, index));
		}
		if (type == lf::DrawType::FILL) {
			mesh->vertices.emplace_back(Vec3(v0x, v0y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
			mesh->vertices.emplace_back(Vec3(v0x, v1y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
			mesh->vertices.emplace_back(Vec3(v1x, v1y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
			mesh->vertices.emplace_back(Vec3(v1x, v0y));
			mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, uv1.x));
		}

		mesh->vertexcount += 4;

		if (mesh->vertexcount * 1.5 > mesh->meshindices->indexcount) {
			mesh->meshindices->indices.reserve(6 + mesh->meshindices->indices.size());

			mesh->meshindices->indices.emplace_back(0 + mesh->vertexcount - 4);
			mesh->meshindices->indices.emplace_back(1 + mesh->vertexcount - 4);
			mesh->meshindices->indices.emplace_back(2 + mesh->vertexcount - 4);
			mesh->meshindices->indices.emplace_back(2 + mesh->vertexcount - 4);
			mesh->meshindices->indices.emplace_back(3 + mesh->vertexcount - 4);
			mesh->meshindices->indices.emplace_back(0 + mesh->vertexcount - 4);

			mesh->meshindices->indexcount += 6;
		}
	}
}

void lf::DrawRect(lf::Mesh *mesh, const Vec3& pos, const Vec3& scale, const Vec3& color, const float& thickness) {
	ConstructRect(lf::DrawType::DRAW, mesh, nullptr, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y, Vec2(color.x, color.y), Vec2(color.z, thickness));
}

void lf::FillRect(lf::Mesh *mesh, const Vec3& pos, const Vec3& scale, const Vec3& color) {
	ConstructRect(lf::DrawType::FILL, mesh, nullptr, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y, Vec2(color.x, color.y), Vec2(color.z, 0));
}

void lf::TextureRect(Mesh *mesh, Texture *texture, const Vec3& pos, const Vec3& scale, const Vec2& uv0, const Vec2& uv1) {
	ConstructRect(lf::DrawType::TEXTURE, mesh, texture, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y, uv0, uv1);
}
