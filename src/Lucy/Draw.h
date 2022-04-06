#pragma once

#include "Lucy.h"

namespace lf {
	typedef uint32_t BatchId;

	void BatchBegin(BatchId id);
	void BatchEnd();
	void RenderBatch(BatchId id);

	enum DrawType {
		TEXTURE,
		FILL,
		DRAW,
	};

	struct Rect {
		float x, y, w, h;

		Rect (const Vec2& pos, const Vec2& scale) {
			x = pos.x;
			y = pos.y;
			w = x + scale.x;
			h = y + scale.y;
		}

		Rect (const Vec3& pos, const Vec3& scale) {
			x = pos.x;
			y = pos.y;
			w = x + scale.x;
			h = y + scale.y;
		}
	};

	struct Cube {
		float x, y, z, w, h, d;

		Cube (const Vec3& pos, const Vec3& scale) {
			x = pos.x;
			y = pos.y;
			z = pos.z;
			w = x + scale.x;
			h = y + scale.y;
			d = z + scale.z;
		}
	};

	void DrawRect(Mesh *mesh, const Vec3& pos, const Vec3& scale, const Vec3& color, const float& thickness);
	void FillRect(Mesh *mesh, const Vec3& pos, const Vec3& scale, const Vec3& color);
	void TextureRect(Mesh *mesh, Texture *texture, const Vec3& pos, const Vec3& scale, const Vec2& uv0 = Vec2(0, 0), const Vec2& uv1 = Vec2(1, 1));
	
	// void DrawRect(Mesh *mesh, const Vec2& pos, const Vec2& scale, const Vec3& color, const int& thickness);
	// void FillRect(Mesh *mesh, const Vec2& pos, const Vec2& scale, const Vec3& color);
	// void TextureRect(Mesh *mesh, Texture *texture, const Vec2& pos, const Vec2& scale, const Vec2& uv0 = Vec2(0, 0), const Vec2& uv1 = Vec2(1, 1));

	// void DrawRect(Mesh *mesh, const Rect& rect, const Vec3& color, const int& thickness);
	// void FillRect(Mesh *mesh, const Rect& rect, const Vec3& color);
	// void TextureRect(Mesh *mesh, Texture *texture, const Rect& rect, const Vec2& uv0 = Vec2(0, 0), const Vec2& uv1 = Vec2(1, 1));
}