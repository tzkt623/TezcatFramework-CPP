#pragma once

#include "TezCPP.h"

namespace tezcat
{
    using TezTypeUID = uint32_t;

    class TezTypeManager
    {
        template<typename Owner>
        struct TypeBuilder
        {
            //这种方法不行,因为在分配ID时这几个静态变量居然还没有初始化
            //static TezTypeUID TypeID;
            //static std::unordered_map<std::string, TezTypeUID> TypeMap;
            //只有把变量放到函数里面才行

            static auto& getTypeMap()
            {
                static std::unordered_map<std::type_index, TezTypeUID> TypeMap;
                return TypeMap;
            }

            static auto& getTypeID()
            {
                static TezTypeUID TypeID{ 1 };
                return TypeID;
            }
        };

    public:
        template<typename Owner, typename T>
        static TezTypeUID registerComponent()
        {
            auto result = TypeBuilder<Owner>::getTypeMap().try_emplace(typeid(T), 0);
            if (result.second)
            {
                result.first->second = TypeBuilder<Owner>::getTypeID()++;
                return result.first->second;
            }
            else
            {
                return result.first->second;
            }
        }

        template<typename Owner>
        static auto& getInfoMap() { return TypeBuilder<Owner>::getTypeMap(); }

        //template<typename T>
        //static TezTypeUID registerComponent()
        //{
        //    auto result = TypeMap.try_emplace(typeid(T).name(), 0);
        //    if (result.second)
        //    {
        //        result.first->second = TypeID++;
        //        return result.first->second;
        //    }
        //    else
        //    {
        //        return result.first->second;
        //    }
        //}

    private:
        //static TezTypeUID TypeID;
        //static std::unordered_map<std::string, TezTypeUID> TypeMap;
    };

    //TezTypeUID TezTypeManager::TypeID = 1;
    //std::unordered_map<std::string, TezTypeUID> TezTypeManager::TypeMap;

    //template<typename Owner>
    //std::unordered_map<std::string, TezTypeUID> TezTypeManager::TypeBuilder<Owner>::TypeMap;
    //
    //template<typename Owner>
    //TezTypeUID TezTypeManager::TypeBuilder<Owner>::TypeID;

    //-------------------------------------------------------------//

    template<typename Owner, typename T>
    struct TezTypeInfo
    {
        static const TezTypeUID UID;
        static const std::string_view Name;
    };

    template<typename Owner, typename T>
    const TezTypeUID TezTypeInfo<Owner, T>::UID = TezTypeManager::registerComponent<Owner, T>();

    template<typename Owner, typename T>
    const std::string_view TezTypeInfo<Owner, T>::Name = typeid(T).name();
}
