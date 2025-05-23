#pragma once

#include "OctreeConfig.h"

struct OctreeAgent;
class OctreeAgentList
{
public:
    OctreeAgentList() {}
    ~OctreeAgentList()
    {
        mRoot = nullptr;
    }

    void setRoot(OctreeAgent* root);
    void push(OctreeAgent* agent);

    void remove(OctreeAgent* agent);

    void foreach(const std::function<void(OctreeAgent*)>& function);

    void clear()
    {
        mRoot = nullptr;
    }

    uint32_t count()
    {
        return mCount;
    }

private:
    OctreeAgent* mRoot = nullptr;
    uint32_t mCount = 0;
};

