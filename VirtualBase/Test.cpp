#include "Test.h"

class IA
{
public:
	IA()
	{
		std::cout << "Create IA" << std::endl;
	}
	virtual ~IA()
	{
		std::cout << "Destroy IA" << std::endl;
	}

	virtual void sumbit(int value) = 0;
};

class IB : public virtual IA
{
public:
	IB()
	{
		std::cout << "Create IB" << std::endl;
	}
	virtual ~IB()
	{
		std::cout << "Destroy IB" << std::endl;
	}

	void sumbit(int value) override
	{
		std::cout << "IB sumbit: " << std::to_string(value) << std::endl;
	}
};

template<typename T>
class Component : public virtual IA
{
public:
	Component()
	{
		std::cout << "Create Component" << std::endl;
	}

	~Component()
	{
		std::cout << "Destroy Component" << std::endl;
	}

	void sumbit(int value) override
	{
		std::cout << "Component sumbit: " << std::to_string(value) << std::endl;
	}
};

class C : public Component<C>, public IB
{
public:
	C()
	{ 
		std::cout << "Create C" << std::endl;
	}
	~C()
	{
		std::cout << "Destroy C" << std::endl;
	}

	void sumbit(int value) override
	{
		std::cout << "C sumbit: " << std::to_string(value) << std::endl;
	}
private:

};


int main()
{
	{
		C c;
		c.sumbit(10);
	}

	system("pause");
	return 0;
}