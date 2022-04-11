#include "Lucy.h"

#include <nlohmann/json.hpp>

extern std::shared_ptr<lf::Lucy> lf_context;

lf::Tileset* lf::LoadTileset(std::string name, std::string filename) {
	LF_ASSERT(lf_context != nullptr);
	LF_ASSERT(lf_context->tileset_map.find(name) == lf_context->tileset_map.end());

	auto tileset = std::make_shared<lf::Tileset>();

	nlohmann::json j;
	std::ifstream file(filename.c_str());
	file >> j;

	for (auto& element: j.items()) {
		if (element.key() == "columns") tileset->columns = element.value();
		if (element.key() == "imageheight") tileset->imageheight = element.value();
		if (element.key() == "imagewidth") tileset->imagewidth = element.value();
		if (element.key() == "margin") tileset->margin = element.value();
		if (element.key() == "spacing") tileset->spacing = element.value();
		if (element.key() == "tilecount") tileset->tilecount = element.value();
		if (element.key() == "tileheight") tileset->tileheight = element.value();
		if (element.key() == "tilewidth") tileset->tilewidth = element.value();
		if (element.key() == "image") tileset->image = element.value();
		if (element.key() == "name") tileset->name = element.value();
		if (element.key() == "tilesetname") tileset->tilesetname = element.value();
		if (element.key() == "transparentcolor") tileset->transparentcolor = element.value();
	}

	lf_context->tileset_map[name] = tileset;

	return nullptr;
}
