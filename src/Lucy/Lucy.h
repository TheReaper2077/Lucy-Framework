#pragma once

#include "../OpenGL/OpenGL.h"
#include "../Math/math.h"

// #define LF_DEBUG

#define LUCY_FRAMEWORK
#define LF_API

#ifndef LF_UPS
#define LF_UPS 60
#endif

namespace lf {
	// -----------------------------------------------------------------------------Events

	struct Events;

	LF_API void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	bool IsKeyPressed(int key);
	bool IsKeyReleased(int key);
	bool IsKeyTyping(int key);
	bool IsKeyToggled(int key);

	LF_API void MouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	LF_API void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
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

	template <typename T> struct MeshT;
	typedef MeshT<Vec3> Mesh;

	Mesh* CreateMesh(Layout layout, RenderType type, MeshIndices* meshindices = nullptr);
	template <typename T> MeshT<T>* CreateMesh(RenderType type, MeshIndices* meshindices = nullptr);
	MeshIndices* CreateMeshIndices();	
		
	LF_API template <typename T> void TransferMesh(T* mesh);	
	LF_API void TransferMeshIndices(MeshIndices* meshindices);

	LF_API template <typename T> void RenderMesh(T* mesh, Shader* shader);
	LF_API template <typename T> void RenderMesh(T* mesh, std::string name);

	LF_API void ClearMesh(Mesh* mesh);
	LF_API void DestroyMesh(Mesh* mesh);

	// -----------------------------------------------------------------------------Camera

	enum ProjectionMode {
		ORTHOGRAPHIC,
		PERSPECTIVE
	};

	struct Camera;

	Camera* CreateCamera(std::string name, ProjectionMode mode);
	Camera* GetCamera(std::string name);
	LF_API void EnableCamera(std::string name);
	LF_API void CameraView(const Vec3 &mag);
	LF_API void CameraView(float zoom);
	LF_API void CameraUpdate();

	// -----------------------------------------------------------------------------Sprites

	typedef uint32_t TileId;

	struct Tile;

	Tile* LoadTile(const char* filename, const Vec2& pos, const Vec2& scale);
	Tile* LoadTile(Texture *texture, const Vec2& pos, const Vec2& scale);
	Tile* GetTile(TileId id);

	// -----------------------------------------------------------------------------Tileset

	struct Tileset;

	Tileset *LoadTileset(std::string name, std::string filename);

	// -----------------------------------------------------------------------------Lucy Framework
	
	struct Lucy;

	LF_API void CreateContext();
	std::shared_ptr<lf::Lucy>& GetContext();
	LF_API void RegisterLayout(Layout layout, const std::vector<VertexArrayLayout> &layouts);
	LF_API template <typename T> void RegisterLayout(const std::vector<VertexArrayLayout> &layouts);

	Shader* RegisterShader(std::string name, std::string vs_filename, std::string fs_filename, bool file = true, bool bind_block = true);
	Shader *GetShader(std::string name);

	LF_API void SetModel(const glm::mat4& model);
	LF_API void SetView(const glm::mat4& view);
	LF_API void SetProjection(const glm::mat4& projection);

	LF_API void Update();
	double& GetTimeStep();

	LF_API void ToggleWireframe(bool wireframe);

	// LF_API void DebugInit()
	// #ifndef LF_DEBUG
	// {}
	// #endif
	// ;
	// LF_API void DebugUpdate()
	// #ifndef LF_DEBUG
	// {}
	// #endif
	// ;
}

#include "Impl.h"
#include "Lucy/Mesh.h"
