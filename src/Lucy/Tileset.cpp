#include "Lucy.h"

#include <nlohmann/json.hpp>

extern std::shared_ptr<lf::Lucy> lf_context;

lf::Tileset* lf::LoadTileset(std::string name, std::string filename) {
	LF_ASSERT(lf_context != nullptr);
	LF_ASSERT(lf_context->tileset_map.find(name) == lf_context->tileset_map.end());

	auto tileset = std::make_shared<lf::Tileset>();

	nlohmann::json json;
	std::ifstream file(filename.c_str());
	file >> json;

	tileset->columns = json["columns"];
	tileset->imageheight = json["imageheight"];
	tileset->imagewidth = json["imagewidth"];
	tileset->margin = json["margin"];
	tileset->spacing = json["spacing"];
	tileset->tilecount = json["tilecount"];
	tileset->tileheight = json["tileheight"];
	tileset->tilewidth = json["tilewidth"];
	tileset->image = json["image"];
	tileset->name = json["name"];
	tileset->tilesetname = json["tilesetname"];
	tileset->transparentcolor = json["transparentcolor"];

	tileset->sprite_map.reserve(tileset->tilecount);

	for (int i = 0; i < tileset->tilecount; i++) {
		// tileset->sprite_map.emplace_back(lf::LoadTile());
	}

	lf_context->tileset_map[name] = tileset;

	return nullptr;
}
