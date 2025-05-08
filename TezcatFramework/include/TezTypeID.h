#pragma once

#include "TezCPP.h"

namespace tezcat
{
    using uint64 = uint64_t;

    union TezTypeID
    {
        uint64 UID;

        struct
        {
            //low
            uint64 Index : 32;
            //hight
            uint64 Category : 32;
        };
    };

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
                static std::unordered_map<std::type_index, TezTypeID> TypeMap;
                return TypeMap;
            }

            static auto& getTypeID()
            {
                static uint64 TypeID{ 1 };
                return TypeID;
            }

            static const uint64 getCategoryID()
            {
                static const uint64 CategoryID{ TezTypeManager::giveCategoryID() };
                return CategoryID;
            }
        };

    public:
        template<typename Owner, typename T>
        static TezTypeID registerComponent()
        {
            auto result = TypeBuilder<Owner>::getTypeMap().try_emplace(typeid(T), 0);
            if (result.second)
            {
                result.first->second.Index = TypeBuilder<Owner>::getTypeID()++;
                result.first->second.Category = TypeBuilder<Owner>::getCategoryID();
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

        static uint64 giveCategoryID()
        {
            return CategoryID++;
        }

    private:
        static uint64 CategoryID;

        //static uint64 TypeID;
        //static std::unordered_map<std::string, TezTypeUID> TypeMap;
    };
    uint64 TezTypeManager::CategoryID = 1;

    //uint64 TezTypeManager::TypeID = 1;
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
        static const std::string_view Name;
        static const TezTypeID TypeID;
        static const uint64 getTypeCategory() { return TypeID.Category; }
        static const uint64 getTypeIndex() { return TypeID.Index; }
        static const uint64 getTypeUID() { return TypeID.UID; }
    };

    template<typename Owner, typename T>
    const TezTypeID TezTypeInfo<Owner, T>::TypeID = TezTypeManager::registerComponent<Owner, T>();

    template<typename Owner, typename T>
    const std::string_view TezTypeInfo<Owner, T>::Name = typeid(T).name();

    bool operator==(const TezTypeID& a, const TezTypeID& b)
    {
        return a.UID == b.UID;
    }

    bool operator!=(const TezTypeID& a, const TezTypeID& b)
    {
        return a.UID != b.UID;
    }
}
