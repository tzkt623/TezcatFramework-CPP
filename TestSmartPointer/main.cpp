#define TEZCAT_DYNAMIC_LIB
//#define TEZCAT_STATIC_LIB 1

#include "../TezcatFramework/include/TezcatFramework.h"


using namespace tezcat;

class Base
{
public:
    Base(std::string name) : name(name) {}
    virtual ~Base() = default;

    std::string name;
};


class T1 : public Base
{
public:
    T1(std::string name, int value) : Base(name), p(value) {}
    virtual ~T1() = default;

    int p = 0;
};

class T2 : public Base
{
public:
    T2(std::string name, float value) : Base(name), p(value) {}
    virtual ~T2() = default;

    float p;
};

int main()
{
    {
        TezUPointer<T1> a(new T1("A", 87));
        TEZ_LOG("name: {}", a->name);
        TezUPointer<T1> b = std::move(a);
        TEZ_LOG("name: {}", b->name);

        TezUPointer<T1> c(new T1("C", 324));
        TezUPointer<T1> d(new T1("D", 5345));

        std::vector<TezUPointer<Base>> baseVector;

        baseVector.push_back(std::move(c));
        baseVector.push_back(std::move(d));

        for (auto& p : baseVector)
        {
            TezUPointer<T1> p2;
            p2.convertFormBaseClass(std::move(p));

            TEZ_CONSOLE_WRITE_LINE(p2->name);
            TEZ_CONSOLE_WRITE_LINE(p2->p);
        }

        //c = d;
        TezUPointer<T1> e(new T1("E", 5345));
        TezUPointer<Base> bA = std::move(e);

        TezUPointer<Base> bB(new T1("bB", 5345));
        //TezUPointer<T1> f = std::move(bB);
        TezUPointer<T1> f;
        f.convertFormBaseClass(std::move(bB));
        TEZ_CONSOLE_WRITE_LINE(f->name);
    }

    {
        TezSPointer<T1> sA = TezSPointer<T1>(new T1("sA", 454));
        TezSPointer<T1> sB = sA;
        TezSPointer<T1> sC(new T1("sC", 35354));
        TezSPointer<int> sE;

        TezSPointer<Base> bA;
        bA.convertFromDerivedClass(sB);

        TezSPointer<T1> sD;
        sD.convertFromBaseClass(bA);

        TezWPointer<T1> wA(sA);
        TezWPointer<T1> wB;
        TezWPointer<T1> wC(wA);
        TezWPointer<T1> wD(std::move(wA));

        if (wA.lock())
        {
            TEZ_CONSOLE_WRITE_LINE(wA->name);
        }

        if (wB.lock())
        {
            TEZ_CONSOLE_WRITE_LINE("wB lock success!!");
        }

        wB = wA;

        if (wB.lock())
        {
            TEZ_CONSOLE_WRITE_LINE("wB lock success!!");
        }

        //bA = sB;
        TEZ_CONSOLE_WRITE_LINE(sD->name);

        if (sC)
        {
            sB = sC;
            TEZ_CONSOLE_WRITE_LINE(sB->p);
            TEZ_CONSOLE_WRITE_LINE(sB->name);
        }
    }

    {
        TezSPointer<T1[]> saA(2, new T1[2]{ {"saA00", 0}, {"saA01", 1}});
        TezSPointer<T1[]> saB = saA;

        TEZ_CONSOLE_WRITE_LINE(saA[1].name);

        TezWPointer<T1[]> wA(saA);
        if (wA.lock())
        {
            TEZ_CONSOLE_WRITE_LINE(wA[0].name);
        }
    }

    TEZ_PAUSE;

    return 0;
}
