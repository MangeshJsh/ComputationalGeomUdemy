#include "QuadTree.h"

QuadTree::QuadTree(std::vector<Point2d> points, AABB& fullRangeBounds)
{
	if (points.empty()) return;

	root = new QDTNode();
	root->boundingBox = fullRangeBounds;
	partition(root, points);
}

void QuadTree::partition(QDTNode* parent, std::vector<Point2d>& points)
{
	if (points.empty())
	{
		parent->isLeaf = true;
		return;
	}
	else if (points.size() == 1)
	{
		parent->dataPoint = points[0];
		parent->isLeaf = true;
		return;
	}
	else
	{
		//Calculate child bounding boxes using parent bounding box

		auto& bbox = parent->boundingBox;

		auto xmid = (bbox.xmin + bbox.xmax) / 2;
		auto ymid = (bbox.ymin + bbox.ymax) / 2;

		AABB ne{xmid,      ymid,       bbox.xmax,   bbox.ymax};
		AABB nw{bbox.xmin, ymid,       xmid,        bbox.ymax };
		AABB sw{bbox.xmin, bbox.ymin,  xmid,        ymid };
		AABB se{xmid,      bbox.ymin,  bbox.xmax,   ymid };


		std::vector<Point2d> pointsNE, pointsNW, pointsSE, pointsSW;

		for (const auto& pt : points)
		{
			if (ne.isInside(pt))
			{
				pointsNE.push_back(pt);
			}
			else if (nw.isInside(pt))
			{
				pointsNW.push_back(pt);
			}
			else if (se.isInside(pt))
			{
				pointsSE.push_back(pt);
			}
			else
			{
				pointsSW.push_back(pt);
			}
		}

		auto nodeNE = new QDTNode();
		auto nodeNW = new QDTNode();
		auto nodeSE = new QDTNode();
		auto nodeSW = new QDTNode();

		nodeNE->boundingBox = ne;
		nodeNW->boundingBox = nw;
		nodeSE->boundingBox = se;
		nodeSW->boundingBox = sw;

		nodeNE->parent = parent;
		nodeNW->parent = parent;
		nodeSE->parent = parent;
		nodeSW->parent = parent;

		parent->ne = nodeNE;
		parent->nw = nodeNW;
		parent->se = nodeSE;
		parent->sw = nodeSW;

		partition(nodeNE, pointsNE);
		partition(nodeNW, pointsNW);
		partition(nodeSE, pointsSE);
		partition(nodeSW, pointsSW);

	}
}

QDTNode* QuadTree::northNeighbor(QDTNode* node, QDTNode* root)
{
	if (node == root) return nullptr;

	if (node == node->parent->sw)
		return node->parent->nw;

	if (node == node->parent->se)
		return node->parent->ne;

	auto u = northNeighbor(node->parent, root);

	if (!u || u->isLeaf)
	{
		return u;
	}
	else if (node == node->parent->nw)
	{
		return u->sw;
	}
	else
		return u->se;
}

QDTNode* QuadTree::southNeighbor(QDTNode* node, QDTNode* root)
{
	if (node == root) return nullptr;

	if (node == node->parent->nw)
		return node->parent->sw;

	if (node == node->parent->ne)
		return node->parent->se;

	auto u = southNeighbor(node->parent, root);

	if (!u || u->isLeaf)
	{
		return u;
	}
	else if (node == node->parent->sw)
	{
		return u->nw;
	}
	else
		return u->ne;
}

QDTNode* QuadTree::westNeighbor(QDTNode* node, QDTNode* root)
{
	if (node == root) return nullptr;

	if (node == node->parent->ne)
		return node->parent->nw;

	if (node == node->parent->se)
		return node->parent->sw;

	auto u = westNeighbor(node->parent, root);

	if (!u || u->isLeaf)
	{
		return u;
	}
	else if (node == node->parent->nw)
	{
		return u->ne;
	}
	else
		return u->se;
}

QDTNode* QuadTree::eastNeighbor(QDTNode* node, QDTNode* root)
{
	if (node == root) return nullptr;

	if (node == node->parent->nw)
		return node->parent->ne;

	if (node == node->parent->sw)
		return node->parent->se;

	auto u = eastNeighbor(node->parent, root);

	if (!u || u->isLeaf)
	{
		return u;
	}
	else if (node == node->parent->ne)
	{
		return u->nw;
	}
	else
		return u->sw;
}