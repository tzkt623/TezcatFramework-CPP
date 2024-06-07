

#include "Octree.h"
#include <random>
#include <iostream>


int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-2048.0f, 2048.0f);
	std::uniform_real_distribution<> length(1.0f, 512.0f);

	Octree tree;
	tree.setBoundingBox(OctVector3(-2048, -2048, -2048), OctVector3(2048, 2048, 2048));

	std::vector<OctreeAgent*> agents;

	for (int i = 0; i < 1024; i++)
	{
		OctreeAgent* agent = new OctreeAgent();
		agents.push_back(agent);

		auto offset = OctVector3(dis(gen), dis(gen), dis(gen));

		// 		auto width = length(gen) / 2.0f;
		// 		auto height = length(gen) / 2.0f;
		// 		auto depth = length(gen) / 2.0f;

		auto width = 32;
		auto height = 32;
		auto depth = 32;

		agent->boundingBox.reset(OctVector3(-width, -height, -depth) + offset
			, OctVector3(width, height, depth) + offset);

		tree.collectBoundingBox(agent->boundingBox);
	}

	tree.logBoundingBox();

	for (auto a : agents)
	{
		tree.addAgent(a);

		//std::cout << OctreeConfig::getName(a->hostNode->getPoint()) << "|" << a->hostNode->getLayer() << std::endl;
	}

	std::cout << tree.getObjects().count() << std::endl;

	tree.getObjects().foreach([](OctreeAgent* agent)
		{
			auto pos = agent->boundingBox.getPosition();
			std::cout << pos.x << "," << pos.y << "," << pos.z << std::endl;
		});

	tree.log();

	std::uniform_int<> index(0, agents.size() - 1);
	auto obj = agents[index(gen)];
	int count = 0;
	obj->forearchPossible([&](OctreeAgent* agent)
		{
			count++;
			if (obj->boundingBox.impact(agent->boundingBox))
			{
				std::cout << "impact" << std::endl;
			}
		});

	std::cout << count << std::endl;

	OctreeAgent* agent64 = new OctreeAgent();
	agent64->boundingBox.reset(OctVector3(-32, -32, -32), OctVector3(32, 32, 32));
	tree.addAgent(agent64);
	std::uniform_real_distribution<> pp(-2048.0f + 33, 2048.0f - 32);

	while (true)
	{
		count = 0;
		std::system("pause");
		auto offset = OctVector3(pp(gen), pp(gen), pp(gen));
		agent64->boundingBox.setPosition(offset);
		agent64->update();

		agent64->forearchPossible([&](OctreeAgent* agent)
			{
				if (agent64 == agent)
				{
					return;
				}
				count++;
				if (agent64->boundingBox.impact(agent->boundingBox))
				{
					std::cout << "impact" << std::endl;
				}
			});
		std::cout << count << std::endl;
	}

	return 0;
}