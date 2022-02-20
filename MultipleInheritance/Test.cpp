#include "Test.h"
#include <memory>
#include <vector>
#include <iostream>

#define Log(x) std::cout << x << std::endl;

class A
{
public:
	A()
	{
		Log("A Build");
	}
	virtual ~A()
	{
		Log("A Delete");
	}

private:

};

class B
{
public:
	B()
	{
		Log("B Build");
	}
	virtual ~B()
	{
		Log("B Delete");
	}

private:

};

class AB : public A, public B
{
public:
	AB()
	{
		Log("AB Build");
	}
	~AB()
	{
		Log("AB Delete");
	}

private:

};


int main()
{

	std::vector<std::shared_ptr<A>> a_array;
	std::vector<std::shared_ptr<B>> b_array;
	std::vector<std::shared_ptr<AB>> ab_array;

	ab_array.emplace_back(new AB());
	ab_array.emplace_back(new AB());
	a_array.emplace_back(ab_array[0]);
	b_array.emplace_back(ab_array[0]);

	system("pause");
	ab_array.clear();

	system("pause");
	b_array.clear();

	system("pause");
	a_array.clear();

	system("pause");
	return 0;
}