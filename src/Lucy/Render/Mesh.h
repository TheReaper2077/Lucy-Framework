#pragma once

#include "../OpenGL/OpenGL.h"
#include "../define.h"
#include "../Math/Vec4.inl"
#include "../Math/Vec3.inl"
#include "../Math/Vec2.inl"

#ifndef RENDERER
#include "Renderer.h"
#endif

#include "Layouts.h"

struct Transform {
	Vec3 offset;
	glm::mat4 mvp;
};

enum MeshDrawType {
	POINTS,
	LINES,
	TRIANGLES,
	INDEXED_POINTS,
	INDEXED_LINES,
	INDEXED_TRIANGLES,
};

struct MeshTemplate{};

struct MeshIndices {
	std::vector<unsigned int> indices;
	uint32_t indexcount = 0;
	IndexBuffer *ebo;
	bool shared = false;

	void SetIndices(const std::vector<uint32_t> &indices) {
		this->indices = indices;
	}
	
	void SetIndices(uint32_t *indices, std::size_t size) {
		this->indices.assign(indices, indices + size);
	}
};

template <typename T>
struct Mesh: MeshTemplate {
	MeshDrawType type;

	MeshIndices *meshindices = nullptr;

	std::vector<T> vertices;
	uint32_t vertexcount = 0;
	VertexBuffer *vbo;

	Transform transform;

	std::map<Texture*, uint32_t> tex_index_map;
	uint32_t next_tex_index = 0;

	void SetVertices(const std::vector<T> &vertices) {
		this->vertices = vertices;
	}

	void SetVertices(T *vertices, std::size_t size) {
		this->vertices.assign(vertices, vertices + size);
	}

	void Clear() {
		vertices.clear();
		if (meshindices != nullptr)
			meshindices->indices.clear();
	}
};

void TransferMeshIndices(MeshIndices *meshindices);
MeshIndices *CreateMeshIndices();