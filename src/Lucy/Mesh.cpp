#include "Lucy.h"

extern std::shared_ptr<lf::Lucy> lf_context;

lf::Mesh* CreateMesh(lf::Layout layout, lf::RenderType type, lf::MeshIndices* meshindices) {
	assert(lf_context != nullptr);

	auto mesh = std::make_shared<lf::Mesh>();
	mesh->layout = layout;
	mesh->type = type;

	mesh->vertexbuffer = VertexBuffer_Create();
	
	if (type == lf::RenderType::TRIANGLE_INDEXED) {
		if (meshindices != nullptr) {
			mesh->meshindices = meshindices;

			if (!mesh->meshindices->shared) {
				mesh->meshindices->layout = layout;
				mesh->meshindices->shared = true;
			} else {
				assert(mesh->meshindices->layout == layout);
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

lf::MeshIndices* lf::CreateMeshIndices(lf::Layout layout = lf::Layout::None) {
	assert(lf_context != nullptr);

	auto meshindices = std::make_shared<lf::MeshIndices>();

	meshindices->shared = false;

	if (layout != lf::Layout::None) {
		meshindices->layout = layout;
		meshindices->indexbuffer = IndexBuffer_Create(lf_context->layout_vao_map[layout]);
	}
	
	lf_context->meshindices_store.push_back(meshindices);

	return meshindices.get();
}

void lf::TransferMesh(lf::Mesh* mesh) {
	assert(lf_context != nullptr);

	if (mesh->vertexbuffer == nullptr) {
		mesh->vertexbuffer = VertexBuffer_Create();
	}

	auto* vertexarray = lf_context->layout_vao_map[mesh->layout];

	VertexBuffer_Allocate(mesh->vertexbuffer, vertexarray->stride*mesh->vertices.size());
	VertexBuffer_AddDataDynamic(mesh->vertexbuffer, mesh->vertices.data(), vertexarray->stride*mesh->vertices.size());
	mesh->vertexcount = mesh->vertices.size();

	if (mesh->meshindices == nullptr) return;
	if (mesh->meshindices->shared) return;
	if (mesh->type != lf::RenderType::TRIANGLE_INDEXED) return;

	TransferMeshIndices(mesh->meshindices);
}

void lf::TransferMeshIndices(lf::MeshIndices* meshindices) {
	assert(meshindices->indexbuffer != nullptr);

	IndexBuffer_AddData(meshindices->indexbuffer, meshindices->indices.data(), meshindices->indices.size()*sizeof(uint32_t));
	meshindices->indexcount = meshindices->indices.size();
}

void lf::RenderMesh(lf::Mesh *mesh, Shader *shader) {
	assert(lf_context != nullptr);
	assert(mesh != nullptr);
	assert(shader != nullptr);

	auto* vao = lf_context->layout_vao_map[mesh->layout];

	VertexArray_Bind(vao);
	VertexArray_BindVertexBuffer(vao, mesh->vertexbuffer, vao->stride);

	switch (mesh->type) {
		case lf::RenderType::POINTS:
			glDrawArrays(GL_POINTS, 0, mesh->vertexcount);
			break;
		case lf::RenderType::LINES:
			glDrawArrays(GL_LINES, 0, mesh->vertexcount);
			break;
		case lf::RenderType::LINE_STRIP:
			glDrawArrays(GL_LINE_STRIP, 0, mesh->vertexcount);
			break;
		case lf::RenderType::TRIANGLES:
			glDrawArrays(GL_TRIANGLES, 0, mesh->vertexcount);
			break;
		case lf::RenderType::TRIANGLE_STRIP:
			glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->vertexcount);
			break;
		case lf::RenderType::TRIANGLE_INDEXED:
			glDrawElements(GL_TRIANGLES, mesh->meshindices->indexcount, GL_UNSIGNED_INT, nullptr);
			break;
	}
}