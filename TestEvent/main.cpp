#include "../TezcatFramework/include/TezcatFramework.h"


using namespace tezcat;

int ID = 0;

class Data
{
public:
    Data() : str("DataString"), id(ID++)
    {
        TEZ_CONSOLE_WRITE_LINE(id << " : " << "Data Created");
    }

    Data(const Data& other)
        : str(other.str), id(ID++)
    {
        TEZ_CONSOLE_WRITE_LINE(id << " : " << "Data Copy");
    }

    // 	Data(Data&& other) : id(ID++)
    // 	{
    // 		std::cout << id << " : " << "Data Move From [" << other.id << "]" << std::endl;
    // 		str = std::move(other.str);
    // 	}

    ~Data()
    {
        TEZ_CONSOLE_WRITE_LINE(id << " : " << "Data Destroy");
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
        TEZ_CONSOLE_WRITE_LINE(x);
    }

    void funcData(Data data)
    {
        TEZ_CONSOLE_WRITE_LINE(data.id << " : " << data.str);
    }

    void func3(const Data& data, int i, float* array)
    {
        TEZ_CONSOLE_WRITE_LINE(data.id << " : " << array[0] << array[1] << array[2]);
    }
};


class MyClass1
{
    TezSPointer<MyClass2> sA{ new MyClass2() };
    TezSPointer<MyClass2> sB{ new MyClass2() };
    TezSPointer<MyClass2> sC{ new MyClass2() };

public:
    MyClass1()
    {
    }

    ~MyClass1()
    {

    }

    void add()
    {
        onEvent.subscribe(sA.get(), &MyClass2::funcInt);
        onDataEvent.subscribe(sA.get(), &MyClass2::funcData);
        onEvent3.subscribe(sA.get(), &MyClass2::func3);


        onEvent3.subscribe(sB.get(), &MyClass2::func3);
        onEvent3.subscribe(sC.get(), &MyClass2::func3);
    }

    void remove()
    {
        onEvent3.unsubscribe(sB.get(), &MyClass2::func3);
        onEvent3.unsubscribe(sC.get(), &MyClass2::func3);
    }

    void dispatch()
    {
        onEvent.dispatch(20);

        onDataEvent.dispatch(Data{});
        onEvent3.dispatch(Data{}, 2, new float[] { 3, 4, 5 });
    }


public:
    TezEventDelegate<int> onEvent;
    TezEventDelegate<Data> onDataEvent;
    TezEventDelegate<const Data&, int, float*> onEvent3;
};

void t(int x) {}

int main()
{
    MyClass1 my;
    my.add();
    my.remove();

    my.dispatch();

    TEZ_PAUSE;

    return 0;
}
