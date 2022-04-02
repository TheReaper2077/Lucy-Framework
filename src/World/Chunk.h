#pragma once


#include "../define"
#include "../Render/Renderer.h"

static bool InsideBounds(Rect *rect, Vec2 *point) {
	return (point->x > rect->x && point->x < rect->x + rect->w && point->y > rect->y && point->y < rect->y + rect->h);
}

template <typename T>
struct Node {
	Vec2 point;
	T *data;
}

template <typename T>
struct Tree {
	Tree *parent = nullptr;
	Tree *NE = nullptr;
	Tree *SE = nullptr;
	Tree *NW = nullptr;
	Tree *SW = nullptr;

	std::vector<Node<T>*> node_array;
	int size = 0;
};

template <typename T>
void Insert(Tree *tree, Node<T> *node) {
	if (node == nullptr) return;

	if (size < )
};