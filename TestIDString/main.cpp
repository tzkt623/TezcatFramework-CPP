#include "../TezcatFramework/include/TezcatFramework.h"
#include <iostream>

using namespace tezcat;

struct Uniform1 {};
struct Uniform2 {};

using MyUniform1 = IDString<Uniform1>;
using MyUniform2 = IDString<Uniform2>;


class TezStringContent
{
    std::string mData{};
public:

    std::string getString()
    {
        return std::string(mData.begin(), mData.end());
    }
};

int main()
{
    MyUniform1::UMap map;

    MyUniform1 str1("uniform");
    MyUniform1 str2("vec3");

    TEZ_LOG("{}", str1 == str2);
    TEZ_LOG("[{}]{}", str1.getUID(), str1.getString());
    TEZ_CONSOLE_WRITE_LINE(str2);

    map.try_emplace("uniform", 1);
    map.try_emplace("sampler2D", 2);
    map.try_emplace(str1, 3);
    map.try_emplace(str2, 4);

    TEZ_CONSOLE_WRITE_LINE(map.size());
    TEZ_CONSOLE_WRITE_LINE((map.find("uniform") != map.end()));
    TEZ_CONSOLE_WRITE_LINE(map[str1]);

    {
        str2 = "hahaha";
    }
    TEZ_CONSOLE_WRITE_LINE(str2);

    {
        str1 = std::string("ooooooo");
    }
    TEZ_CONSOLE_WRITE_LINE(str1);

    MyUniform2 str21("vec4");
    MyUniform2 str22("vec3");

    TEZ_PAUSE;

    return 0;
}
