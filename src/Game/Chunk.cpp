#include "Chunk.h"

BlockId& GetBlock(Chunk *chunk, glm::ivec3 &pos) {
	return chunk->blocks[INDEX_VEC(pos)];
}

void AddBlock(Chunk *chunk, const glm::ivec3 &pos, BlockId id) {
	chunk->blocks[INDEX_VEC(pos)] = id;
}

void MeshChunk(Chunk* chunk, Chunk* top, Chunk* bottom, Chunk* left, Chunk* right, Chunk* near, Chunk* far) {
	for (int z = 0; z < CHUNK_SIZE; z++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				if (chunk->blocks[INDEX(x, y, z)] == 0) {
					continue;
				}

				// if (chunk->blocks[INDEX(x, y, z + 1)] == 1)
			}
		}
	}
}

