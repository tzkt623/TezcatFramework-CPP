#pragma once

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
