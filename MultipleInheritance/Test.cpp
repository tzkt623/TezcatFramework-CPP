#include "Test.h"

class A
{
public:
    A()
    {
        MY_CONSOLE_WRITE_LINE("A Build");
    }
    virtual ~A()
    {
        MY_CONSOLE_WRITE_LINE("A Delete");
    }

private:

};

class B
{
public:
    B()
    {
        MY_CONSOLE_WRITE_LINE("B Build");
    }
    virtual ~B()
    {
        MY_CONSOLE_WRITE_LINE("B Delete");
    }

private:

};

class AB : public A, public B
{
public:
    AB()
    {
        MY_CONSOLE_WRITE_LINE("AB Build");
    }
    ~AB()
    {
        MY_CONSOLE_WRITE_LINE("AB Delete");
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

    MY_PAUSE;
    ab_array.clear();

    MY_PAUSE;
    b_array.clear();

    MY_PAUSE;
    a_array.clear();

    MY_PAUSE;
    return 0;
}
