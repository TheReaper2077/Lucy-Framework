#pragma once

#include "../OpenGL/OpenGL.h"
#include "../Math/math.h"

#define LUCY_FRAMEWORK

#define LF_UPS 60

namespace lf {
	// -----------------------------------------------------------------------------Events

	struct Events;

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

	struct MeshIndices;

	struct Mesh;

	Mesh* CreateMesh(Layout layout, RenderType type, MeshIndices* meshindices = nullptr);
	MeshIndices* CreateMeshIndices(Layout layout = Layout::None);
	void TransferMesh(Mesh* mesh);
	void TransferMeshIndices(MeshIndices* meshindices);
	void RenderMesh(Mesh* mesh, std::string name);
	void RenderMesh(Mesh* mesh, Shader* shader);
	void ClearMesh(Mesh* mesh);
	void DestroyMesh(Mesh* mesh);

	// -----------------------------------------------------------------------------Camera

	enum ProjectionMode {
		ORTHOGRAPHIC,
		PERSPECTIVE
	};

	struct Camera;

	Camera* CreateCamera(std::string name, ProjectionMode mode);
	Camera* GetCamera(std::string name);
	void EnableCamera(std::string name);
	void CameraView(float x, float y, float z);
	void CameraView(float zoom);
	void CameraUpdate();
	void CameraMouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos);

	// -----------------------------------------------------------------------------Tiles

	typedef uint32_t TileId;

	struct Tile;

	// -----------------------------------------------------------------------------Lucy Framework
	
	struct Lucy;

	void CreateContext();
	void RegisterLayout(Layout layout, const std::vector<VertexArrayLayout> &layouts);

	Shader* RegisterShader(std::string name, std::string vs_filename, std::string fs_filename);
	Shader *GetShader(std::string name);

	void SetModel(const glm::mat4& model);
	void SetView(const glm::mat4& view);
	void SetProjection(const glm::mat4& projection);

	void Update();
	double& GetTimeStep();

	void ToggleWireframe(bool wireframe);
}

#include "Impl.h"