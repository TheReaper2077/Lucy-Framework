#include "Lucy.h"

std::shared_ptr<lf::Lucy> lf_context;

void lf::CreateContext() {
	assert(lf_context == nullptr);

	lf_context = std::make_shared<lf::Lucy>();

	lf::RegisterLayout(lf::Layout::Vertex3D, {
		{0, 3, GL_FLOAT},
		{1, 3, GL_FLOAT},
	});
	lf::RegisterLayout(lf::Layout::Vertex3DNormal, {
		{0, 3, GL_FLOAT},
		{1, 3, GL_FLOAT},
		{2, 3, GL_FLOAT},
	});
}

void lf::RegisterLayout(Layout layout, const std::vector<VertexArrayLayout> &layouts) {
	assert(lf_context != nullptr);

	lf_context->layout_vao_map[layout] = VertexArray_Create(layouts);
}
