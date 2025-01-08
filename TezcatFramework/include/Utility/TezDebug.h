#pragma once

#include "../TezConfig.h"

namespace tezcat
{
    class TezDebug
    {
    public:

        template<typename ...Args>
        static void log(const std::source_location& loc, const std::format_string<Args...>& fmt, Args&&... args)
        {
            std::cerr
                << "[File]: " << loc.file_name() << "(" << loc.line() << "," << loc.column() << ")\n"
                << "[Function]: " << loc.function_name() << "\n"
                << "[Msg]: " << std::vformat(fmt.get(), std::make_format_args(args...))
                << "\n";
        }

        template<typename ...Args>
        static void log(const std::format_string<Args...>& fmt, Args&&... args)
        {
            std::cerr
                << "[Msg]: " << std::vformat(fmt.get(), std::make_format_args(args...))
                << "\n";
        }
    };

#ifndef TEZ_RELEASE
#define TEZ_LOG_LINE(content) std::cerr << content << "\n"
#define TEZ_LOG(fmt, ...) TezDebug::log(fmt, __VA_ARGS__)
#define TEZ_LOGF(fmt, ...) TezDebug::log(std::source_location::current(), fmt, __VA_ARGS__)
#else
#define TEZ_PRINT_LINE(content)
#define TEZ_LOG(fmt, ...)
#define TEZ_LOGF(fmt, ...
#endif // !TEZ_RELEASE

}
