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

Shader* lf::RegisterShader(std::string name, std::string vs_filename, std::string fs_filename) {
	assert(lf_context != nullptr);
	assert(lf_context->shader_map.find(name) == lf_context->shader_map.end());

	auto* shader = Shader_Create(vs_filename, fs_filename);
	Shader_BindUniformBlock(shader, "ProjectionMatrix", 0);
	lf_context->shader_map[name] = shader;

	return shader;
}

Shader *lf::GetShader(std::string name) {
	assert(lf_context != nullptr);
	assert(lf_context->shader_map.find(name) != lf_context->shader_map.end());
	
	return lf_context->shader_map[name];
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

void lf::Update() {
	assert(lf_context != nullptr);

	lf::CameraUpdate();

	if (lf_context->camera != nullptr) {
		SetProjection(lf_context->camera->projection);
		SetView(lf_context->camera->view);
		SetModel(lf_context->camera->model);
	}

	lf_context->end_time = std::chrono::high_resolution_clock::now();
	lf_context->dt = std::chrono::duration<double, std::ratio<1, LF_UPS>>(lf_context->end_time - lf_context->start_time).count();
	lf_context->start_time = std::chrono::high_resolution_clock::now();
}

double& lf::GetTimeStep() {
	return lf_context->dt;
}

void lf::ToggleWireframe(bool wireframe) {
	assert(lf_context != nullptr);

	if (wireframe && !lf_context->wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		lf_context->wireframe = wireframe;
	}
	if (!wireframe && lf_context->wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		lf_context->wireframe = wireframe;
	}
}