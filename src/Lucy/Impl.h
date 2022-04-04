#pragma once

#ifndef LUCY_FRAMEWORK
#include "Lucy.h"
#endif

namespace lf {
	struct Events {
		unsigned int key_state[GLFW_KEY_LAST + 1] = {GLFW_RELEASE};
		bool key_toggled[GLFW_KEY_LAST + 1] = {false};

		double xpos, ypos;
		unsigned int button_state[GLFW_MOUSE_BUTTON_LAST + 1] = {GLFW_RELEASE};
		bool button_toggled[GLFW_MOUSE_BUTTON_LAST + 1] = {false};
	};

	struct MeshIndices {
		std::vector<uint32_t> indices;
		IndexBuffer* indexbuffer = nullptr;
		uint32_t indexcount = 0;

		bool shared = false;
		Layout layout;
	};

	struct Mesh {
		RenderType type;
		Layout layout;
		MeshIndices* meshindices = nullptr;

		std::vector<Vec3> vertices;
		VertexBuffer* vertexbuffer = nullptr;
		uint32_t vertexcount = 0;
	};

	struct Camera {
		ProjectionMode mode;

		glm::vec3 Front;
		glm::vec3 Position;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		glm::vec3 Up;
		
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;

		bool first_mouse = true;
		float speed = 0;
		float yaw = -90.0, pitch = 0;
		float lastX = WIDTH/2, lastY = HEIGHT/2;
		float zoom = 0.001f;
	};

	struct Tile {
		Texture *tex;
		Vec2 uv0, uv1;
		TileId id;
	};

	struct Lucy  {
		std::vector<std::shared_ptr<Mesh>> mesh_store;
		std::vector<std::shared_ptr<MeshIndices>> meshindices_store;

		std::unordered_map<Layout, VertexArray*> layout_vao_map;
		std::unordered_map<std::string, std::shared_ptr<Camera>> camera_map;
		std::unordered_map<TileId, Tile> tile_id_map;

		std::shared_ptr<Events> event;

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;

		UniformBuffer *mvp_ubo;
		Camera* camera;

		double dt;
		std::chrono::steady_clock::time_point end_time;
		std::chrono::steady_clock::time_point start_time;

		bool wireframe = false;
	};
}