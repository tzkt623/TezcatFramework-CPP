#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include <unordered_map>

class Test1
{
public:
	Test1() {}
	virtual ~Test1() {};

	virtual void test() = 0;

	int x = 5;
};

class ITest
{
public:
	ITest() {}
	virtual ~ITest() {}

	virtual void show() = 0;

};


class Test2 : public Test1, public ITest
{
public:
	Test2() {}
	virtual ~Test2() {}

	void show() override
	{
		std::cout << x << std::endl;
	}

	void test() override
	{

	}

private:

};
