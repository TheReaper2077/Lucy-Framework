#pragma once

#include "../OpenGL/OpenGL.h"
#include "../Math/math.h"

#define LF_UPS 60

namespace lf {
	// -----------------------------------------------------------------------------Events

	struct Events {
		unsigned int key_state[GLFW_KEY_LAST + 1] = {GLFW_RELEASE};
		bool key_toggled[GLFW_KEY_LAST + 1] = {false};

		double xpos, ypos;
		unsigned int button_state[GLFW_MOUSE_BUTTON_LAST + 1] = {GLFW_RELEASE};
		bool button_toggled[GLFW_MOUSE_BUTTON_LAST + 1] = {false};
	};

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	bool IsKeyPressed(int key);
	bool IsKeyReleased(int key);
	bool IsKeyTyping(int key);
	bool IsKeyToggled(int key);

	void MouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	bool IsMousePressed(int button);
	bool IsMouseReleased(int button);
	bool IsMouseToggled(int button);
	double GetMousePosX();
	double GetMousePosY();

	// -----------------------------------------------------------------------------Mesh

	enum RenderType {
		POINTS,
		LINES,
		LINE_STRIP,
		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_INDEXED,
	};

	enum Layout {
		None,
		Vertex3D,
		Vertex3DNormal,
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

	Mesh* CreateMesh(Layout layout, RenderType type, MeshIndices* meshindices = nullptr);
	MeshIndices* CreateMeshIndices(Layout layout = Layout::None);
	void TransferMesh(Mesh* mesh);
	void TransferMeshIndices(MeshIndices* meshindices);
	void RenderMesh(Mesh* mesh, Shader* shader);
	void ClearMesh(Mesh* mesh);
	void DestroyMesh(Mesh* mesh);

	// -----------------------------------------------------------------------------Camera

	enum ProjectionMode {
		ORTHOGRAPHIC,
		PERSPECTIVE
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
		double speed = 0.05;
		float yaw = -90.0, pitch = 0;
		float lastX = WIDTH/2, lastY = HEIGHT/2;
		float zoom = 0.001f;
	};

	Camera* CreateCamera(std::string name, ProjectionMode mode);
	void EnableCamera(std::string name);
	void CameraUpdate();
	void CameraMouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos);

	// -----------------------------------------------------------------------------Tiles

	struct Tile {
		Texture *tex;
	};

	// -----------------------------------------------------------------------------Lucy
	
	struct Lucy {
		std::vector<std::shared_ptr<Mesh>> mesh_store;
		std::vector<std::shared_ptr<MeshIndices>> meshindices_store;
		std::unordered_map<Layout, VertexArray*> layout_vao_map;
		std::unordered_map<std::string, std::shared_ptr<Camera>> camera_map;

		std::shared_ptr<Events> event;

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;

		UniformBuffer *mvp_ubo;
		Camera* camera;

		double dt;
		std::chrono::steady_clock::time_point end_time;
		std::chrono::steady_clock::time_point start_time;
	};

	void CreateContext();
	void RegisterLayout(Layout layout, const std::vector<VertexArrayLayout> &layouts);

	void SetModel(const glm::mat4& model);
	void SetModel(float x, float y, float z, float zoom);
	void SetView(const glm::mat4& view);
	void SetProjection(const glm::mat4& projection);

	void Update();
	double& GetTimeStep();
}