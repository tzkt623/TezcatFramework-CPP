#include "../TezcatFramework/include/TezcatFramework.h"

using namespace tezcat;

void testView()
{
    std::unordered_map<std::string_view, std::string> map;
    std::string_view v1;	//struct
    std::string_view v2;	//struct
    std::string_view v3;	//TINY_Lit_Direction
    std::string_view v4;	//vec3

    std::string content =
        "struct TINY_Lit_Direction"
        "{"
        "vec3 direction;"
        "vec3 ambient;"
        "vec3 diffuse;"
        "vec3 specular;"
        "};";


    TEZ_LOG_LINE(content);

    v1 = std::string_view(content.begin(), content.begin() + 6);
    v2 = std::string_view(content.c_str(), 6);
    v3 = std::string_view(content.c_str() + 7, 18);
    v4 = std::string_view(content.begin() + 26, content.begin() + 26 + 4);

    TEZ_LOG("v1: {}", v1);
    TEZ_LOG("v2: {}", v2);
    TEZ_LOG("v3: {}", v3);
    TEZ_LOG("v4: {}", v4);

    TEZ_LOG("v1==v2: {}", (v1 == v2));
    TEZ_LOG("v1==v3: {}", (v1 == v3));
    TEZ_LOG("v2==v4: {}", (v2 == v4));

    map.emplace(v1, "i am v1");
    map.emplace(v2, "i am v2");
    map.emplace(v3, "i am v3");
    map.emplace(v4, "i am v4");

    TEZ_LOG("Map Count: {}", map.size());
    TEZ_LOG("Check with v1: {}", map.at(v1));
    TEZ_LOG("Check with v2: {}", map.at(v2));
    TEZ_LOG("Check with v3: {}", map.at(v3));
    TEZ_LOG("Check with v4: {}", map.at(v4));
}

void testToFromChars()
{
    std::size_t min = std::numeric_limits<std::size_t>::max();
    std::string data;
    data.resize(30);
    auto result = std::to_chars(data.data(), data.data() + data.size(), min);
    if (result.ec == std::errc())
    {
        TEZ_LOG("{}", data);
    }
    else
    {
        TEZ_LOG("{}", std::make_error_code(result.ec).message());
    }

    int s{};
    auto [r, e] = std::from_chars(data.data(), data.data() + data.size(), s);
    if (e == std::errc())
    {
        TEZ_LOG("{}", s);
    }
    else
    {
        TEZ_LOG("{}", std::make_error_code(e).message());
    }
}

int main()
{
    testView();
    testToFromChars();

    TEZ_PAUSE;

    return 0;
}
