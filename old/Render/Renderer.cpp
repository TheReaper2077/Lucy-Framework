#include "Renderer.h"

std::shared_ptr<Renderer> rendercontext;

void InitRenderer() {
	assert(rendercontext == nullptr);

	OpenGL_CreateContext();

	rendercontext = std::make_shared<Renderer>();

	RegisterVertex<layout::Vertex2D>();
}

void RegisterShader(const char* name, const std::string &vs_filename, const std::string &fs_filename) {
	assert(rendercontext != nullptr);

	rendercontext->shader_store_map[name] = Shader_Create(vs_filename, fs_filename);
}

// void RegisterCamera(const char* name, Camera::Mode mode) {
// 	assert(rendercontext != nullptr);

// 	// rendercontext->camera_store_map[name] = Camera::Camera
// };

void RegisterUniformBuffer(const char* name, std::size_t size) {
	assert(rendercontext != nullptr);

	rendercontext->uniform_buffer_store_map[name] = UniformBuffer_Create();
	UniformBuffer_Allocate(rendercontext->uniform_buffer_store_map[name], size);
}

void RegisterUniformBufferRange(const char* name, uint32_t index, std::size_t size, std::size_t offset) {
	assert(rendercontext != nullptr);

	UniformBuffer_BindRange(rendercontext->uniform_buffer_store_map[name], index, size, offset);
}