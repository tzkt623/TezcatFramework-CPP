#include "main.h"

template<typename T>
struct function_return_value_category
{
    static constexpr auto value = "prvalue";
};

template<typename T>
struct function_return_value_category<T&>
{
    static constexpr auto value = "lvalue";
};

template<typename T>
struct function_return_value_category<T&&>
{
    static constexpr auto value = "xvalue";
};


std::string f1()
{
    return std::string("f1");
}

std::string& f2()
{
    auto s = std::string("f2");
    return s;
}

std::string&& f3()
{
    return std::move(std::string("f3"));
}

int main()
{
    int b = 5;
    int& c = b;
    int&& d = 5;

    MY_CONSOLE_WRITE_LINE(function_return_value_category<decltype((b))>::value);
    MY_CONSOLE_WRITE_LINE(function_return_value_category<decltype(f1())>::value);
    MY_CONSOLE_WRITE_LINE(function_return_value_category<decltype(f2())>::value);
    MY_CONSOLE_WRITE_LINE(function_return_value_category<decltype(f3())>::value);


    MY_PAUSE;
    return 0;
}
