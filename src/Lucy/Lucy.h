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

	template <typename T>
	struct MeshT;
	typedef MeshT<Vec3> Mesh;

	Mesh* CreateMesh(Layout layout, RenderType type, MeshIndices* meshindices = nullptr);

	template <typename T>
	MeshT<T>* CreateMesh(RenderType type, MeshIndices* meshindices = nullptr);
	
	MeshIndices* CreateMeshIndices();
		
	template <typename T>
	void TransferMesh(T* mesh);
	
	void TransferMeshIndices(MeshIndices* meshindices);

	template <typename T>
	void RenderMesh(T* mesh, Shader* shader);
	template <typename T>
	void RenderMesh(T* mesh, std::string name);

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
	void CameraView(const Vec3 &mag);
	void CameraView(float zoom);
	void CameraUpdate();
	void CameraMouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos);

	// -----------------------------------------------------------------------------Sprites

	typedef uint32_t TileId;

	struct Tile;

	Tile* LoadTile(const char* filename, const Vec2& pos, const Vec2& scale);
	Tile* LoadTile(Texture *texture, const Vec2& pos, const Vec2& scale);
	Tile* GetTile(TileId id);

	// -----------------------------------------------------------------------------Lucy Framework
	
	struct Lucy;

	void CreateContext();
	std::shared_ptr<lf::Lucy>& GetContext();
	void RegisterLayout(Layout layout, const std::vector<VertexArrayLayout> &layouts);
	template <typename T>
	void RegisterLayout(const std::vector<VertexArrayLayout> &layouts);

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
#include "Lucy/Mesh.h"