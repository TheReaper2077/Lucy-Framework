#include "Lucy.h"

std::shared_ptr<lf::Lucy> lf_context;

const std::string color_vs =
"#version 400 core\n"
"layout (location=0) in vec3 v_pos;\n"
"layout (location=1) in vec3 v_attr;\n"
"uniform mat4 u_mvp;\n"
"out vec3 f_attr;\n"
"void main() {\n"
"\tf_attr = v_attr;\n"
"\tgl_Position = u_mvp * vec4(v_pos, 1.0f);\n"
"}";

const std::string color_fs =
"#version 400 core\n"
"in vec3 f_attr;\n"
"void main() {\n"
"\tgl_FragColor = vec4(f_attr, 1.0f);\n"
"}";

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
	UniformBuffer_Allocate(lf_context->mvp_ubo, 3 * sizeof(glm::mat4));
	UniformBuffer_BindRange(lf_context->mvp_ubo, 0, 3 * sizeof(glm::mat4));

	lf::RegisterShader("3d_ui", color_vs, color_fs, false, false);
}

std::shared_ptr<lf::Lucy>& lf::GetContext() {
	assert(lf_context != nullptr);

	return lf_context;
}

void lf::RegisterLayout(Layout layout, const std::vector<VertexArrayLayout>& layouts) {
	assert(lf_context != nullptr);

	lf_context->layout_vao_map[layout] = VertexArray_Create(layouts);
}

Shader* lf::RegisterShader(std::string name, std::string vs_filename, std::string fs_filename, bool file, bool bind_block) {
	assert(lf_context != nullptr);
	assert(lf_context->shader_map.find(name) == lf_context->shader_map.end());

	auto* shader = Shader_Create(vs_filename, fs_filename, file);
	if (bind_block) Shader_BindUniformBlock(shader, "ProjectionMatrix", 0);
	lf_context->shader_map[name] = shader;

	return shader;
}

Shader* lf::GetShader(std::string name) {
	assert(lf_context != nullptr);
	assert(lf_context->shader_map.find(name) != lf_context->shader_map.end());

	return lf_context->shader_map[name];
}

void lf::SetModel(const glm::mat4& model) {
	assert(lf_context != nullptr);

	if (lf_context->model == model) return;
	lf_context->model = model;

	UniformBuffer_AddDataDynamic(lf_context->mvp_ubo, &lf_context->model[0][0], sizeof(glm::mat4), 0 * sizeof(glm::mat4));
}

void lf::SetView(const glm::mat4& view) {
	assert(lf_context != nullptr);

	if (lf_context->view == view) return;
	lf_context->view = view;
	UniformBuffer_AddDataDynamic(lf_context->mvp_ubo, &lf_context->view[0][0], sizeof(glm::mat4), 1 * sizeof(glm::mat4));
}

void lf::SetProjection(const glm::mat4& projection) {
	assert(lf_context != nullptr);

	if (lf_context->projection == projection) return;
	lf_context->projection = projection;
	UniformBuffer_AddDataDynamic(lf_context->mvp_ubo, &lf_context->projection[0][0], sizeof(glm::mat4), 2 * sizeof(glm::mat4));
}

void lf::Update() {
	assert(lf_context != nullptr);

	lf_context->end_time = std::chrono::high_resolution_clock::now();
	lf_context->dt = std::chrono::duration<double, std::ratio<1, LF_UPS>>(lf_context->end_time - lf_context->start_time).count();
	lf_context->start_time = std::chrono::high_resolution_clock::now();

	lf::CameraUpdate();

	auto* camera = lf_context->camera;

	if (lf_context->camera != nullptr) {
		SetProjection(camera->projection);
		SetView(camera->view);
		SetModel(camera->model);

		if (camera->mode == lf::ProjectionMode::PERSPECTIVE) {
			Shader_SetUniformMat4(lf::GetShader("3d_ui"), "u_mvp", &(camera->projection * camera->view)[0][0]);
		}
	}

	static Vec3 mag;

	if (ImGui::Begin("Scene")) {
		if (ImGui::CollapsingHeader("Camera")) {
			ImGui::InputFloat("Speed", &camera->speed);
			ImGui::InputFloat3("Position", &camera->Position[0]);
			if (camera->mode == lf::ProjectionMode::PERSPECTIVE) {
				ImGui::InputFloat3("Direction", &camera->Front[0]);
			}
			ImGui::SliderFloat3("Scene Rotation", &mag[0], 0, 360, nullptr, 1);

			lf::CameraView(mag);
		}
	}
	ImGui::End();

	if (camera->mode == lf::ProjectionMode::PERSPECTIVE) {
		static lf::Mesh* ui_mesh;

		if (ui_mesh == nullptr) {
			ui_mesh = lf::CreateMesh(lf::Vertex3D, lf::RenderType::LINES);
		}

		glm::vec3 tmp = camera->Position + camera->Front * 10.0f;

		ui_mesh->vertices.reserve(ui_mesh->vertices.size() + 4 * 3);

		ui_mesh->vertices.emplace_back(Vec3(tmp.x, tmp.y, tmp.z));
		ui_mesh->vertices.emplace_back(Vec3(1, 0, 0));
		ui_mesh->vertices.emplace_back(Vec3(tmp.x + 1, tmp.y, tmp.z));
		ui_mesh->vertices.emplace_back(Vec3(1, 0, 0));

		ui_mesh->vertices.emplace_back(Vec3(tmp.x, tmp.y, tmp.z));
		ui_mesh->vertices.emplace_back(Vec3(0, 0, 1));
		ui_mesh->vertices.emplace_back(Vec3(tmp.x, tmp.y + 1, tmp.z));
		ui_mesh->vertices.emplace_back(Vec3(0, 0, 1));

		ui_mesh->vertices.emplace_back(Vec3(tmp.x, tmp.y, tmp.z));
		ui_mesh->vertices.emplace_back(Vec3(0, 1, 0));
		ui_mesh->vertices.emplace_back(Vec3(tmp.x, tmp.y, tmp.z + 1));
		ui_mesh->vertices.emplace_back(Vec3(0, 1, 0));

		glClear(GL_DEPTH_BUFFER_BIT);

		lf::TransferMesh(ui_mesh);
		lf::RenderMesh(ui_mesh, "3d_ui");
		lf::ClearMesh(ui_mesh);
	}
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