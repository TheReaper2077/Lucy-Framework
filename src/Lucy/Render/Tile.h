// #pragma once

// #include "Lucy.h"

// namespace lf {
// 	struct Tile {
// 		Texture *tex = nullptr;
// 		Vec2 uv0 = (0, 0);
// 		Vec2 uv1 = (1, 1);

// 		Tile(Texture *tex, Vec2 pos, Vec2 size) {
// 			this->tex = tex;
// 			assert(tex != nullptr);

// 			this->uv0 = Vec2(pos.x/tex->width, pos.y/tex->height);
// 			this->uv1 = Vec2((pos.x + size.x)/tex->width, (pos.y + size.y)/tex->height);
// 		}
// 	};

// 	Tile* RegisterTile(const char* name, Texture *tex, Vec2 pos, Vec2 size);

// 	Tile* RegisterTile(const char* name, const Tile &tile);

// 	Tile* GetTile(const char* name);
// }