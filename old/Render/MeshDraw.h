#pragma once

#ifndef RENDERER
#include "Renderer.h"
#endif

struct Rect {
	int x, y, w, h;
};

template <typename T>
void BatchLines(Mesh<T> *mesh, const std::vector<Vec2> &vertices, const Vec3 color = Vec3(1, 1, 1)) {
	assert(vertices.size() % 2 == 0);

	if (mesh->type == LINES) {
		mesh->vertices.reserve(6 + mesh->vertices.size());

		for (int i = 0; i < vertices.size() / 2; i++) {
			mesh->vertices.emplace_back(layout::Vertex2D{vertices[i * 2 + 0], color});
			mesh->vertices.emplace_back(layout::Vertex2D{vertices[i * 2 + 1], color});
		}
	}
}

template <typename T>
void TextureQuad(Mesh<T> *mesh, Texture *texture, Rect *pos, Rect *uv, bool uv_normalized = false) {
	if (mesh->tex_index_map.find(texture) == mesh->tex_index_map.find(texture))
		mesh->tex_index_map[texture] = mesh->next_tex_index++;

	// lock to 8 textures for android
	assert(mesh->next_tex_index < 8);

	int index = mesh->tex_index_map[texture];
	
	if (mesh->type == TRIANGLES) {
		mesh->vertices.reserve(6 + mesh->vertices.size());
		
		if (uv_normalized) {
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x, pos->y), Vec3(uv->x, uv->y, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x, pos->y + pos->h), Vec3(uv->x, uv->y + uv->h, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x + pos->w, pos->y + pos->h), Vec3(uv->x + uv->w, uv->y + uv->h, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x + pos->w, pos->y + pos->h), Vec3(uv->x + uv->w, uv->y + uv->h, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x + pos->w, pos->y), Vec3(uv->x + uv->w, uv->y, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x, pos->y), Vec3(uv->x, uv->y, index)});
		} else {
			float x = uv->x/texture->width, y = uv->y/texture->height, w = uv->w/texture->width, h = uv->h/texture->height;

			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x, pos->y), Vec3(x, y, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x, pos->y + pos->h), Vec3(x, y + h, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x + pos->w, pos->y + pos->h), Vec3(x + w, y + h, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x + pos->w, pos->y + pos->h), Vec3(x + w, y + h, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x + pos->w, pos->y), Vec3(x + w, y, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x, pos->y), Vec3(x, y, index)});
		}

		mesh->vertexcount += 6;
	} else if (mesh->type == INDEXED_TRIANGLES) {
		mesh->vertices.reserve(4 + mesh->vertices.size());

		if (uv_normalized) {
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x, pos->y), Vec3(uv->x, uv->y, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x, pos->y + pos->h), Vec3(uv->x, uv->y + uv->h, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x + pos->w, pos->y + pos->h), Vec3(uv->x + uv->w, uv->y + uv->h, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x + pos->w, pos->y), Vec3(uv->x + uv->w, uv->y, index)});
		} else {
			float x = uv->x/texture->width, y = uv->y/texture->height, w = uv->w/texture->width, h = uv->h/texture->height;
			
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x, pos->y), Vec3(x, y, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x, pos->y + pos->h), Vec3(x, y + h, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x + pos->w, pos->y + pos->h), Vec3(x + w, y + h, index)});
			mesh->vertices.emplace_back(layout::Vertex2D{Vec2(pos->x + pos->w, pos->y), Vec3(x + w, y, index)});
		}

		if (mesh->meshindices->indexcount < mesh->vertices.size()*1.5) {
			mesh->meshindices->indices.reserve(6 + mesh->meshindices->indices.size());

			mesh->meshindices->indices.emplace_back(mesh->vertexcount + 0);
			mesh->meshindices->indices.emplace_back(mesh->vertexcount + 1);
			mesh->meshindices->indices.emplace_back(mesh->vertexcount + 2);
			mesh->meshindices->indices.emplace_back(mesh->vertexcount + 2);
			mesh->meshindices->indices.emplace_back(mesh->vertexcount + 3);
			mesh->meshindices->indices.emplace_back(mesh->vertexcount + 0);
			
			mesh->meshindices->indexcount += 6;
		}

		mesh->vertexcount += 4;
	} else {
		assert("NOT A VALID MESH TYPE FOR QUADS" && false);
	}
}
