#include "Event.h"

int ID = 0;

class Data
{
public:
    Data() : str("DataString"), id(ID++)
    {
        MY_CONSOLE_WRITE_LINE(id << " : " << "Data Created");
    }

    Data(Data& other)
    {
        MY_CONSOLE_WRITE_LINE(id << " : " << "Data Copy");
    }

    // 	Data(Data&& other) : id(ID++)
    // 	{
    // 		std::cout << id << " : " << "Data Move From [" << other.id << "]" << std::endl;
    // 		str = std::move(other.str);
    // 	}

    ~Data()
    {
        MY_CONSOLE_WRITE_LINE(id << " : " << "Data Destroy");
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
        MY_CONSOLE_WRITE_LINE(x);
    }

    void funcData(Data data)
    {
        MY_CONSOLE_WRITE_LINE(data.id << " : " << data.str);
    }

    void func3(const Data& data, int i, float* array)
    {
        MY_CONSOLE_WRITE_LINE(data.id << " : " << array[0] << array[1] << array[2]);
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
    my.onEvent3.addListener(&p, std::bind(&MyClass2::func3, &p
        , std::placeholders::_1
        , std::placeholders::_2
        , std::placeholders::_3));
    my.dispatch();


    MY_PAUSE;

    return 0;
}
