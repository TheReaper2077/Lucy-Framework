#include "Lucy.h"

extern std::shared_ptr<lf::Lucy> lf_context;

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

void lf::DebugInit() {
	LF_ASSERT(lf_context != nullptr);

	// lf::RegisterShader("3d_ui", color_vs, color_fs, false, false);
}

void lf::DebugUpdate() {
	if (!lf::IsKeyToggled(LF_KEY_F5)) return;

	LF_ASSERT(lf_context != nullptr);

	auto* camera = lf_context->camera;

	if (camera != nullptr) {
		static Vec3 mag;

		if (ImGui::Begin("Scene")) {
			if (ImGui::CollapsingHeader("Camera")) {
				ImGui::InputFloat("Speed", &camera->speed);
				ImGui::InputFloat3("Position", &camera->Position[0]);
				ImGui::SliderFloat3("Scene Rotation", &mag[0], 0, 360, nullptr, 1);

				lf::CameraView(mag);
			}
		}
		ImGui::End();

		if (ImGui::Begin("Debug")) {
			
		}
		ImGui::End();
	}
}



		// if (camera->mode == lf::ProjectionMode::PERSPECTIVE) {
		// 	static lf::Mesh* ui_mesh;

		// 	if (ui_mesh == nullptr) {
		// 		ui_mesh = lf::CreateMesh(lf::Vertex3D, lf::MeshType::LINES);
		// 	}

		// 	glm::vec3 tmp = camera->Position + camera->Front * 10.0f;

		// 	ui_mesh->vertices.reserve(ui_mesh->vertices.size() + 4 * 3);

		// 	ui_mesh->vertices.emplace_back(Vec3(tmp.x, tmp.y, tmp.z));
		// 	ui_mesh->vertices.emplace_back(Vec3(1, 0, 0));
		// 	ui_mesh->vertices.emplace_back(Vec3(tmp.x + 1, tmp.y, tmp.z));
		// 	ui_mesh->vertices.emplace_back(Vec3(1, 0, 0));

		// 	ui_mesh->vertices.emplace_back(Vec3(tmp.x, tmp.y, tmp.z));
		// 	ui_mesh->vertices.emplace_back(Vec3(0, 0, 1));
		// 	ui_mesh->vertices.emplace_back(Vec3(tmp.x, tmp.y + 1, tmp.z));
		// 	ui_mesh->vertices.emplace_back(Vec3(0, 0, 1));

		// 	ui_mesh->vertices.emplace_back(Vec3(tmp.x, tmp.y, tmp.z));
		// 	ui_mesh->vertices.emplace_back(Vec3(0, 1, 0));
		// 	ui_mesh->vertices.emplace_back(Vec3(tmp.x, tmp.y, tmp.z + 1));
		// 	ui_mesh->vertices.emplace_back(Vec3(0, 1, 0));

		// 	glClear(GL_DEPTH_BUFFER_BIT);

		// 	lf::TransferMesh(ui_mesh);
		// 	lf::RenderMesh(ui_mesh, "3d_ui");
		// 	lf::ClearMesh(ui_mesh);
		// }