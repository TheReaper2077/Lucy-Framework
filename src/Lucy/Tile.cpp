#include "Lucy.h"

extern std::shared_ptr<lf::Lucy> lf_context;

lf::Tile* LoadTile(const char* filename, const Vec2& pos, const Vec2& scale) {
	return lf::LoadTile(Texture_LoadFile(filename), pos, scale);
}

lf::Tile* lf::LoadTile(Texture *texture, const Vec2& pos, const Vec2& scale) {
	assert(lf_context != nullptr);

	auto sprite = std::make_shared<lf::Tile>();

	sprite->texture = texture;
	sprite->uv0 = pos / Vec2(texture->width, texture->height);
	sprite->uv1 = (pos + scale) / Vec2(texture->width, texture->height);
	sprite->id = lf_context->next_spriteid++;

	lf_context->sprite_id_map[sprite->id] = sprite;

	return sprite.get();
}

lf::Tile* lf::GetTile(lf::TileId id) {
	assert(lf_context != nullptr);
	
	return lf_context->sprite_id_map[id].get();
}