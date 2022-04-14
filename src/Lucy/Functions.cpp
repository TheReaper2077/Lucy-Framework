#include "Functions.h"

void lf::RenderRect(Mesh* mesh, TexTile *tex, const Vec3& pos, const Vec3& scale, bool enable_indexing) {
	LF_ASSERT(mesh->layout == lf::Vertex3D);
	LF_ASSERT(tex->texture != nullptr);
	lf::RenderRect(mesh, tex->texture, pos, scale, tex->uv0, tex->uv1, enable_indexing);
}

void lf::RenderRect(lf::Mesh* mesh, Texture *tex, const Vec3& pos, const Vec3& scale, const Vec2& uv0, const Vec2& uv1, bool enable_indexing) {
	LF_ASSERT(mesh->layout == lf::Vertex3D);
	LF_ASSERT(mesh->type == lf::TRIANGLES || (mesh->type == lf::TRIANGLE_INDEXED && enable_indexing));

	if (mesh->textures.find(tex) == mesh->textures.end()) {
		LF_ASSERT(mesh->next_texture_unit < LF_ABSOLUTE_TEXTURES_LIMIT);

		mesh->textures[tex] = mesh->next_texture_unit++;
	}

	float tex_index = mesh->textures[tex];

	if (mesh->type == lf::MeshType::TRIANGLES) {
		mesh->vertices.reserve(6 + 6 + mesh->vertices.size());

		mesh->vertices.emplace_back(Vec3(pos.x, pos.y, pos.z));
		mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, tex_index));
		mesh->vertices.emplace_back(Vec3(pos.x, pos.y + scale.y, pos.z));
		mesh->vertices.emplace_back(Vec3(uv0.x, uv1.y, tex_index));
		mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y + scale.y, pos.z));
		mesh->vertices.emplace_back(Vec3(uv1.x, uv1.y, tex_index));
		mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y + scale.y, pos.z));
		mesh->vertices.emplace_back(Vec3(uv1.x, uv1.y, tex_index));
		mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y, pos.z));
		mesh->vertices.emplace_back(Vec3(uv1.x, uv0.y, tex_index));
		mesh->vertices.emplace_back(Vec3(pos.x, pos.y, pos.z));
		mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, tex_index));

		mesh->vertexcount += 6;
	} else if (mesh->type == lf::TRIANGLE_INDEXED) {	
		mesh->vertices.reserve(4 + 4 + mesh->vertices.size());
		
		mesh->vertices.emplace_back(Vec3(pos.x, pos.y, pos.z));
		mesh->vertices.emplace_back(Vec3(uv0.x, uv0.y, tex_index));
		mesh->vertices.emplace_back(Vec3(pos.x, pos.y + scale.y, pos.z));
		mesh->vertices.emplace_back(Vec3(uv0.x, uv1.y, tex_index));
		mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y + scale.y, pos.z));
		mesh->vertices.emplace_back(Vec3(uv1.x, uv1.y, tex_index));
		mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y, pos.z));
		mesh->vertices.emplace_back(Vec3(uv1.x, uv0.y, tex_index));

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

void lf::RenderRect(Mesh* mesh, const Vec3& pos, const Vec3& scale, const Vec3& color, bool fill, bool enable_indexing) {
	LF_ASSERT(mesh->layout == lf::Vertex3D);
	if (fill) {
		LF_ASSERT(mesh->type == lf::MeshType::TRIANGLES || (mesh->type == lf::MeshType::TRIANGLE_INDEXED && enable_indexing));

		if (mesh->type == lf::MeshType::TRIANGLES) {
			mesh->vertices.reserve(6 + 6 + mesh->vertices.size());

			mesh->vertices.emplace_back(Vec3(pos.x, pos.y, pos.z));
			mesh->vertices.emplace_back(color);
			mesh->vertices.emplace_back(Vec3(pos.x, pos.y + scale.y, pos.z));
			mesh->vertices.emplace_back(color);
			mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y + scale.y, pos.z));
			mesh->vertices.emplace_back(color);
			mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y + scale.y, pos.z));
			mesh->vertices.emplace_back(color);
			mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y, pos.z));
			mesh->vertices.emplace_back(color);
			mesh->vertices.emplace_back(Vec3(pos.x, pos.y, pos.z));
			mesh->vertices.emplace_back(color);

			mesh->vertexcount += 6;
		} else if (mesh->type == lf::MeshType::TRIANGLE_INDEXED) {
			mesh->vertices.reserve(4 + 4 + mesh->vertices.size());
			
			mesh->vertices.emplace_back(Vec3(pos.x, pos.y, pos.z));
			mesh->vertices.emplace_back(color);
			mesh->vertices.emplace_back(Vec3(pos.x, pos.y + scale.y, pos.z));
			mesh->vertices.emplace_back(color);
			mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y + scale.y, pos.z));
			mesh->vertices.emplace_back(color);
			mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y, pos.z));
			mesh->vertices.emplace_back(color);

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
	} else {
		LF_ASSERT(mesh->type == lf::MeshType::LINES);

		mesh->vertices.reserve(8 + 8 + mesh->vertices.size());

		mesh->vertices.emplace_back(Vec3(pos.x, pos.y, pos.z));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(pos.x, pos.y + scale.y, pos.z));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(pos.x, pos.y + scale.y, pos.z));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y + scale.y, pos.z));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y + scale.y, pos.z));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y, pos.z));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(pos.x + scale.x, pos.y, pos.z));
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(Vec3(pos.x, pos.y, pos.z));
		mesh->vertices.emplace_back(color);

		mesh->vertexcount += 8;
	}
}

void lf::RenderLine(Mesh* mesh, const std::vector<Vec3>& vertices, const Vec3& color) {
	LF_ASSERT(mesh->layout == lf::Vertex3D);
	LF_ASSERT(mesh->type == lf::MeshType::LINES);
	LF_ASSERT(vertices.size() % 2 == 0);

	mesh->vertices.reserve(2*vertices.size() + mesh->vertices.size());

	for (int i = 0; i < vertices.size(); i += 2) {
		mesh->vertices.emplace_back(vertices[i + 0]);
		mesh->vertices.emplace_back(color);
		mesh->vertices.emplace_back(vertices[i + 1]);
		mesh->vertices.emplace_back(color);
	}
}

void lf::RenderLine(Mesh* mesh, const Vec3& v0, const Vec3& v1, const Vec3& color) {
	LF_ASSERT(mesh->layout == lf::Vertex3D);
	LF_ASSERT(mesh->type == lf::MeshType::LINES);

	mesh->vertices.reserve(2 + 2 + mesh->vertices.size());

	mesh->vertices.emplace_back(v0);
	mesh->vertices.emplace_back(color);
	mesh->vertices.emplace_back(v1);
	mesh->vertices.emplace_back(color);
}

void lf::RenderPoint(Mesh* mesh, const std::vector<Vec3>& vertices, const Vec3& color) {
	LF_ASSERT(mesh->layout == lf::Vertex3D);
	LF_ASSERT(mesh->type == lf::MeshType::POINTS);

	mesh->vertices.reserve(2*vertices.size() + mesh->vertices.size());

	for (int i = 0; i < vertices.size(); i ++) {
		mesh->vertices.emplace_back(vertices[i]);
		mesh->vertices.emplace_back(color);
	}
}

void lf::RenderPoint(Mesh* mesh, const Vec3& v, const Vec3& color) {
	LF_ASSERT(mesh->layout == lf::Vertex3D);
	LF_ASSERT(mesh->type == lf::MeshType::LINES);

	mesh->vertices.reserve(1 + 1 + mesh->vertices.size());

	mesh->vertices.emplace_back(v);
	mesh->vertices.emplace_back(color);
}