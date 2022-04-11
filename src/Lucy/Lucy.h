#pragma once

#include "../OpenGL/OpenGL.h"
#include "../Math/math.h"

#define LF_API

#define LF_ABSOLUTE_TEXTURES_LIMIT 8

#define LF_ASSERT(x) assert(x)
#define LF_DISABLE_ASSERT(x) assert(x)

#ifndef LF_UPS
#define LF_UPS 60
#endif

#include "GLFW_Compat.h"

namespace lf {
	// -----------------------------------------------------------------------------Events

	struct Events;

	LF_API void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	LF_API bool IsKeyPressed(int key);
	LF_API bool IsKeyReleased(int key);
	LF_API bool IsKeyTyping(int key);
	LF_API bool IsKeyToggled(int key);

	LF_API void MouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	LF_API void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	LF_API bool IsMousePressed(int button);
	LF_API bool IsMouseReleased(int button);
	LF_API bool IsMouseToggled(int button);
	LF_API double GetMousePosX();
	LF_API double GetMousePosY();

	// -----------------------------------------------------------------------------Mesh

	enum MeshType {
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

	LF_API Mesh* CreateMesh(Layout layout, MeshType type, MeshIndices* meshindices = nullptr);
	LF_API template <typename T> MeshT<T>* CreateMesh(MeshType type, MeshIndices* meshindices = nullptr);
	LF_API MeshIndices* CreateMeshIndices();	
		
	LF_API template <typename T> void TransferMesh(T* mesh);	
	LF_API void TransferMeshIndices(MeshIndices* meshindices);

	LF_API template <typename T> void RenderMesh(T* mesh, Shader* shader);
	LF_API template <typename T> void RenderMesh(T* mesh, std::string name);

	LF_API template <typename T> void ClearMesh(T* mesh);
	LF_API void DestroyMesh(Mesh* mesh);

	// -----------------------------------------------------------------------------Camera

	enum ProjectionMode {
		ORTHOGRAPHIC,
		PERSPECTIVE
	};

	struct Camera;

	LF_API Camera* CreateCamera(std::string name, ProjectionMode mode);
	LF_API Camera* GetCamera(std::string name);
	LF_API void EnableCamera(std::string name);
	LF_API void CameraView(const Vec3 &mag);
	LF_API void CameraView(float zoom);
	LF_API void CameraUpdate();

	// -----------------------------------------------------------------------------Sprites

	typedef uint32_t TexTileId;

	struct TexTile;

	LF_API TexTile* LoadTile(const char* filename, const Vec2& pos, const Vec2& scale, bool normalized = false);
	LF_API TexTile* LoadTile(Texture *texture, const Vec2& pos, const Vec2& scale, bool normalized = false);
	LF_API TexTile* GetTile(TexTileId id);

	// -----------------------------------------------------------------------------Tileset

	struct Tileset;

	LF_API Tileset *LoadTileset(std::string name, std::string filename);

	// -----------------------------------------------------------------------------World

	struct World;

	LF_API World *LoadWorldAsQTree(std::string name, std::string filename);
	LF_API World *LoadWorldAsTiled(std::string name, std::string filename);

	// -----------------------------------------------------------------------------Lucy Framework
	
	struct Lucy;

	LF_API void CreateContext();
	LF_API std::shared_ptr<lf::Lucy>& GetContext();
	LF_API void RegisterLayout(Layout layout, const std::vector<VertexArrayLayout> &layouts);
	LF_API template <typename T> void RegisterLayout(const std::vector<VertexArrayLayout> &layouts);

	LF_API Shader* RegisterShader(std::string name, std::string vs_filename, std::string fs_filename, bool file = true, bool bind_block = true);
	LF_API Shader *GetShader(std::string name);

	LF_API void SetModel(const glm::mat4& model);
	LF_API void SetView(const glm::mat4& view);
	LF_API void SetProjection(const glm::mat4& projection);

	LF_API void Update();
	LF_API double& GetTimeStep();

	LF_API void ToggleWireframe(bool wireframe);

	LF_API void DebugInit();
	LF_API void DebugUpdate();
}

#include "Impl.h"
#include "Mesh.h"
#include "Functions.h"