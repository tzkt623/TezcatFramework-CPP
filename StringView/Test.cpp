#include "../Utility/Utility.h"


int main()
{
    std::unordered_map<std::string_view, std::string> map;
    std::string_view v1;	//struct
    std::string_view v2;	//struct
    std::string_view v3;	//TINY_Lit_Direction
    std::string_view v4;	//vec3

    {
        std::string content = "struct TINY_Lit_Direction\
        {\
            vec3 direction;\
            vec3 ambient;\
            vec3 diffuse;\
            vec3 specular;\
        };";

        v1 = std::string_view(content.c_str(), 6);
        v2 = std::string_view(content.c_str(), 6);
        v3 = std::string_view(content.c_str() + 7, 18);
        v4 = std::string_view(content.c_str() + 28, 4);

        MY_CONSOLE_WRITE_LINE("v1: " << v1);
        MY_CONSOLE_WRITE_LINE("v2: " << v2);
        MY_CONSOLE_WRITE_LINE("v3: " << v3);
        MY_CONSOLE_WRITE_LINE("v4: " << v4);

        MY_CONSOLE_WRITE_LINE("v1==v2: " << (v1 == v2));
        MY_CONSOLE_WRITE_LINE("v1==v3: " << (v1 == v3));
        MY_CONSOLE_WRITE_LINE("v2==v4: " << (v2 == v4));

        map.emplace(v1, "i am v1");
        map.emplace(v2, "i am v2");
        map.emplace(v3, "i am v3");
        map.emplace(v4, "i am v4");
    }

    MY_CONSOLE_WRITE_LINE("Map Count: " << map.size());
    MY_CONSOLE_WRITE_LINE("Check with v1: " << map.at(v1));
    MY_CONSOLE_WRITE_LINE("Check with v2: " << map.at(v2));
    MY_CONSOLE_WRITE_LINE("Check with v3: " << map.at(v3));
    MY_CONSOLE_WRITE_LINE("Check with v4: " << map.at(v4));

    MY_PAUSE;

    return 0;
}
