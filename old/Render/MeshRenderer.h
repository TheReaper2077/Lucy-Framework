#pragma once

#include "../OpenGL/OpenGL.h"
#include "../define.h"
#include "../Math/Vec4.inl"
#include "../Math/Vec3.inl"
#include "../Math/Vec2.inl"
#include "Renderer.h"


extern std::shared_ptr<Renderer> rendercontext;

template <class T>
void RegisterVertex() {
	assert(rendercontext != nullptr);

	rendercontext->vertex_array_store_map[typeid(T).hash_code()] = Create(T::GetLayout());
}

template <typename T>
Mesh<T> *CreateMesh(MeshDrawType type, MeshIndices *meshindices = nullptr) {
	assert(rendercontext != nullptr);
	assert(rendercontext->vertex_array_store_map.find(typeid(T).hash_code()) != rendercontext->vertex_array_store_map.end());

	auto mesh = std::make_shared<Mesh<T>>();
	
	rendercontext->mesh_store.push_back(std::static_pointer_cast<MeshTemplate>(mesh));
	
	mesh->type = type;
	mesh->vbo = VertexBuffer_Create();

	if (meshindices != nullptr) {
		mesh->meshindices = meshindices;
		mesh->meshindices->shared = true;
	} else if (type == INDEXED_LINES || type == INDEXED_TRIANGLES || type == INDEXED_POINTS) {
		mesh->meshindices = new MeshIndices();
		mesh->meshindices->shared = false;
		mesh->meshindices->ebo = IndexBuffer_Create(rendercontext->vertex_array_store_map[typeid(T).hash_code()]);
	}

	return mesh.get();
}

template <typename T>
void TransferMeshData(Mesh<T> *mesh, int offset = 0, int count = 0) {
	assert(mesh != nullptr);

	VertexBuffer_Allocate(mesh->vbo, sizeof(T)*mesh->vertices.size());
	VertexBuffer_AddDataDynamic(mesh->vbo, mesh->vertices.data(), sizeof(T)*mesh->vertices.size());
	mesh->vertexcount = mesh->vertices.size();

	if (mesh->meshindices == nullptr) return;
	if (mesh->meshindices->shared) return;

	switch(mesh->type) {
		case INDEXED_POINTS:
			break;
		case INDEXED_LINES:
			break;
		case INDEXED_TRIANGLES:
			break;
		default:
			return;
	}

	TransferMeshIndices(mesh->meshindices);
};

template <typename T>
void RenderMesh(Mesh<T> *mesh, Shader *shader, Vec3 offset = Vec3()) {
	assert(mesh != nullptr);

	auto* vao = rendercontext->vertex_array_store_map[typeid(T).hash_code()];
	Shader_Bind(shader);
	Shader_SetUniformVec3(shader, "offset", &offset[0]);

	Bind(vao);
	BindVertexBuffer(vao, mesh->vbo, sizeof(T));

	for (auto& pair: mesh->tex_index_map) {
		Texture_BindUnit(pair.first, pair.second);
	}

	switch(mesh->type) {
		case POINTS:
			glDrawArrays(GL_POINTS, 0, mesh->vertexcount);
			break;
			
		case LINES:
			glDrawArrays(GL_LINES, 0, mesh->vertexcount);
			break;
			
		case TRIANGLES:
			glDrawArrays(GL_TRIANGLES, 0, mesh->vertexcount);
			break;
			
		case INDEXED_POINTS:
			BindIndexBuffer(vao, mesh->meshindices->ebo);
			glDrawElements(GL_POINTS, mesh->meshindices->indexcount, GL_UNSIGNED_INT, nullptr);
			break;
			
		case INDEXED_LINES:
			BindIndexBuffer(vao, mesh->meshindices->ebo);
			glDrawElements(GL_LINES, mesh->meshindices->indexcount, GL_UNSIGNED_INT, nullptr);
			break;

		case INDEXED_TRIANGLES:
			BindIndexBuffer(vao, mesh->meshindices->ebo);
			glDrawElements(GL_TRIANGLES, mesh->meshindices->indexcount, GL_UNSIGNED_INT, nullptr);
			break;
	}
}
