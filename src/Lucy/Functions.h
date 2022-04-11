#pragma once

#ifndef LF_API
#include "Lucy.h"
#endif

namespace lf {
	void RenderRect(Mesh* mesh, Texture *tex, const Vec3& pos, const Vec3& scale, const Vec2& uv0, const Vec2& uv1, bool enable_indexing = true);

	void RenderRect(Mesh* mesh, const Vec3& pos, const Vec3& scale, const Vec3& color, bool fill = false, bool enable_indexing = true);

	void RenderLine(Mesh* mesh, const std::vector<Vec3>& vertices, const Vec3& color);

	void RenderLine(Mesh* mesh, const Vec3& v0, const Vec3& v1, const Vec3& color);

	void RenderPoint(Mesh* mesh, const std::vector<Vec3>& vertices, const Vec3& color);

	void RenderPoint(Mesh* mesh, const Vec3& v, const Vec3& color);
}
