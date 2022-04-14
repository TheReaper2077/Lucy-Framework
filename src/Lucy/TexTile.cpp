#include "Lucy.h"

extern std::shared_ptr<lf::Lucy> lf_context;

lf::TexTile* lf::LoadTile(const char* filename, const Vec2& pos, const Vec2& scale, bool normalized) {
	return lf::LoadTile(Texture_LoadFile(filename), pos, scale, normalized);
}

lf::TexTile* lf::LoadTile(Texture *texture, const Vec2& pos, const Vec2& scale, bool normalized) {
	LF_ASSERT(lf_context != nullptr);

	auto sprite = std::make_shared<lf::TexTile>();

	sprite->texture = texture;
	if (normalized) {
		sprite->uv0 = pos;
		sprite->uv1 = scale;
	} else {
		sprite->uv0 = pos / Vec2(texture->width, texture->height);
		sprite->uv1 = (pos + scale) / Vec2(texture->width, texture->height);
	}
	sprite->id = lf_context->next_spriteid++;

	lf_context->sprite_id_map[sprite->id] = sprite;

	return sprite.get();
}

lf::TexTile* lf::GetTile(lf::TexTileId id) {
	LF_ASSERT(lf_context != nullptr);
	
	return lf_context->sprite_id_map[id].get();
}