#include "Event.h"
#include <iostream>
#include <string>

int ID = 0;

class Data
{
public:
	Data() : str("DataString"), id(ID++)
	{
		std::cout << id << " : " << "Data Created" << std::endl;
	}

	Data(Data& other)
	{
		std::cout << id << " : " << "Data Copy" << std::endl;
	}

	// 	Data(Data&& other) : id(ID++)
	// 	{
	// 		std::cout << id << " : " << "Data Move From [" << other.id << "]" << std::endl;
	// 		str = std::move(other.str);
	// 	}

	~Data()
	{
		std::cout << id << " : " << "Data Destroy" << std::endl;
	}

	int id;
	std::string str;
};

class MyClass2
{
public:
	MyClass2() {}
	~MyClass2() {}

	void funcInt(int x)
	{
		std::cout << x << std::endl;
	}

	void funcData(Data data)
	{
		std::cout << data.id << " : " << data.str << std::endl;
	}

	void func3(const Data& data, int i, float* array)
	{
		std::cout << data.id << " : " << array[0] << array[1] << array[2] << std::endl;
	}
};


class MyClass1
{
public:
	MyClass1() {}
	~MyClass1() {}

	void dispatch()
	{
		Data e;
		//		onDataEvent.dispatch(e);

		onEvent3.dispatch(e, 2, new float[] { 3, 4, 5 });
	}


public:
	Event<int> onEvent;
	Event<Data> onDataEvent;
	Event<const Data&, int, float*> onEvent3;
};


int main()
{
	MyClass2 p;

	MyClass1 my;
	my.onEvent3.addListener(&p,
		std::bind(&MyClass2::func3, &p, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	my.dispatch();

	system("pause");

	return 0;
}