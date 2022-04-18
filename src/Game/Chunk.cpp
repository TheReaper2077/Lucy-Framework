#include "Chunk.h"

static BlockRegistry *block_registry = BlockRegistry::SharedInstance();

void InitMesh(Chunk *chunk, lf::MeshIndices *meshindices) {
	chunk->mesh = lf::CreateMesh<Vertex>(lf::TRIANGLE_INDEXED, meshindices);
	chunk->meshed = false;
}

BlockId& GetBlock(Chunk *chunk, glm::ivec3 &pos) {
	return chunk->blocks[INDEX_VEC(pos)];
}

void AddBlock(Chunk *chunk, const glm::ivec3 &pos, BlockId id) {
	chunk->blocks[INDEX_VEC(pos)] = id;
}

void MeshChunk(Chunk* chunk, Chunk* top, Chunk* bottom, Chunk* left, Chunk* right, Chunk* near, Chunk* far) {
	chunk->meshed = true;
	
	for (int z = 0; z < CHUNK_SIZE; z++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				auto& id = chunk->blocks[INDEX(x, y, z)];
				auto& block = block_registry->GetBlock(id);

				if (block.type == AIR || block.type == TRANSPARENT)
					continue;

				if (z < CHUNK_SIZE) {
					if (block_registry->GetBlock(chunk->blocks[INDEX(x, y, z + 1)]).type == AIR)
						rect_FAR(chunk->mesh->vertices, x, y, z, 1, 1, 1, block.uv0, block.uv1, block.idx);
				} else if (far != nullptr) {
					if (block_registry->GetBlock(far->blocks[INDEX(x, y, 0)]).type == AIR)
						rect_FAR(chunk->mesh->vertices, x, y, z, 1, 1, 1, block.uv0, block.uv1, block.idx);
				}

				if (z >= 0) {
					if (block_registry->GetBlock(chunk->blocks[INDEX(x, y, z - 1)]).type == AIR) {
						rect_NEAR(chunk->mesh->vertices, x, y, z, 1, 1, 1, block.uv0, block.uv1, block.idx);
					}
				} else if (near != nullptr) {
					if (block_registry->GetBlock(near->blocks[INDEX(x, y, CHUNK_SIZE - 1)]).type == AIR)
						rect_NEAR(chunk->mesh->vertices, x, y, z, 1, 1, 1, block.uv0, block.uv1, block.idx);
				}

				if (y < CHUNK_SIZE) {
					if (block_registry->GetBlock(chunk->blocks[INDEX(x, y + 1, z)]).type == AIR) {
						rect_TOP(chunk->mesh->vertices, x, y, z, 1, 1, 1, block.uv0, block.uv1, block.idx);
					}
				} else if (top != nullptr) {
					if (block_registry->GetBlock(top->blocks[INDEX(x, 0, z)]).type == AIR)
						rect_TOP(chunk->mesh->vertices, x, y, z, 1, 1, 1, block.uv0, block.uv1, block.idx);
				}

				if (y >= 0) {
					if (block_registry->GetBlock(chunk->blocks[INDEX(x, y - 1, z)]).type == AIR) {
						rect_BOTTOM(chunk->mesh->vertices, x, y, z, 1, 1, 1, block.uv0, block.uv1, block.idx);
					}
				} else if (bottom != nullptr) {
					if (block_registry->GetBlock(bottom->blocks[INDEX(x, CHUNK_SIZE - 1, z)]).type == AIR)
						rect_BOTTOM(chunk->mesh->vertices, x, y, z, 1, 1, 1, block.uv0, block.uv1, block.idx);
				}

				if (x < CHUNK_SIZE) {
					if (block_registry->GetBlock(chunk->blocks[INDEX(x + 1, y, z)]).type == AIR) {
						rect_RIGHT(chunk->mesh->vertices, x, y, z, 1, 1, 1, block.uv0, block.uv1, block.idx);
					}
				} else if (right != nullptr) {
					if (block_registry->GetBlock(right->blocks[INDEX(0, y, z)]).type == AIR)
						rect_RIGHT(chunk->mesh->vertices, x, y, z, 1, 1, 1, block.uv0, block.uv1, block.idx);
				}

				if (x >= 0) {
					if (block_registry->GetBlock(chunk->blocks[INDEX(x - 1, y, z)]).type == AIR) {
						rect_LEFT(chunk->mesh->vertices, x, y, z, 1, 1, 1, block.uv0, block.uv1, block.idx);
					}
				} else if (left != nullptr) {
					if (block_registry->GetBlock(left->blocks[INDEX(CHUNK_SIZE - 1, y, z)]).type == AIR)
						rect_LEFT(chunk->mesh->vertices, x, y, z, 1, 1, 1, block.uv0, block.uv1, block.idx);
				}
			}
		}
	}
}

void RenderChunk(Chunk *chunk) {
	lf::RenderMesh(chunk->mesh, "texture");
}
