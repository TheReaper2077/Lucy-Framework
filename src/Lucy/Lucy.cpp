#include "Lucy.h"

std::shared_ptr<lf::Lucy> lf_context;

void lf::CreateContext() {
	assert(lf_context == nullptr);

	OpenGL_CreateContext();

	lf_context = std::make_shared<lf::Lucy>();
	lf_context->event = std::make_shared<lf::Events>();

	lf::RegisterLayout(lf::Layout::Vertex3D, {
		{0, 3, GL_FLOAT},
		{1, 3, GL_FLOAT},
	});
	lf::RegisterLayout(lf::Layout::Vertex3DNormal, {
		{0, 3, GL_FLOAT},
		{1, 3, GL_FLOAT},
		{2, 3, GL_FLOAT},
	});

	lf_context->mvp_ubo = UniformBuffer_Create();
	UniformBuffer_Allocate(lf_context->mvp_ubo, 3*sizeof(glm::mat4));
	UniformBuffer_BindRange(lf_context->mvp_ubo, 0, 3*sizeof(glm::mat4));
}

void lf::RegisterLayout(Layout layout, const std::vector<VertexArrayLayout> &layouts) {
	assert(lf_context != nullptr);

	lf_context->layout_vao_map[layout] = VertexArray_Create(layouts);
}

void lf::SetModel(const glm::mat4& model) {
	assert(lf_context != nullptr);

	if (lf_context->model == model) return;
	lf_context->model = model;

	UniformBuffer_AddDataDynamic(lf_context->mvp_ubo, &lf_context->model[0][0], sizeof(glm::mat4), 0*sizeof(glm::mat4));
}

void lf::SetView(const glm::mat4& view) {
	assert(lf_context != nullptr);

	if (lf_context->view == view) return;
	lf_context->view = view;
	UniformBuffer_AddDataDynamic(lf_context->mvp_ubo, &lf_context->view[0][0], sizeof(glm::mat4), 1*sizeof(glm::mat4));
}

void lf::SetProjection(const glm::mat4& projection) {
	assert(lf_context != nullptr);

	if (lf_context->projection == projection) return;
	lf_context->projection = projection;
	UniformBuffer_AddDataDynamic(lf_context->mvp_ubo, &lf_context->projection[0][0], sizeof(glm::mat4), 2*sizeof(glm::mat4));
}
