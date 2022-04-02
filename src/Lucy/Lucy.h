#pragma once

#include "../OpenGL/OpenGL.h"
#include "../Math/math.h"

namespace lf {
	struct KeyEvents;
	struct MouseEvents;

	struct Camera;

	struct Tile;
	struct TileMap;

	struct MeshTemplate;

	struct Lucy;

	// Components
	struct TilemapRenderer;
	struct SpriteRenderer;
	struct Transform;

	// Func
	namespace mesh {
		enum MeshType {
			POINTS,
			LINES,
			LINE_STRIP,
			TRIANGLES,
			TRIANGLE_STRIP,
			TRIANGLE_INDEXED,
		};

		struct MeshIndices {
			std::vector<uint32_t> indices;
			IndexBuffer* indexbuffer = nullptr;
			uint32_t indexcount = 0;
		};

		struct Mesh {
			std::vector<Vec3> mesh;

			VertexBuffer* vertexbuffer;
			MeshIndices* indices;
		};

		void Create();
		// void 
	}
}