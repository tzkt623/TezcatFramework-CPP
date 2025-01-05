#pragma once

#include <string>
#include <string_view>
#include <format>

#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <ranges>
#include <ostream>
#include <iostream>

#include <regex>

#include <memory>
#include <typeindex>
#include <functional>

#include <coroutine>
#include <exception>

#include <thread>
#include <condition_variable>

#include <concepts>

#include <stdint.h>


#define TEZ_CONSOLE_ENDL std::cout << std::endl
#define TEZ_CONSOLE_WRITE_LINE(X) std::cout << X << std::endl
#define TEZ_CONSOLE_WRITE(X) std::cout << X


#define TEZ_PAUSE system("pause")
