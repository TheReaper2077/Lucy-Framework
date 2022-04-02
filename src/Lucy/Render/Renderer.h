#pragma once

#include "../OpenGL/OpenGL.h"
#include "../define.h"
#include "../Math/Vec4.inl"
#include "../Math/Vec3.inl"
#include "../Math/Vec2.inl"

#define RENDERER

#include "Mesh.h"
#include "Camera.h"

struct Renderer {
	std::map<std::size_t, VertexArray*> vertex_array_store_map;
	std::map<const char*, UniformBuffer*> uniform_buffer_store_map;
	std::map<const char*, Shader*> shader_store_map;
	// std::map<const char*, Camera::Camera*> camera_store_map;

	std::vector<std::shared_ptr<MeshTemplate>> mesh_store;
	std::vector<std::shared_ptr<MeshIndices>> meshindices_store;
};

void InitRenderer();

void RegisterShader(const char* name);
// void RegisterCamera(const char* name, Camera::Mode mode);
void RegisterUniformBuffer(const char* name, std::size_t size);
void RegisterUniformBufferRange(const char* name, uint32_t index, std::size_t size, std::size_t offset);

template <class T>
void RegisterVertex();

#include "Mesh.h"
#include "MeshRenderer.h"
#include "MeshDraw.h"
#include "Layouts.h"
