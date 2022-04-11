#pragma once

#ifndef LF_API
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

	template <typename T> struct MeshT {
		MeshType type;
		Layout layout;
		
		MeshIndices* meshindices = nullptr;
		VertexBuffer* vertexbuffer = nullptr;
		VertexArray* vertexarray = nullptr;

		std::vector<T> vertices;
		std::unordered_map<Texture*, uint32_t> textures;
		uint32_t next_texture_unit = 0;
		uint32_t vertexcount = 0;
	};

	struct Camera {
		ProjectionMode mode;

		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;

		bool first_mouse = true;
		float speed = 0;
		float yaw = -90.0, pitch = 0;
		float lastX = WIDTH/2, lastY = HEIGHT/2;
		float zoom = 0.001f;

		bool mouse_enabled = false;
		bool keyboard_enabled = true;

		std::string name;
	};

	struct TexTile {
		TexTileId id;
		Texture *texture;
		Vec2 uv0, uv1;
	};

	struct Tileset {
		int columns;
		int imageheight;
		int imagewidth;
		int margin;
		int spacing;
		int tilecount;
		int tileheight;
		int tilewidth;
		std::string image;
		std::string name;
		std::string tilesetname;
		std::string transparentcolor;

		std::unordered_map<SpriteId, TexTile*> sprite_map;
		
		TextureArray *spriteatlas = nullptr;
	};

	struct Lucy  {
		std::vector<std::shared_ptr<Mesh>> mesh_store;
		std::vector<std::shared_ptr<MeshIndices>> meshindices_store;

		std::unordered_map<std::size_t, VertexArray*> layout_vao_map;
		std::unordered_map<std::string, Shader*> shader_map;
		std::unordered_map<std::string, std::shared_ptr<Camera>> camera_map;
		std::unordered_map<TexTileId, std::shared_ptr<TexTile>> sprite_id_map;
		std::unordered_map<std::string, std::shared_ptr<Tileset>> tileset_map;

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

		TexTileId next_spriteid = 0;
	};
}
