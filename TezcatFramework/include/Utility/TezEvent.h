#pragma once

#include "../TezConfig.h"

namespace tezcat
{
    template<typename... Args>
    class TezEventDelegate
    {
    public:
        using F = std::function<void(Args...)>;

    private:
        struct Comparer
        {
            bool operator()(const F& a, const F& b) const
            {
                return a.target<void(Args...)>() == b.target<void(Args...)>();
            }
        };

        struct Hash
        {
            std::size_t operator()(const F& f) const
            {
                static std::hash<void*> hs;
                return hs(f.target<void(Args...)>());
            }
        };

        using USet = std::unordered_set<F, Hash, Comparer>;
        using UMap = std::unordered_map<void*, USet>;

        UMap mMap;
    public:
        TezEventDelegate() { }
        ~TezEventDelegate() { }

    public:
        template<class Master, class Func>
        void subscribe(Master* master, Func&& func)
        {
            auto [it, flag] = mMap.try_emplace(master, USet());
            if (flag)
            {
                TEZ_CONSOLE_WRITE_LINE("Insert Successed");
            }

            it->second.emplace(std::bind_front(TEZ_FWD(func), master));
        }

        template<class Master, class Func>
        bool unsubscribe(Master* master, Func&& func)
        {
            auto it = mMap.find(master);
            if (it != mMap.end())
            {
                it->second.erase(std::bind_front(TEZ_FWD(func), master));
                return true;
            }

            return false;
        }

        bool unsubscribeAll(void* master)
        {
            auto it = mMap.find(master);
            if (it != mMap.end())
            {
                mMap.erase(it);
                return true;
            }

            return false;
        }

        template<class... Args2>
        void dispatch(Args2&&... args)
        {
            for (auto& pair : mMap)
            {
                for (auto& f : pair.second)
                {
                    f(TEZ_FWD(args)...);
                }
            }
        }
    };
}
