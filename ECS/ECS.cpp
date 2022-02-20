#include "ECS.h"





int main()
{
	auto go = new GameObject();
 	go->addComponent<Com1>("hahaha", 1);
 	go->addComponent<Com2>(go, 19.9999);
 	go->addComponent<Com3>();
 	go->addComponent<Com4>();

	auto com1 = go->getComponent<Com1>();
	auto com2 = go->getComponent<Com2>();
	auto com3 = go->getComponent<Com3>();
	auto com4 = go->getComponent<Com4>();

	std::cout << "Com1: " << com1 << "|" << com1->getComponentType().name() << std::endl;
	std::cout << "Com2: " << com2 << "|" << com2->getComponentType().name() << std::endl;
	std::cout << "Com3: " << com3 << "|" << com3->getComponentType().name() << std::endl;
	std::cout << "Com4: " << com4 << "|" << com4->getComponentType().name() << std::endl;

	system("pause");
}