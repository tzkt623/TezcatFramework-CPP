#include <iostream>
#include <string_view>
#include <string>

template<auto Lambda>
struct StringHolder
{
    static constexpr std::string_view myString{ Lambda() };
};

using P1 = StringHolder < []() { return "P1"; } > ;
using P2 = StringHolder < []() { return "P2"; } > ;
using P3 = StringHolder < []() { return "P3"; } > ;

int main()
{

    std::cout << P1::myString << "\n";
    std::cout << P2::myString << "\n";
    std::cout << P3::myString << "\n";
    return 0;
}
