#pragma once

#include "../define.h"

typedef uint8_t BlockId;

enum BlockTypes {
	AIR,
	TRANSPARENT,
	SOLID,
};

struct Block {
	BlockTypes type;
	uint32_t idx;
	Vec2 uv0 = Vec2(0, 0), uv1 = Vec2(1, 1);
};

class BlockRegistry {
	BlockRegistry() {}

	std::vector<Block> block_array;
	BlockId next_id = 0;

public:
	static BlockRegistry* SharedInstance() {
		static BlockRegistry instance;
		return &instance;
	}

	BlockId AddBlock(const Block& block) {
		block_array.push_back(block);
		return next_id++;
	}

	Block& GetBlock(const BlockId& id) {
		return block_array[id];
	}
};