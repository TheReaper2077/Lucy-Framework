#pragma once

#include "../define.h"
#include "Block.h"
#include "../Lucy/Lucy.h"

#define CHUNK_SIZE 16
#define INDEX(x, y, z) x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE
#define INDEX_VEC(pos) (pos.x & 15) + (pos.y & 15) * CHUNK_SIZE + (pos.z & 15) * CHUNK_SIZE * CHUNK_SIZE

template <typename T>
void rect_NEAR(std::vector<T> &vertices, const float& x, const float& y, const float& z, const float& w, const float& h, const float& d, const Vec2& uv0, const Vec2& uv1, const float& idx, const Vec3& normal) {
	vertices.emplace_back(T{ Vec3(x, y, z), Vec3(uv0.x, uv0.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x + w, y, z), Vec3(uv1.x, uv0.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x + w, y + h, z), Vec3(uv1.x, uv1.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x, y + h, z), Vec3(uv0.x, uv1.y, idx), normal });
};

template <typename T>
void rect_FAR(std::vector<T> &vertices, const float& x, const float& y, const float& z, const float& w, const float& h, const float& d, const Vec2& uv0, const Vec2& uv1, const float& idx, const Vec3& normal) {
	vertices.emplace_back(T{ Vec3(x, y, z + d), Vec3(uv0.x, uv0.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x + w, y, z + d), Vec3(uv1.x, uv0.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x + w, y + h, z + d), Vec3(uv1.x, uv1.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x, y + h, z + d), Vec3(uv0.x, uv1.y, idx), normal });
};
	
template <typename T>
void rect_TOP(std::vector<T> &vertices, const float& x, const float& y, const float& z, const float& w, const float& h, const float& d, const Vec2& uv0, const Vec2& uv1, const float& idx, const Vec3& normal) {
	vertices.emplace_back(T{ Vec3(x, y + h, z), Vec3(uv0.x, uv0.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x + w, y + h, z), Vec3(uv1.x, uv0.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x + w, y + h, z + d), Vec3(uv1.x, uv1.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x, y + h, z + d), Vec3(uv0.x, uv1.y, idx), normal });
};
	
template <typename T>
void rect_BOTTOM(std::vector<T> &vertices, const float& x, const float& y, const float& z, const float& w, const float& h, const float& d, const Vec2& uv0, const Vec2& uv1, const float& idx, const Vec3& normal) {
	vertices.emplace_back(T{ Vec3(x, y, z), Vec3(uv0.x, uv0.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x + w, y, z), Vec3(uv1.x, uv0.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x + w, y, z + d), Vec3(uv1.x, uv1.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x, y, z + d), Vec3(uv0.x, uv1.y, idx), normal });
};
	
template <typename T>
void rect_LEFT(std::vector<T> &vertices, const float& x, const float& y, const float& z, const float& w, const float& h, const float& d, const Vec2& uv0, const Vec2& uv1, const float& idx, const Vec3& normal) {
	vertices.emplace_back(T{ Vec3(x + w, y, z), Vec3(uv0.x, uv0.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x + w, y, z + d), Vec3(uv1.x, uv0.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x + w, y + h, z + d), Vec3(uv1.x, uv1.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x + w, y + h, z), Vec3(uv0.x, uv1.y, idx), normal });
};
	
template <typename T>
void rect_RIGHT(std::vector<T> &vertices, const float& x, const float& y, const float& z, const float& w, const float& h, const float& d, const Vec2& uv0, const Vec2& uv1, const float& idx, const Vec3& normal) {
	vertices.emplace_back(T{ Vec3(x, y, z), Vec3(uv0.x, uv0.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x, y, z + d), Vec3(uv1.x, uv0.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x, y + h, z + d), Vec3(uv1.x, uv1.y, idx), normal });
	vertices.emplace_back(T{ Vec3(x, y + h, z), Vec3(uv0.x, uv1.y, idx), normal });
};

struct Vertex {
	Vec3 position;
	Vec3 uv;
	const Vec3& normals;
};

struct Chunk {
	BlockId blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
	bool visible = true;

	// lf::MeshT<Vertex> mesh
};

BlockId& GetBlock(Chunk* chunk, const glm::ivec3& pos);
void AddBlock(Chunk* chunk, const glm::ivec3& pos, BlockId id);
void MeshChunk(Chunk* chunk, Chunk* top, Chunk* bottom, Chunk* left, Chunk* right, Chunk* near, Chunk* far);
void RenderChunk(Chunk *chunk);
