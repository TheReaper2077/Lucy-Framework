#include "Lucy.h"
#include "Camera.h"

std::shared_ptr<lf::Context> rendercontext;

// ---------------------------------	// Initialize

void lf::InitContext() {
	assert(rendercontext == nullptr);

	rendercontext = std::make_shared<lf::Context>();

	OpenGL_CreateContext();
	lf::Events::InitEvents();

	lf::RegisterVertex<Vertex3D>();
	lf::RegisterVertex<Vertex2D>();

	// lf::RegisterUniformBuffer("ProjectionMatrix", sizeof(glm::mat4)*3);
	// lf::RegisterUniformBufferRange("ProjectionMatrix", 0, sizeof(glm::mat4)*3, 0);
	auto* ubo = UniformBuffer_Create();
	UniformBuffer_Allocate(ubo, sizeof(glm::mat4)*3);
	UniformBuffer_BindRange(ubo, 0, sizeof(glm::mat4)*3, 0);

	rendercontext->ubo = ubo;
}

void lf::Events::InitEvents() {
	assert(rendercontext->event_listener == nullptr);

	rendercontext->event_listener = std::make_shared<lf::Events::Listener>();

	rendercontext->event_listener->key_listener = std::make_shared<lf::Events::Key::Listener>();
	rendercontext->event_listener->mouse_listener = std::make_shared<lf::Events::Mouse::Listener>();
}

// ---------------------------------	// Create

void lf::RegisterCamera(std::string name, lf::CameraMode mode, const glm::vec3 &position) {
	assert(rendercontext != nullptr);

	auto camera = std::make_shared<lf::Camera>();

	camera->mode = mode;
	camera->Position = position;
	camera->Front = glm::vec3(0.0f, 0.0f, -1.0f);
	camera->Up = glm::vec3(0.0f, 1.0f,  0.0f);
	
	// camera->ubo = rendercontext->uniform_buffer_store_map["ProjectionMatrix"];
	camera->ubo = rendercontext->ubo;

	if (mode == lf::ORTHOGRAPHIC) {
		camera->model = glm::ortho<float>(-WIDTH/2, WIDTH/2, HEIGHT/2, -HEIGHT/2, -1000, 1000);
		camera->view = glm::mat4(1.0f);
		camera->projection = glm::mat4(1.0f);
	}
	if (mode == lf::PERSPECTIVE) {
		camera->model = glm::perspective(glm::radians(45.0f), (float)WIDTH/HEIGHT, 0.01f, 1000.0f);
		camera->view = glm::mat4(1.0f);
		camera->projection = glm::mat4(1.0f);
	}

	rendercontext->camera_store_map[name] = camera;

	// lf::EnableCamera(name);
	rendercontext->camera = camera.get();
}

// CreateMesh<T>();

// ---------------------------------	// Register

void lf::RegisterShader(std::string name, const std::string &vs_filename, const std::string &fs_filename, bool bind_ubo) {
	assert(rendercontext != nullptr);

	rendercontext->shader_store_map[name] = Shader_Create(vs_filename, fs_filename);

	Shader_BindUniformBlock(rendercontext->shader_store_map[name], "ProjectionMatrix", 0);
}

// void lf::RegisterUniformBuffer(std::string name, std::size_t size) {
// 	assert(rendercontext != nullptr);

// 	rendercontext->uniform_buffer_store_map[name] = Create();
// 	Allocate(rendercontext->uniform_buffer_store_map[name], size);
// }

// void lf::RegisterUniformBufferRange(std::string name, uint32_t index, std::size_t size, std::size_t offset) {
// 	assert(rendercontext != nullptr);
// 	assert(rendercontext->uniform_buffer_store_map[name] != nullptr);

// 	BindRange(rendercontext->uniform_buffer_store_map[name], index, size, offset);
// }

// ---------------------------------	// MVP

void lf::SetModel(const glm::mat4 &model) {
	assert(rendercontext != nullptr);

	// if (rendercontext->model == model) return;
	rendercontext->model = model;
	// AddDataDynamic(rendercontext->uniform_buffer_store_map["ProjectionMatrix"], &(rendercontext->model)[0][0], sizeof(glm::mat4), 0*sizeof(glm::mat4));
	UniformBuffer_AddDataDynamic(rendercontext->ubo, &(rendercontext->model)[0][0], sizeof(glm::mat4), 0*sizeof(glm::mat4));
}

void lf::SetView(const glm::mat4 &view) {
	assert(rendercontext != nullptr);

	// if (rendercontext->view == view) return;
	rendercontext->view = view;

	// AddDataDynamic(rendercontext->uniform_buffer_store_map["ProjectionMatrix"], &(rendercontext->view)[0][0], sizeof(glm::mat4), 1*sizeof(glm::mat4));
	UniformBuffer_AddDataDynamic(rendercontext->ubo, &(rendercontext->view)[0][0], sizeof(glm::mat4), 1*sizeof(glm::mat4));
}

void lf::SetProjection(const glm::mat4 &projection) {
	assert(rendercontext != nullptr);

	// if (rendercontext->projection == projection) return;
	rendercontext->projection = projection;
	// AddDataDynamic(rendercontext->uniform_buffer_store_map["ProjectionMatrix"], &(rendercontext->projection)[0][0], sizeof(glm::mat4), 2*sizeof(glm::mat4));
	UniformBuffer_AddDataDynamic(rendercontext->ubo, &(rendercontext->projection)[0][0], sizeof(glm::mat4), 2*sizeof(glm::mat4));
}

// RegisterVertex<T>()