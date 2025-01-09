#include "Range.h"
#include <regex>

void regexTest()
{
    std::string hello("Hello world TINY_END_HEAD hahaha ; test split");

    std::regex ws_re("TINY_END_HEAD|;");
    std::vector<std::string> v(std::sregex_token_iterator(hello.begin(), hello.end(), ws_re, 1), std::sregex_token_iterator());
    for (auto&& s : v)
    {
        std::cout << s << std::endl;
    }
}

struct Sentinel
{
    bool operator== (auto it) const
    {
        return (*it) > 3;
    }
};


void sentinelTest()
{
    std::string hello("Hello world test split");
    for (auto x : std::ranges::subrange(hello.begin(), hello.end()))
    {
        TEZ_CONSOLE_WRITE(x);
    }

    TEZ_CONSOLE_ENDL;

    for (auto x : std::ranges::subrange(std::ranges::find(hello, 'e'), std::ranges::find(hello, 's')))
    {
        TEZ_CONSOLE_WRITE(x);
    }

    TEZ_CONSOLE_ENDL;
}

int main()
{
    sentinelTest();

    TEZ_PAUSE;

    return 0;
}
