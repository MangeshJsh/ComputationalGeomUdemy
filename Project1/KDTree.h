#pragma once

#include <list>
#include "Vector.h"

class KDTree
{
	struct KDRegion2D
	{
		float left, right, bot, top;
	};

	/*Each non leaf node represents a rectangular region in the space.*/
	/*For non leaf nodes store the splitting value and for the leaf nodes store the point value*/
	struct KDNode
	{
		KDNode* left;
		KDNode* right;
		Vector2f point; // data point value
		float value = FLT_MIN; //split value
		KDRegion2D boundary{-10, 10, -10, 10};

		KDNode(Vector2f _data, KDNode* _left = nullptr, KDNode* _right = nullptr):
			left(_left), right(_right), point(_data){}

		KDNode(float _val, KDNode* _left = nullptr, KDNode* _right = nullptr) :
			left(_left), right(_right), value(_val) {}

	};

	KDNode* root = nullptr;

	KDRegion2D defaultBound{ -10, 10, -10, 10 };
	KDRegion2D invalidBound{ 0,0,0,0 };

	KDNode* constructKDTree(std::list<Vector2f>& data, int depth);
	void traverse(KDNode* node, std::list<Vector2f>& list);

public:

	KDTree() {}

	KDTree(std::list<Vector2f>& data, float depth)
	{
		constructKDTree(data, depth);
	}

	searchKDTree(node, searchRange);
};
