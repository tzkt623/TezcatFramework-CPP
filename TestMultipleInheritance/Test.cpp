#include "Test.h"

class A
{
public:
    A()
    {
        TEZ_CONSOLE_WRITE_LINE("A Build");
    }
    virtual ~A()
    {
        TEZ_CONSOLE_WRITE_LINE("A Delete");
    }

private:

};

class B
{
public:
    B()
    {
        TEZ_CONSOLE_WRITE_LINE("B Build");
    }
    virtual ~B()
    {
        TEZ_CONSOLE_WRITE_LINE("B Delete");
    }

private:

};

class AB : public A, public B
{
public:
    AB()
    {
        TEZ_CONSOLE_WRITE_LINE("AB Build");
    }
    ~AB()
    {
        TEZ_CONSOLE_WRITE_LINE("AB Delete");
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

    TEZ_PAUSE;
    ab_array.clear();

    TEZ_PAUSE;
    b_array.clear();

    TEZ_PAUSE;
    a_array.clear();

    TEZ_PAUSE;
    return 0;
}
