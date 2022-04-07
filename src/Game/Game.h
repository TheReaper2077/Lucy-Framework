#pragma once

#include "../Lucy/Lucy.h"
#include "../Lucy/Draw.h"
#include "Components.h"

struct Game {
	entt::registry registry;

	lf::Mesh *mesh, *map;

	Vec3 color = Vec3(1, 1, 1);
};

void GameInit();
void GameUpdate();

void RenderTransform(Transform *transform);