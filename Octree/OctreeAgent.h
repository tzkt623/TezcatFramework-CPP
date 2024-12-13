#pragma once

#include "BoundingBox.h"

class OctreeAgentList;
class OctreeNode;
struct OctreeAgent
{
    OctreeAgent* preAgent = nullptr;
    OctreeAgent* nextAgent = nullptr;

    BoundingBox boundingBox;
    OctreeNode* hostNode = nullptr;

    ~OctreeAgent();

    void update();

    void removeSelf();

    void forearchPossible(const std::function<void(OctreeAgent*)>& function);
};

