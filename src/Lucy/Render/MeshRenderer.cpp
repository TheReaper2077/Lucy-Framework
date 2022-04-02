#pragma once

#ifndef RENDERER
#include "Renderer.h"
#endif

<<<<<<< HEAD:src/Lucy/MeshRenderer.cpp
extern std::shared_ptr<lf::Context> rendercontext;

void lf::TransferMeshIndices(lf::MeshIndices *meshindices) {
=======
extern std::shared_ptr<Renderer> rendercontext;

void TransferMeshIndices(MeshIndices *meshindices) {
>>>>>>> parent of 1b39039 (refractor):src/Render/MeshRenderer.cpp
	assert(meshindices != nullptr);

	IndexBuffer_AddData(meshindices->ebo, meshindices->indices.data(), sizeof(uint32_t)*meshindices->indices.size());
	meshindices->indexcount = meshindices->indices.size();
};

<<<<<<< HEAD:src/Lucy/MeshRenderer.cpp
lf::MeshIndices *lf::CreateMeshIndices() {
	assert(rendercontext != nullptr);

	auto meshindices = std::make_shared<lf::MeshIndices>();
=======
MeshIndices *CreateMeshIndices() {
	assert(rendercontext != nullptr);

	auto meshindices = std::make_shared<MeshIndices>();
>>>>>>> parent of 1b39039 (refractor):src/Render/MeshRenderer.cpp

	rendercontext->meshindices_store.push_back(meshindices);

	return meshindices.get();
}