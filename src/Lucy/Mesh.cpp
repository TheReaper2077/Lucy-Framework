#include "Lucy.h"

extern std::shared_ptr<lf::Lucy> lf_context;

lf::Mesh* lf::CreateMesh(lf::Layout layout, lf::RenderType type, lf::MeshIndices* meshindices) {
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

lf::MeshIndices* lf::CreateMeshIndices(lf::Layout layout) {
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

	VertexBuffer_Allocate(mesh->vertexbuffer, mesh->vertices.size()*sizeof(mesh->vertices[0]));
	VertexBuffer_AddDataDynamic(mesh->vertexbuffer, mesh->vertices.data(), mesh->vertices.size()*sizeof(mesh->vertices[0]));
	mesh->vertexcount = mesh->vertices.size()*sizeof(mesh->vertices[0]) / vertexarray->stride;

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

void lf::RenderMesh(Mesh* mesh, std::string name) {
	assert(lf_context != nullptr);

	lf::RenderMesh(mesh, lf_context->shader_map[name]);
}

void lf::RenderMesh(lf::Mesh* mesh, Shader* shader) {
	assert(lf_context != nullptr);
	assert(mesh != nullptr);
	assert(shader != nullptr);

	auto* vertexarray = lf_context->layout_vao_map[mesh->layout];

	int i = 0;
	for (auto& tex: mesh->textures) {
		Texture_BindUnit(tex, i++);
	}

	Shader_Bind(shader);
	VertexArray_Bind(vertexarray);
	VertexArray_BindVertexBuffer(vertexarray, mesh->vertexbuffer, vertexarray->stride);

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
			VertexArray_BindIndexBuffer(vertexarray, mesh->meshindices->indexbuffer);
			glDrawElements(GL_TRIANGLES, mesh->meshindices->indexcount, GL_UNSIGNED_INT, nullptr);
			break;
	}
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