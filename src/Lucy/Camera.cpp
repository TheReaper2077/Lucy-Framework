#include "Lucy.h"

extern std::shared_ptr<lf::Lucy> lf_context;

void lf::CreateCamera(std::string name, ProjectionMode mode) {
	auto camera = std::make_shared<lf::Camera>();

	if (mode == lf::ORTHOGRAPHIC) {
		
	}
	if (mode == lf::PERSPECTIVE) {

	}
}