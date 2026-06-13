#include "BinarySearchTree.h"
#include <queue>

BST::BST(std::vector<float> _values, const unsigned int _index)
{
	root = new BSTNode(_values[_index]);
	for (size_t i = 0; i < _values.size(); ++i)
	{
		if (i != _index)
		{
			insert(_values[i]);
		}
	}
}

void BST::insert(float _val)
{
	if (!root)
	{
		root = new BSTNode(_val);
	}
	else
	{
		BSTNode* ptr = root;

		while (true)
		{
			if (_val < ptr->value)
			{
				if (ptr->left)
				{
					ptr = ptr->left;
				}
				else
				{
					ptr->left = new BSTNode(_val);
					ptr->left->parent = ptr;
					break;
				}
			}
			else if (_val > ptr->value)
			{
				if (ptr->right)
				{
					ptr = ptr->right;
				}
				else
				{
					ptr->right = new BSTNode(_val);
					ptr->right->parent = ptr;
					break;
				}
			}
		}
	}
}

void BST::preOrderTraversal(BSTNode* node, std::vector<float>& _values)
{
	if (!node) return;
	_values.push_back(node->value);
	preOrderTraversal(node->left, _values);
	preOrderTraversal(node->right, _values);
}

void BST::postOrderTraversal(BSTNode* node, std::vector<float>& _values)
{
	if (!node) return;
	postOrderTraversal(node->left, _values);
	postOrderTraversal(node->right, _values);
	_values.push_back(node->value);
}

void BST::inOrderTraversal(BSTNode* node, std::vector<float>& _values)
{
	if (!node) return;
	inOrderTraversal(node->left, _values);
	_values.push_back(node->value);
	inOrderTraversal(node->right, _values);
}

bool BST::find(float val)
{
	return find(root, val) ? true : false;
}

BST::BSTNode* BST::find(BSTNode* startNode, float val)
{
	BSTNode* temp = startNode;
	while (temp && temp->value != val)
	{
		if (temp->value < val)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return temp;
}

BST::BSTNode* BST::min(BSTNode* startNode)
{
	BSTNode* temp = root;

	if(startNode)
		temp = startNode;

	while (temp->left)
	{
		temp = temp->left;			
	}
	return temp;
}

BST::BSTNode* BST::max(BSTNode* startNode)
{
	BSTNode* temp = root;

	if (startNode)
		temp = startNode;

	while (temp->right)
	{
		temp = temp->right;			
	}
	return temp;
}

/*In an in-order traversal, successor of a node is the minimum of the node's right subtree.
If right subtree does not exist then, search for a parent node with a left child.
*/
BST::BSTNode* BST::successor(BSTNode* startNode)
{
	BSTNode* temp = root;

	if (startNode)
		temp = startNode;

	if (temp->right)
		return BST::min(temp->right);
	else
	{
		while (temp->parent && temp != temp->parent->left)
		{
			temp = temp->parent;
		}
	}
	return temp->parent;
}


/*
* predecessor is the maximum of the left subtree of the node. If the left child is null
* then search for a parent with the right child.
*/

BST::BSTNode* BST::predecessor(BSTNode* startNode)
{
	BSTNode* temp = root;

	if (startNode)
		temp = startNode;

	if (temp->left)
		return BST::max(temp->left);
	else
	{
		while (temp->parent && temp != temp->parent->right)
		{
			temp = temp->parent;
		}
	}
	return temp->parent;
}

bool BST::isALeaf(BSTNode* node)
{
	return node->left == nullptr && node->right == nullptr;
}

void BST::transplant(BSTNode* u, BSTNode* v)
{
	if (!u->parent)
	{
		root = v;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}

	if (v)
	{
		v->parent = u->parent;
	}
}

bool BST::remove(float _val)
{
	BSTNode* nodeToDelete = find(root, _val);
	if (nodeToDelete)
	{
		BSTNode* leftChild = nodeToDelete->left;
		BSTNode* rightChild = nodeToDelete->right;

		if (isALeaf(nodeToDelete))
		{
			transplant(nodeToDelete, nullptr);
		}
		else if (!leftChild)
		{
			transplant(nodeToDelete, rightChild);
		}
		else if (!rightChild)
		{
			transplant(nodeToDelete, leftChild);
		}
		else
		{
			BSTNode* successorOfNodeToDelete = min(rightChild);

			if (successorOfNodeToDelete->parent != nodeToDelete)
			{
				transplant(successorOfNodeToDelete, successorOfNodeToDelete->right);
				successorOfNodeToDelete->right = nodeToDelete->right;
				successorOfNodeToDelete->right->parent = successorOfNodeToDelete;
			}
			

			transplant(nodeToDelete, successorOfNodeToDelete);
			successorOfNodeToDelete->left = nodeToDelete->left;
			successorOfNodeToDelete->left->parent = successorOfNodeToDelete;
		}
		return true;
	}

	return false;
}

/* 1-D Range Query using BST.
* The values are arranged in a BST and range query is performed on the BST.
* Find the split node that exists on both the search paths to lower bound and
* upper bound of the query range.
*	Follow the search path of the LEFT BONDARY value
*		At each node where path goes to the left, report all the leaves in the right subtree
*	Follow the search path of the RIGHT BOUNDARY value
*		At each node where the path goes to the right, report all the leaves in the left subtree
* 
* Check the leaf node values at the end of the search paths. They may or may not lie in the search range.


*/
BST::BSTNode* BST::findSplitNode(float lowerBound, float upperBound)
{
	BSTNode* node = root;

	while (!isALeaf(node) && (node->value < lowerBound || node->value >= upperBound))
	{
		if (node->value < lowerBound)
			node = node->right;
		else if (node->value >= upperBound)
			node = node->left;
	}
	return node;
}

std::vector<float> BST::oneDimensionalRangeSearch(float lowerBound, float upperBound)
{
	std::vector<float> valuesInRange;
	BST::BSTNode* splitNode = findSplitNode(lowerBound, upperBound);

	if (isALeaf(splitNode))
	{
		if (splitNode->value >= lowerBound && splitNode->value < upperBound)
		{
			valuesInRange.push_back(splitNode->value);
		}
	}
	else
	{
		auto node = splitNode->left;
		while (!isALeaf(node))
		{
			if (node->value >= lowerBound)
			{
				inOrderTraversal(node->right, valuesInRange);
				valuesInRange.push_back(node->value);
				node = node->left;
			}
			else
			{
				node = node->right;
			}
		}

		if (node->value >= lowerBound)
			valuesInRange.push_back(node->value);

		node = splitNode->right;

		while (!isALeaf(node))
		{
			if (node->value <= upperBound)
			{
				inOrderTraversal(node->left, valuesInRange);
				node = node->right;
			}
			else
			{
				node = node->left;
			}
		}

		if (node->value <= upperBound)
			valuesInRange.push_back(node->value);
	}

	return valuesInRange;
}