#include "Lucy.h"

extern std::shared_ptr<lf::Lucy> lf_context;

lf::Mesh* lf::CreateMesh(lf::Layout layout, lf::RenderType type, lf::MeshIndices* meshindices) {
	assert(lf_context != nullptr);

	auto mesh = std::make_shared<lf::Mesh>();
	mesh->layout = layout;
	mesh->type = type;

	mesh->vertexbuffer = VertexBuffer_Create();
	mesh->vertexarray = lf_context->layout_vao_map[layout];

	if (type == lf::RenderType::TRIANGLE_INDEXED) {
		if (meshindices != nullptr) {
			mesh->meshindices = meshindices;

			if (!mesh->meshindices->shared) {
				
				mesh->meshindices->shared = true;
			}
		} else {
			mesh->meshindices = lf::CreateMeshIndices();
		}

		if (mesh->meshindices->indexbuffer == nullptr) {
			mesh->meshindices->indexbuffer = IndexBuffer_Create(lf_context->layout_vao_map[layout]);
		}
	}	

	lf_context->mesh_store.push_back(mesh);

	return mesh.get();
}

lf::MeshIndices* lf::CreateMeshIndices() {
	assert(lf_context != nullptr);

	auto meshindices = std::make_shared<lf::MeshIndices>();

	meshindices->shared = false;
	
	lf_context->meshindices_store.push_back(meshindices);

	return meshindices.get();
}

void lf::TransferMeshIndices(lf::MeshIndices* meshindices) {
	assert(meshindices->indexbuffer != nullptr);

	IndexBuffer_AddData(meshindices->indexbuffer, meshindices->indices.data(), meshindices->indices.size()*sizeof(uint32_t));
	meshindices->indexcount = meshindices->indices.size();
}

void lf::ClearMesh(lf::Mesh* mesh) {
	mesh->vertexcount = 0;
	mesh->textures.clear();
	mesh->vertices.clear();

	if (mesh->meshindices != nullptr) {
		mesh->meshindices->indices.clear();
		mesh->meshindices->indexcount = 0;
	}
}