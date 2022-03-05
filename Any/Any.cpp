#include "Any.h"
#include <iostream>
#include <string>
#include <functional>
#include <vector>

using F = void(*)(const std::string&, int);
using Func = std::function<void(const std::string&, int)>;

void test(const std::string& data, int i)
{
	std::string str("���Ǹ�ȫ�ֺ���: ");
	std::cout << str << data << i << std::endl;
}

class PP
{
public:
	PP() : p(100) {}
	PP(const PP& other) : name("��������")
	{
		std::cout << name << std::endl;
	}

	PP(PP&& other) : name("�ƶ�����")
	{
		std::cout << name << std::endl;
	}

	~PP()
	{
		std::cout << name << "-ɾ��" << std::endl;
	}

	void test(const std::string& data, int i)
	{
		std::string str("���Ǹ������еĺ���: [");
		std::cout << str << typeid(PP).name() << "]" << data << i << std::endl;
	}

	int p;
	std::string name;
};

struct BB
{
	BB()
	{
		std::cout << "���캯��" << std::endl;
	}

	BB(const BB& other)
	{
		std::cout << "��������" << std::endl;
	}

	~BB()
	{
		std::cout << "��������" << std::endl;
	}
};

BB getBB()
{
	return BB();
}

void display1()
{
	int i = 10;
	float f = 3.3333f;

	Any a = std::string("����������");
	std::cout << a.cast<std::string>() << std::endl;

	PP c;
	a = std::move(c);
	std::cout << a.cast<PP>().p << std::endl;

	a = 10;
	std::cout << a.cast<int>() << std::endl;

	a = &test;
	a.cast<F>()("�Բ�!!", 30);

	PP p;
	a = Func(std::bind(&PP::test, &p, std::placeholders::_1, std::placeholders::_2));
	a.cast<Func>()("���˸����!!", 40);
}

void display2()
{
	std::vector<Any> arrays;
	arrays.resize(5);

	arrays[0] = std::string("hoho");
	arrays[1] = 10;
	arrays[2] = 20.0f;
	arrays[3] = 30.0;
	arrays[4] = PP();

	for (auto& a : arrays)
	{

	}
}

int main()
{
	//	display1();
	//	display2();

	BB b = getBB();

	int i = 0;
	i++;

	system("pause");
	return 0;
}