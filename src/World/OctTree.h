#pragma once

// x, y, z
#define Q1 6
#define Q2 2
#define Q3 0
#define Q4 4
#define Q5 7
#define Q6 3
#define Q7 1
#define Q8 5

#include "../Math/Vec3.inl"
#include <vector> 
#include <memory>

bool InBounds(const Vec3 &point, const Vec3 &scale, const Vec3 &v) {
	return (
		v.x > point.x && v.y > point.y && v.z > point.z &&
		v.x <= point.x + scale.x && v.y <= point.y + scale.y && v.z <= point.z + scale.z
	);
};

struct OctTree {
	int32_t parent = 0;
	int32_t child[8] = {0};
	int32_t id;
	Vec3 point, scale;

	bool filled = false;

	OctTree(Vec3 point, Vec3 scale) {
		this->point = point;
		this->scale = scale;

		parent = 0;
	}
};

void Create(std::vector<OctTree> *tree, Vec3 point, Vec3 scale) {
	assert(tree != nullptr);
	assert(tree->size() == 0);

	tree->push_back(OctTree{point, scale});
};

void Insert(std::vector<OctTree> *tree, const Vec3& point, const uint32_t &id, int32_t parent = 0) {
	assert(tree->size() != 0);

	auto& parent_tree = tree->at(parent);

	if (!InBounds(parent_tree.point, parent_tree.scale, point)) return;
	
	// if (!parent_tree.filled || parent_tree.scale <= 1) {
	// 	parent_tree.id = id;
	// 	parent_tree.filled = true;
	// 	return;
	// } else if (!parent_tree.filled) {
		
	// }

	auto next_size = parent_tree.scale / 2;

	if (InBounds(parent_tree.point, next_size, point)) {	// 2
		if (parent_tree.child[Q2] == 0) {
			auto temp = OctTree{parent_tree.point, next_size};
			temp.id = id;
			temp.filled = true;
			temp.parent = parent;

			parent_tree.child[Q2] = tree->size();
			tree->push_back(temp);

			return;
		}
		
		Insert(tree, point, id, parent_tree.child[Q2]);
	}

	if (InBounds(parent_tree.point + Vec3(0, 0, next_size.z), next_size, point)) {	// 1
		if (parent_tree.child[Q1] == 0) {
			auto temp = OctTree{parent_tree.point + Vec3(0, 0, next_size.z), next_size};
			temp.id = id;
			temp.filled = true;
			temp.parent = parent;

			parent_tree.child[Q1] = tree->size();
			tree->push_back(temp);

			return;
		}
		
		Insert(tree, point, id, parent_tree.child[Q1]);
	}

	if (InBounds(parent_tree.point + Vec3(0, next_size.y, 0), next_size, point)) {	// 6
		if (parent_tree.child[Q6] == 0) {
			auto temp = OctTree{parent_tree.point + Vec3(0, next_size.y, 0), next_size};
			temp.id = id;
			temp.filled = true;
			temp.parent = parent;

			parent_tree.child[Q6] = tree->size();
			tree->push_back(temp);

			return;
		}
		
		Insert(tree, point, id, parent_tree.child[Q6]);
	}

	if (InBounds(parent_tree.point + Vec3(0, next_size.y, next_size.z), next_size, point)) {	// 5
		if (parent_tree.child[Q5] == 0) {
			auto temp = OctTree{parent_tree.point + Vec3(0, next_size.y, next_size.z), next_size};
			temp.id = id;
			temp.filled = true;
			temp.parent = parent;

			parent_tree.child[Q5] = tree->size();
			tree->push_back(temp);

			return;
		}
		
		Insert(tree, point, id, parent_tree.child[Q5]);
	}

	if (InBounds(parent_tree.point + Vec3(next_size.x, 0, 0), next_size, point)) {	// 3
		if (parent_tree.child[Q3] == 0) {
			auto temp = OctTree{parent_tree.point + Vec3(next_size.x, 0, 0), next_size};
			temp.id = id;
			temp.filled = true;
			temp.parent = parent;

			parent_tree.child[Q3] = tree->size();
			tree->push_back(temp);

			return;
		}
		
		Insert(tree, point, id, parent_tree.child[Q3]);
	}

	if (InBounds(parent_tree.point + Vec3(next_size.x, 0, next_size.z), next_size, point)) {	// 4
		if (parent_tree.child[Q4] == 0) {
			auto temp = OctTree{parent_tree.point + Vec3(next_size.x, 0, next_size.z), next_size};
			temp.id = id;
			temp.filled = true;
			temp.parent = parent;

			parent_tree.child[Q4] = tree->size();
			tree->push_back(temp);

			return;
		}
		
		Insert(tree, point, id, parent_tree.child[Q4]);
	}

	if (InBounds(parent_tree.point + Vec3(next_size.x, next_size.y, 0), next_size, point)) {	// 7
		if (parent_tree.child[Q7] == 0) {
			auto temp = OctTree{parent_tree.point + Vec3(next_size.x, next_size.y, 0), next_size};
			temp.id = id;
			temp.filled = true;
			temp.parent = parent;

			parent_tree.child[Q7] = tree->size();
			tree->push_back(temp);

			return;
		}
		
		Insert(tree, point, id, parent_tree.child[Q7]);
	}

	if (InBounds(parent_tree.point + next_size, next_size, point)) {	// 8
		if (parent_tree.child[Q8] == 0) {
			auto temp = OctTree{parent_tree.point + next_size, next_size};
			temp.id = id;
			temp.filled = true;
			temp.parent = parent;

			parent_tree.child[Q8] = tree->size();
			tree->push_back(temp);

			return;
		}
		
		Insert(tree, point, id, parent_tree.child[Q8]);
	}
};

void Surround() {

};
