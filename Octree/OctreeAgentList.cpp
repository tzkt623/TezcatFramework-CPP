#include "OctreeAgentList.h"
#include "OctreeAgent.h"



void OctreeAgentList::push(OctreeAgent* agent)
{
	if (mRoot == nullptr)
	{
		mRoot = agent;
	}
	else
	{
		mRoot->preAgent = agent;
		agent->nextAgent = mRoot;
		mRoot = agent;
	}

	++mCount;
}

void OctreeAgentList::remove(OctreeAgent* agent)
{
	--mCount;
}

void OctreeAgentList::foreach(const std::function<void(OctreeAgent*)>& function)
{
	int count = 0;
	OctreeAgent* agent = mRoot;
	while (agent)
	{
		function(agent);
		agent = agent->nextAgent;
		count++;
	}

	if (count != mCount)
	{
		throw new std::logic_error("");
	}
}

void OctreeAgentList::setRoot(OctreeAgent* root)
{
	mRoot = root;
}
