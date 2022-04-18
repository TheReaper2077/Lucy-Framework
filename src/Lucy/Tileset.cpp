#include "Lucy.h"

#include <nlohmann/json.hpp>

extern std::shared_ptr<lf::Lucy> lf_context;

lf::Tileset* lf::LoadTileset(std::string name, std::string filename, bool tile_array) {
	LF_ASSERT(lf_context != nullptr);
	LF_ASSERT(lf_context->tileset_map.find(name) == lf_context->tileset_map.end());

	auto tileset = std::make_shared<lf::Tileset>();

	nlohmann::json json;
	std::ifstream file(filename.c_str());
	file >> json;

	tileset->columns = json["columns"];
	// tileset->imageheight = json["imageheight"];
	// tileset->imagewidth = json["imagewidth"];
	// tileset->margin = json["margin"];
	// tileset->spacing = json["spacing"];
	// tileset->tilecount = json["tilecount"];
	// tileset->tileheight = json["tileheight"];
	// tileset->tilewidth = json["tilewidth"];
	// tileset->image = json["image"];
	// tileset->name = json["name"];
	// tileset->tilesetname = json["tilesetname"];
	// std::cout << json["transparentcolor"] << '\n';

	// std::size_t index = filename.find(tileset->name + std::string(".json"));
	// std::cout << index << '\n';
	// std::string 
	// tileset->spriteatlas = TextureArray_LoadFile(tileset->tilewidth, tileset->tileheight, tileset->name);

	lf_context->tileset_map[name] = tileset;

	return nullptr;
}
