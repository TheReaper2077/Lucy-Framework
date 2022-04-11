#pragma once

#ifndef LF_API
#include "Lucy.h"
#endif

// All Templated Functions

template <typename T>
void lf::RegisterLayout(const std::vector<VertexArrayLayout>& layouts) {
	assert(lf::GetContext()->layout_vao_map.find(typeid(T).hash_code) == lf::GetContext()->layout_vao_map.end());
	
	lf::GetContext()->layout_vao_map[typeid(T).hash_code] = VertexArray_Create(layouts);
};

template <typename T>
void lf::ClearMesh(T* mesh) {
	mesh->vertexcount = 0;
	mesh->textures.clear();
	mesh->vertices.clear();

	if (mesh->meshindices != nullptr) {
		mesh->meshindices->indices.clear();
		mesh->meshindices->indexcount = 0;
	}
}

template <typename T>
lf::MeshT<T>* CreateMesh(lf::MeshType type, lf::MeshIndices* meshindices = nullptr) {

	auto mesh = std::make_shared<lf::MeshT<T>>();
	mesh->type = type;

	mesh->vertexbuffer = VertexBuffer_Create();
	mesh->vertexarray = lf::GetContext()->layout_vao_map[typeid(T).hash_code];
	
	if (type == lf::MeshType::TRIANGLE_INDEXED) {
		if (meshindices != nullptr) {
			mesh->meshindices = meshindices;

			mesh->meshindices->shared = true;
		} else {
			mesh->meshindices = lf::CreateMeshIndices();
		}

		if (mesh->meshindices->indexbuffer == nullptr) {
			mesh->meshindices->indexbuffer = IndexBuffer_Create(lf::GetContext()->layout_vao_map[typeid(T).hash_code]);
		}
	}	

	lf::GetContext()->mesh_store.push_back(std::static_pointer_cast<lf::Mesh>(mesh));

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

	if (typeid(T) == typeid(lf::Mesh)) {
		mesh->vertexcount = mesh->vertices.size()*sizeof(mesh->vertices[0]) / mesh->vertexarray->stride;
	} else {
		mesh->vertexcount = mesh->vertices.size();
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
