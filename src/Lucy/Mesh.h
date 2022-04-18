#pragma once

#include "Lucy.h"

// All Templated Functions

template <typename T>
void lf::RegisterLayout(const std::vector<VertexArrayLayout>& layouts) {
	std::size_t hash = typeid(T).hash_code();
	LF_ASSERT(lf::GetContext()->layout_vao_map.find(hash) == lf::GetContext()->layout_vao_map.end());
	
	lf::GetContext()->layout_vao_map[hash] = VertexArray_Create(layouts);
};

template <typename T>
void lf::ClearMesh(T* mesh) {
	mesh->vertexcount = 0;
	mesh->textures.clear();
	mesh->vertices.clear();
	mesh->next_texture_unit = 0;

	if (mesh->meshindices != nullptr) {
		mesh->meshindices->indices.clear();
		mesh->meshindices->indexcount = 0;
	}
}

template <typename T>
lf::MeshT<T>* lf::CreateMesh(lf::MeshType type, lf::MeshIndices* meshindices) {
	auto mesh = std::make_shared<lf::MeshT<T>>();
	mesh->type = type;

	mesh->vertexbuffer = VertexBuffer_Create();
	mesh->vertexarray = lf::GetContext()->layout_vao_map[typeid(T).hash_code()];
	
	if (type == lf::MeshType::TRIANGLE_INDEXED) {
		if (meshindices != nullptr) {
			mesh->meshindices = meshindices;

			mesh->meshindices->shared = true;
		} else {
			mesh->meshindices = lf::CreateMeshIndices();
		}

		if (mesh->meshindices->indexbuffer == nullptr) {
			mesh->meshindices->indexbuffer = IndexBuffer_Create(lf::GetContext()->layout_vao_map[typeid(T).hash_code()]);
		}
	}	

	lf::GetContext()->mesh_store.push_back(std::static_pointer_cast<lf::MeshTemplate>(mesh));

	return mesh.get();
};

template <typename T>
void lf::TransferMesh(T* mesh) {
	assert(mesh != nullptr);

	if (mesh->vertexbuffer == nullptr) {
		mesh->vertexbuffer = VertexBuffer_Create();
	}

	VertexBuffer_Allocate(mesh->vertexbuffer, mesh->vertices.size() * sizeof(mesh->vertices[0]));
	VertexBuffer_AddDataDynamic(mesh->vertexbuffer, mesh->vertices.data(), mesh->vertices.size() * sizeof(mesh->vertices[0]));

	if (typeid(T).hash_code() == typeid(lf::Mesh).hash_code()) {
		mesh->vertexcount = (uint32_t)(mesh->vertices.size()*sizeof(mesh->vertices[0]) / mesh->vertexarray->stride);
	} else {
		mesh->vertexcount = (uint32_t)(mesh->vertices.size());
	}

	if (mesh->meshindices == nullptr) return;
	if (mesh->meshindices->shared) return;
	if (mesh->type != lf::MeshType::TRIANGLE_INDEXED) return;

	TransferMeshIndices(mesh->meshindices);
};

template <typename T>
void lf::RenderMesh(T* mesh, std::string name) {
	lf::RenderMesh(mesh, lf::GetContext()->shader_map[name]);
};

template <typename T>
void lf::RenderMesh(T* mesh, Shader* shader) {
	assert(mesh != nullptr);
	assert(shader != nullptr);

	for (auto& tex: mesh->textures) {
		Texture_BindUnit(tex.first, tex.second);
	}

	Shader_Bind(shader);
	VertexArray_Bind(mesh->vertexarray);
	VertexArray_BindVertexBuffer(mesh->vertexarray, mesh->vertexbuffer, mesh->vertexarray->stride);

	switch (mesh->type) {
		case lf::MeshType::POINTS:
			glDrawArrays(GL_POINTS, 0, mesh->vertexcount);
			break;
		case lf::MeshType::LINES:
			glDrawArrays(GL_LINES, 0, mesh->vertexcount);
			break;
		case lf::MeshType::LINE_STRIP:
			glDrawArrays(GL_LINE_STRIP, 0, mesh->vertexcount);
			break;
		case lf::MeshType::TRIANGLES:
			glDrawArrays(GL_TRIANGLES, 0, mesh->vertexcount);
			break;
		case lf::MeshType::TRIANGLE_STRIP:
			glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->vertexcount);
			break;
		case lf::MeshType::TRIANGLE_INDEXED:
			VertexArray_BindIndexBuffer(mesh->vertexarray, mesh->meshindices->indexbuffer);
			glDrawElements(GL_TRIANGLES, mesh->meshindices->indexcount, GL_UNSIGNED_INT, nullptr);
			break;
	}	
};
