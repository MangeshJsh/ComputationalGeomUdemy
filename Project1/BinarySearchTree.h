#pragma once
#include <vector>

class BST
{
	struct BSTNode
	{
		BSTNode* left;
		BSTNode* right;
		BSTNode* parent;
		float value;

		BSTNode(float val, BSTNode* _left = nullptr, BSTNode* _right = nullptr, BSTNode* _parent = nullptr) :
			value(val), left(_left), right(_right), parent(_parent) {}
	};

public:
	BST() {}
	BST(std::vector<float> _values, const unsigned int _index = 0);
	void insert(float _val);
	void preOrderTraversal(BSTNode* node, std::vector<float>& values);
	void postOrderTraversal(BSTNode* node, std::vector<float>& values);
	void inOrderTraversal(BSTNode* node, std::vector<float>& values);
	bool find(float val);
	BSTNode* min(BSTNode* startNode = nullptr);
	BSTNode* max(BSTNode* startNode = nullptr);
	BSTNode* successor(BSTNode* startNode = nullptr);
	BSTNode* predecessor(BSTNode* startNode = nullptr);
	bool remove(float _val);
	std::vector<float> oneDimensionalRangeSearch(float lowerBound, float upperBound);

private:
	BSTNode* find(BSTNode* startNode, float _val);
	bool isALeaf(BSTNode* node);
	void transplant(BSTNode* u, BSTNode* v); // u to be replaced by v
	BST::BSTNode* findSplitNode(float lowerBound, float upperBound);

	BSTNode* root = nullptr;
};