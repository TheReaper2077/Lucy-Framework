#pragma once

#include "../OpenGL/OpenGL.h"
#include "../define.h"
#include "../Math/Vec4.inl"
#include "../Math/Vec3.inl"
#include "../Math/Vec2.inl"

typedef std::vector<VertexArrayLayout> LAYOUT;

#define POS_LAYOUT {0, 2, GL_FLOAT}
#define POS3_LAYOUT {0, 3, GL_FLOAT}

#define ATTRS_LAYOUT {1, 3, GL_FLOAT}

#define NORMAL_LAYOUT {2, 3, GL_FLOAT}


struct VertexTemplate {
	static LAYOUT GetLayout();
};

<<<<<<< HEAD:src/Lucy/Layouts.h
struct Vertex2D: VertexTemplate {
	Vec2 pos;
	Vec3 attrs;

	Vertex2D(Vec2 pos, Vec3 attrs = Vec3()) {
		this->pos = pos;
		this->attrs = attrs;
	}

	static LAYOUT GetLayout() {
		return LAYOUT{
			POS_LAYOUT,
			ATTRS_LAYOUT,
		};
	}
};

struct Vertex3D: VertexTemplate {
	Vec3 pos;
	Vec3 attrs;

	Vertex3D(Vec3 pos, Vec3 attrs = Vec3()) {
		this->pos = pos;
		this->attrs = attrs;
	}

	static LAYOUT GetLayout() {
		return LAYOUT{
			POS3_LAYOUT,
			ATTRS_LAYOUT,
		};
	}
};
=======

namespace layout {
	struct Vertex2D: VertexTemplate {
		Vec2 pos;
		Vec3 attrs;

		Vertex2D(Vec2 pos, Vec3 attrs = Vec3()) {
			this->pos = pos;
			this->attrs = attrs;
		}

		static LAYOUT GetLayout() {
			return LAYOUT{
				POS_LAYOUT,
				ATTRS_LAYOUT,
			};
		}
	};
}
>>>>>>> parent of 1b39039 (refractor):src/Render/Layouts.h
