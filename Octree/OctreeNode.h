#pragma once

#include "BoundingBox.h"
#include "OctreeAgentList.h"
#include "OctreeConfig.h"

struct OctreeAgent;
class OctreeNode
{
	friend struct OctreeAgent;
public:
	OctreeNode();
	OctreeNode(OctreeNode* parent, const OctPoint& point);

	void addAgent(OctreeAgent* agent);

	OctPoint getPoint()
	{
		return mOctPoint;
	}

	int getLayer()
	{
		return mLayerIndex;
	}

	void update()
	{

	}

	void log();

	void logBoundingBox();

	OctreeAgentList& getObjects() { return mObjects; }

protected:
	OctPoint mOctPoint;
	int mLayerIndex;
	OctreeNode* mParent;
	BoundingBox mBoundingBox;
	OctreeNode* mChildren[8];
	OctreeAgentList mObjects;
};

