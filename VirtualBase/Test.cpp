#include "Test.h"

class IA
{
public:
    IA()
    {
        MY_CONSOLE_WRITE_LINE("Create IA");
    }
    virtual ~IA()
    {
        MY_CONSOLE_WRITE_LINE("Destroy IA");
    }

    virtual void sumbit(int value) = 0;
};

class IB : public virtual IA
{
public:
    IB()
    {
        MY_CONSOLE_WRITE_LINE("Create IB");
    }
    virtual ~IB()
    {
        MY_CONSOLE_WRITE_LINE("Destroy IB");
    }

    void sumbit(int value) override
    {
        MY_CONSOLE_WRITE_LINE("IB sumbit: " << std::to_string(value));
    }
};

template<typename T>
class Component : public virtual IA
{
public:
    Component()
    {
        MY_CONSOLE_WRITE_LINE("Create Component");
    }

    ~Component()
    {
        MY_CONSOLE_WRITE_LINE("Destroy Component");
    }

    void sumbit(int value) override
    {
        MY_CONSOLE_WRITE_LINE("Component sumbit: " << std::to_string(value));
    }
};

class C : public Component<C>, public IB
{
public:
    C()
    {
        MY_CONSOLE_WRITE_LINE("Create C");
    }
    ~C()
    {
        MY_CONSOLE_WRITE_LINE("Destroy C");
    }

    void sumbit(int value) override
    {
        MY_CONSOLE_WRITE_LINE("C sumbit: " << std::to_string(value));
    }
private:

};


int main()
{
    {
        C c;
        c.sumbit(10);
    }

    MY_PAUSE;
    return 0;
}
