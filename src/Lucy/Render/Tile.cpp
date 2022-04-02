// #include "Tile.h"

// std::shared_ptr<lf::Context> rendercontext;

// lf::Tile* lf::RegisterTile(const char* name, Texture *tex, Vec2 pos, Vec2 size) {
// 	assert(rendercontext != nullptr);
// 	assert(tex != nullptr);

// 	rendercontext->tile_store_map[name] = lf::Tile{tex, pos, size};

// 	return &rendercontext->tile_store_map[name];
// }

// lf::Tile* lf::RegisterTile(const char* name, const lf::Tile &tile) {
// 	assert(rendercontext != nullptr);

// 	rendercontext->tile_store_map[name] = tile;

// 	return &rendercontext->tile_store_map[name];
// }

// lf::Tile* lf::GetTile(const char* name) {
// 	return &rendercontext->tile_store_map[name];
// }

