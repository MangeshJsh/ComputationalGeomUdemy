#include "KDTree.h"

KDTree::KDNode* KDTree::constructKDTree(std::list<Vector2f>& data, int depth)
{
	size_t size = data.size();
	if (size == 1)
		return new KDNode(data.front());

	if (depth % 2 == 0)
		data.sort([](Vector2f a, Vector2f b) {return a[X] < b[X]; });
	else
		data.sort([](Vector2f a, Vector2f b) {return a[Y] < b[Y]; });

	size_t mid = size / 2;
	auto mid_ptr = data.begin();
	std::advance(mid_ptr, mid);
	auto leftList = std::list<Vector2f>(data.begin(), mid_ptr);
	auto rightList = std::list<Vector2f>(mid_ptr, data.end());

	auto leftChild = constructKDTree(leftList, depth + 1);
	auto rightChild = constructKDTree(rightList, depth + 1);

	return new KDNode((*mid_ptr)[depth%2], leftChild, rightChild);

}

void KDTree::traverse(KDNode* node, std::list<Vector2f>& list)
{
	if (!node) return;
	traverse(node->left, list);
	if (isALeaf(node))
	{
		list.push_back(node->point);
	}
	traverse(node->right, list);
}

void KDTree::preprocessBoundaries(KDNode* node, bool isEvenDepth)
{
	if (!node || isALeaf(node)) return;

	if (isEvenDepth)
	{
		if (node->left)
		{
			node->left->boundary = node->boundary;
			node->left->boundary.right = node->value;
			preprocessBoundaries(node->left, !isEvenDepth);
		}

		if (node->right)
		{
			node->right->boundary = node->boundary;
			node->right->boundary.left = node->value;
			preprocessBoundaries(node->right, !isEvenDepth);
		}
	}
	else
	{
		if (node->left)
		{
			node->left->boundary = node->boundary;
			node->left->boundary.top = node->value;
			preprocessBoundaries(node->left, !isEvenDepth);
		}

		if (node->right)
		{
			node->right->boundary = node->boundary;
			node->right->boundary.bot = node->value;
			preprocessBoundaries(node->right, !isEvenDepth);
		}
	}
}

bool KDTree::isInside(const KDRegion2D& r1, const KDRegion2D& r2)
{
	if (r1.left >= r2.left &&
		r1.right <= r2.right &&
		r1.top <= r2.top &&
		r1.bot >= r2.bot)
	{
		return true;
	}
	return false;
}

bool KDTree::isIntersect(const KDRegion2D& r1, const KDRegion2D& r2)
{
	if (r1.right < r2.left || r1.left > r2.right)
		return false;
	if (r1.top < r2.bot || r1.bot > r2.top)
		return false;

	return true;
}

void KDTree::searchKDTree(KDNode* node, const KDRegion2D& searchRange, std::list<Vector2f>& list)
{
	if (isALeaf(node))
	{
		if (isInRange(node->point, searchRange))
		{
			list.push_back(node->point);
		}
	}
	else
	{
		if (node->left)
		{
			if (isInside(node->left->boundary, searchRange))
				traverse(node->left, list);
			else if (isIntersect(node->left->boundary, searchRange))
				searchKDTree(node->left, searchRange, list);
		}

		if (node->right)
		{
			if (isInside(node->right->boundary, searchRange))
				traverse(node->right, list);
			else if (isIntersect(node->right->boundary, searchRange))
				searchKDTree(node->right, searchRange, list);
		}
	}
}