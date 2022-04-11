#include "Lucy.h"

std::shared_ptr<lf::Lucy> lf_context;

void lf::CreateContext() {
	LF_ASSERT(lf_context == nullptr);

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
	UniformBuffer_Allocate(lf_context->mvp_ubo, 3 * sizeof(glm::mat4));
	UniformBuffer_BindRange(lf_context->mvp_ubo, 0, 3 * sizeof(glm::mat4));

	lf::DebugInit();
}

std::shared_ptr<lf::Lucy>& lf::GetContext() {
	LF_ASSERT(lf_context != nullptr);

	return lf_context;
}

void lf::RegisterLayout(Layout layout, const std::vector<VertexArrayLayout>& layouts) {
	LF_ASSERT(lf_context != nullptr);

	lf_context->layout_vao_map[layout] = VertexArray_Create(layouts);
}

Shader* lf::RegisterShader(std::string name, std::string vs_filename, std::string fs_filename, bool file, bool bind_block) {
	LF_ASSERT(lf_context != nullptr);
	LF_ASSERT(lf_context->shader_map.find(name) == lf_context->shader_map.end());

	auto* shader = Shader_Create(vs_filename, fs_filename, file);
	if (bind_block) Shader_BindUniformBlock(shader, "ProjectionMatrix", 0);
	lf_context->shader_map[name] = shader;

	return shader;
}

Shader* lf::GetShader(std::string name) {
	LF_ASSERT(lf_context != nullptr);
	LF_ASSERT(lf_context->shader_map.find(name) != lf_context->shader_map.end());

	return lf_context->shader_map[name];
}

void lf::SetModel(const glm::mat4& model) {
	LF_ASSERT(lf_context != nullptr);

	if (lf_context->model == model) return;
	lf_context->model = model;

	UniformBuffer_AddDataDynamic(lf_context->mvp_ubo, &lf_context->model[0][0], sizeof(glm::mat4), 0 * sizeof(glm::mat4));
}

void lf::SetView(const glm::mat4& view) {
	LF_ASSERT(lf_context != nullptr);

	if (lf_context->view == view) return;
	lf_context->view = view;
	UniformBuffer_AddDataDynamic(lf_context->mvp_ubo, &lf_context->view[0][0], sizeof(glm::mat4), 1 * sizeof(glm::mat4));
}

void lf::SetProjection(const glm::mat4& projection) {
	LF_ASSERT(lf_context != nullptr);

	if (lf_context->projection == projection) return;
	lf_context->projection = projection;
	UniformBuffer_AddDataDynamic(lf_context->mvp_ubo, &lf_context->projection[0][0], sizeof(glm::mat4), 2 * sizeof(glm::mat4));
}

void lf::Update() {
	LF_ASSERT(lf_context != nullptr);

	lf_context->end_time = std::chrono::high_resolution_clock::now();
	lf_context->dt = std::chrono::duration<double, std::ratio<1, LF_UPS>>(lf_context->end_time - lf_context->start_time).count();
	lf_context->start_time = std::chrono::high_resolution_clock::now();

	lf::CameraUpdate();

	auto* camera = lf_context->camera;

	if (lf_context->camera != nullptr) {
		SetProjection(camera->projection);
		SetView(camera->view);
		SetModel(camera->model);
	}

	lf::DebugUpdate();
}

double& lf::GetTimeStep() {
	return lf_context->dt;
}

void lf::ToggleWireframe(bool wireframe) {
	LF_ASSERT(lf_context != nullptr);

	if (wireframe && !lf_context->wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		lf_context->wireframe = wireframe;
	}
	if (!wireframe && lf_context->wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		lf_context->wireframe = wireframe;
	}
}