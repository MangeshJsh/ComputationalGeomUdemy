#pragma once
#include "Point.h"
#include <vector>

#define INE 0
#define INW 1
#define ISE 2
#define ISW 3

struct AABB
{
	float xmin = 0.0f;
	float ymin = 0.0f;
	float xmax = 0.0f;
	float ymax = 0.0f;

	AABB() = default;

	AABB(float _xmin, float _ymin, float _xmax, float _ymax) :
		xmin(_xmin), ymin(_ymin), xmax(_xmax), ymax(_ymax){}

	/*Used to decide whether to partition a node or not based on the number
	of points inside the node. */
	bool isInside(const Point2d& point)
	{
		if ((xmin <= point[X] && point[X] <= xmax) &&
			(ymin <= point[Y] && point[Y] <= ymax))
		{
			return true;
		}
		return false;
	}
};

/*Each internal tree node of a quad tree represents a square area of the 2D space.
Quad tree node either has 4 children or 0 children. Node is partitioned/devided till
there is only point in a square and that point is contained in the leaf node. */

struct QDTNode
{
	QDTNode* ne = nullptr;
	QDTNode* nw = nullptr;
	QDTNode* se = nullptr;
	QDTNode* sw = nullptr;

	QDTNode* parent = nullptr;
	AABB boundingBox;
	Point2d dataPoint = DEFAULT_POINT_2D;
	bool isLeaf = false;
	QDTNode() = default;
};

class QuadTree
{
public:
	QuadTree() {}

	//QuadTree(const std::vector<Point2d>& points);

	QuadTree(std::vector<Point2d> points, AABB& fullRangeBounds);

	/*void generateMesh();

	void balanceTree();*/

private:

	void partition(QDTNode* parent, std::vector<Point2d>& points);

	QDTNode* northNeighbor(QDTNode* node, QDTNode* root);
	QDTNode* westNeighbor(QDTNode* node, QDTNode* root);
	QDTNode* southNeighbor(QDTNode* node, QDTNode* root);
	QDTNode* eastNeighbor(QDTNode* node, QDTNode* root);

private:

	QDTNode* root = nullptr;
};