#pragma once

#include <format>
#include <iostream>
#include <source_location>

namespace tezcat
{
    class Debug
    {
    public:

        template<typename ...Args>
        struct FormatWrapper
        {
            std::format_string<Args...> fmt;
            std::source_location location;

            FormatWrapper(std::format_string<Args...> fmt, std::source_location loc = std::source_location::current())
            {
                location = loc;
                fmt = fmt;
            }
        };

    public:

        void test()
        {
            //FormatWrapper f("asdasd");
        }

        template<typename ...Args>
        static void log(FormatWrapper<Args...> wrapper, Args&&... args)
        {
            std::source_location& loc = wrapper.location;
            std::cout
                << "File: " << loc.file_name() << "(" << loc.line() << "," << loc.column() << ")\n"
                << "Function: " << loc.function_name() << "\n"
                << std::vformat(wrapper.fmt.get(), std::make_format_args(args...))
                << "\n";
        }

        template<typename ...Args>
        static void log(const std::source_location& loc, std::format_string<Args...> fmt, Args&&... args)
        {
            std::cerr
                << "File: " << loc.file_name() << "(" << loc.line() << "," << loc.column() << ")\n"
                << "Function: " << loc.function_name() << "\n"
                << "Msg: " << std::vformat(fmt.get(), std::make_format_args(args...))
                << "\n";
        }

    };

#ifndef TEZ_RELEASE
#define TEZ_LOG(x, ...) Debug::log(std::source_location::current(), x, __VA_ARGS__)
#else
#define TEZ_LOG(x, ...)
#endif // !TEZ_RELEASE

}
