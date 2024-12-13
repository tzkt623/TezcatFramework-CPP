#include "../Utility/Utility.h"


class MyClass
{
public:
    MyClass() :
        mID(0)
    {}

    union
    {
        uint64_t mID;

        struct Type1
        {
            uint64_t id0_7 : 8;
            uint64_t id8_15 : 8;
            uint64_t id16_31 : 16;
            uint64_t id32_47 : 16;
            uint64_t id48_63 : 16;
        } mCombineID;
    };
};


int main()
{
    MyClass my;
    my.mCombineID.id0_7 = 1;
    my.mCombineID.id48_63 = 0;

    MY_CONSOLE_WRITE_LINE(my.mCombineID.id0_7);
    MY_CONSOLE_WRITE_LINE(my.mCombineID.id8_15);
    MY_CONSOLE_WRITE_LINE(my.mCombineID.id16_31);
    MY_CONSOLE_WRITE_LINE(my.mCombineID.id32_47);
    MY_CONSOLE_WRITE_LINE(my.mCombineID.id48_63);

    MY_CONSOLE_WRITE_LINE(my.mID);

    MY_CONSOLE_ENDL;

    my.mCombineID.id0_7 = 0;
    my.mCombineID.id48_63 = 1;

    MY_CONSOLE_WRITE_LINE(my.mCombineID.id0_7);
    MY_CONSOLE_WRITE_LINE(my.mCombineID.id8_15);
    MY_CONSOLE_WRITE_LINE(my.mCombineID.id16_31);
    MY_CONSOLE_WRITE_LINE(my.mCombineID.id32_47);
    MY_CONSOLE_WRITE_LINE(my.mCombineID.id48_63);

    MY_CONSOLE_ENDL;

    return 0;
}
