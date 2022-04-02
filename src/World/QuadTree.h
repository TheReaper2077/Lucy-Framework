#pragma once


#include "../define.h"
#include "../Render/Renderer.h"

<<<<<<< HEAD
static bool InsideBounds(lf::Rect *rect, Vec2 *point) {
	return (point->x > rect->x && point->x < rect->x + rect->w && point->y > rect->y && point->y < rect->y + rect->h);
=======
static bool InsideBounds(const Rect &rect, Vec2 *point) {
	return (point->x > rect.x && point->x < rect.x + rect.w && point->y > rect.y && point->y < rect.y + rect.h);
>>>>>>> parent of 1b39039 (refractor)
}

const int max_size = 4;

struct Data {
	Vec2 point;
	uint32_t data;
};

<<<<<<< HEAD
struct QuadTree {
	QuadTree *NE = nullptr;
	QuadTree *NW = nullptr;
	QuadTree *SE = nullptr;
	QuadTree *SW = nullptr;

	std::vector<Node*> data_array;
	lf::Rect rect;
=======
struct Node {
	Node *NE = nullptr;
	Node *NW = nullptr;
	Node *SE = nullptr;
	Node *SW = nullptr;

	std::vector<Data*> data_array;
>>>>>>> parent of 1b39039 (refractor)

	Rect rect;

<<<<<<< HEAD
	QuadTree (lf::Rect rect): rect(rect), leaf_node(true) {}
=======
	bool leaf_node;
>>>>>>> parent of 1b39039 (refractor)

	Node (Rect rect): rect(rect) {}

	void Insert(Data *i_node) {
		if (i_node == nullptr) return;

		if (leaf_node && data_array.size() < max_size) {
			
		} else if (leaf_node) {
			for (auto& data: data_array) {
				Insert(data);
			}
<<<<<<< HEAD
			data_array.clear();
		}
		
		if (node->point.x > rect.x && node->point.x < rect.x + rect.w / 2) {
			if (node->point.y > rect.y && node->point.y < rect.y + rect.h / 2) {
				if (NE == nullptr) {
					NE = new QuadTree(lf::Rect{rect.x, rect.y, rect.w / 2, rect.h / 2});
				}
				NE->Insert(node);
			} else {
				if (SE == nullptr) {
					SE = new QuadTree(lf::Rect{rect.x, rect.y + rect.h / 2, rect.w / 2, rect.h / 2});
				}
				SE->Insert(node);
			}
		} else {
			if (node->point.y > rect.y && node->point.y < rect.y + rect.h / 2) {
				if (NW == nullptr) {
					NW = new QuadTree(lf::Rect{rect.x + rect.w / 2, rect.y, rect.w / 2, rect.h / 2});
				}
				NW->Insert(node);
			} else {
				if (SW == nullptr) {
					SW = new QuadTree(lf::Rect{rect.x + rect.w / 2, rect.y + rect.h / 2, rect.w / 2, rect.h / 2});
				}
				SW->Insert(node);
			}
=======
>>>>>>> parent of 1b39039 (refractor)
		}
	}
};