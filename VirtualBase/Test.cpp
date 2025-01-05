#include "Test.h"
#include "../TezcatFramework/TezConfig.h"

class IA
{
public:
    IA()
    {
        TEZ_CONSOLE_WRITE_LINE("Create IA");
    }
    virtual ~IA()
    {
        TEZ_CONSOLE_WRITE_LINE("Destroy IA");
    }

    virtual void sumbit(int value) = 0;
};

class IB : public virtual IA
{
public:
    IB()
    {
        TEZ_CONSOLE_WRITE_LINE("Create IB");
    }
    virtual ~IB()
    {
        TEZ_CONSOLE_WRITE_LINE("Destroy IB");
    }

    void sumbit(int value) override
    {
        TEZ_CONSOLE_WRITE_LINE("IB sumbit: " << std::to_string(value));
    }

    TEZ_PROPERTY(int, OP)
};

template<typename T>
class Component : public virtual IA
{
public:
    Component()
    {
        TEZ_CONSOLE_WRITE_LINE("Create Component");
    }

    ~Component()
    {
        TEZ_CONSOLE_WRITE_LINE("Destroy Component");
    }

    void sumbit(int value) override
    {
        TEZ_CONSOLE_WRITE_LINE("Component sumbit: " << std::to_string(value));
    }
};

class C : public Component<C>, public IB
{
public:
    C()
    {
        TEZ_CONSOLE_WRITE_LINE("Create C");
    }
    ~C()
    {
        TEZ_CONSOLE_WRITE_LINE("Destroy C");
    }

    void sumbit(int value) override
    {
        TEZ_CONSOLE_WRITE_LINE("C sumbit: " << std::to_string(value));
    }
private:

};


int main()
{
    {
        C c;
        c.sumbit(10);
    }

    TEZ_PAUSE;
    return 0;
}
