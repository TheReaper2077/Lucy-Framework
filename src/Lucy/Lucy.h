#pragma once

#include "../OpenGL/OpenGL.h"
#include "../Math/math.h"

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

	void IsKeyPressed(int key);
	void IsKeyReleased(int key);
	void IsKeyTyping(int key);
	void IsKeyToggled(int key);

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
	void DestroyMesh(Mesh* mesh);
	void ClearMesh(Mesh* mesh);

	// 
	
	struct Lucy {
		std::vector<std::shared_ptr<Mesh>> mesh_store;
		std::vector<std::shared_ptr<MeshIndices>> meshindices_store;
		std::unordered_map<Layout, VertexArray*> layout_vao_map;
		std::shared_ptr<Events> event;
	};

	void CreateContext();
	void RegisterLayout(Layout layout, const std::vector<VertexArrayLayout> &layouts);
}