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