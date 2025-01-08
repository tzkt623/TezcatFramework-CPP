#pragma once

#define TEZCAT_STATIC_LIB 1

#ifdef TEZCAT_DYNAMIC_LIB
#define TEZCAT_API __declspec(dllimport)
#elif TEZCAT_STATIC_LIB
#define TEZCAT_API
#else 
#define TEZCAT_API __declspec(dllexport)
#endif

#ifndef TEZCAT_RELEASE
#define LOG(x) std::cout << x << std::endl;


#else
#define LOG(x)


#endif


#define TEZ_FWD(arg) std::forward<decltype(arg)>(arg)
#define TEZ_BIND(func, ...) [__VA_ARGS__] (auto &&..._args) { func(FWD(_args)...); }


#define TEZ_PROPERTY_BASE(argType, argName, getType, setType) \
private:\
argType m##argName;\
public:\
getType get##argName() { return m##argName;}\
void set##argName(setType value) { m##argName = value; }\
private:

#define TEZ_PROPERTY(argType, argName) TEZ_PROPERTY_BASE(argType, argName, argType, argType)

#define TEZ_PAUSE std::system("pause")

#ifndef TEZ_RELEASE
#define TEZ_CONSOLE_ENDL std::cout << "\n"
#define TEZ_CONSOLE_WRITE_LINE(X) std::cout << X << "\n"
#define TEZ_CONSOLE_WRITE(X) std::cout << X
#else
#define TEZ_CONSOLE_ENDL
#define TEZ_CONSOLE_WRITE_LINE(X)
#define TEZ_CONSOLE_WRITE(X)
#endif


