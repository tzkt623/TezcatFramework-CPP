#pragma once

#include "../TezConfig.h"

namespace tezcat {

    template<typename Belong>
    class IDString
    {
        using IndexID = std::size_t;

        struct CompareHash
        {
            std::size_t operator() (const IDString& str) const
            {
                static std::hash<std::size_t> hs;
                return hs(str.getUID());
            }
        };

        struct Comparer
        {
            bool operator() (const IDString& a, const IDString& b) const
            {
                return a == b;
            }
        };

    public:
        using UMap = std::unordered_map<IDString, IndexID, CompareHash, Comparer>;
        using USet = std::unordered_set<IDString, CompareHash, Comparer>;

    public:
        IDString()
        {

        }

        IDString(const char* string)
        {
            this->init(string);
        }

        IDString(std::string&& string)
        {
            this->init(std::forward<std::string>(string));
        }

        IDString(const std::string& other)
        {
            this->init(other);
        }

        IDString(const IDString& other)
            : mID(other.mID)
        {

        }

        IDString(IDString&& other) noexcept
            : mID(other.mID)
        {
            other.mID = 0;
        }

        ~IDString()
        {

        }

        const IndexID getUID() const
        {
            return mID;
        }

        const char* getStringData() const
        {
            return sStringArray[mID]->data();
        }

        std::string_view getString() const
        {
            return { *sStringArray[mID] };
        }

        IDString& operator=(const char* data)
        {
            this->init(data);
            return *this;
        }

        IDString& operator=(const std::string& data)
        {
            this->init(data);
            return *this;
        }

        IDString& operator=(std::string&& data)
        {
            this->init(std::forward<std::string>(data));
            return *this;
        }

        IDString& operator=(IDString&& idString)
        {
            mID = idString.mID;
            idString.mID = 0;
            return *this;
        }

        bool operator==(const IDString& other) const
        {
            return mID == other.mID;
        }

        bool operator!=(const IDString& other) const
        {
            return mID != other.mID;
        }

        operator IndexID()
        {
            return mID;
        }

        operator const char* ()
        {
            return sStringArray[mID]->data();
        }

    private:
        void init(const std::string& data)
        {
            auto it = sStringViewMap.find(data);
            if (it != sStringViewMap.end())
            {
                mID = it->second;
            }
            else
            {
                mID = sStringArray.size();
                sStringArray.emplace_back(new std::string(data));
                sStringViewMap.emplace(*sStringArray.back(), mID);
            }
        }

        void init(std::string&& data)
        {
            auto it = sStringViewMap.find(data);
            if (it != sStringViewMap.end())
            {
                mID = it->second;
            }
            else
            {
                mID = sStringArray.size();
                sStringArray.emplace_back(new std::string(std::move(data)));
                sStringViewMap.emplace(*sStringArray.back(), mID);
            }
        }

    private:
        IndexID mID{ 0 };

    public:
        static auto allStringCount() { return sStringArray.size(); }

    private:
        static std::vector<std::string*> sStringArray;
        static std::unordered_map<std::string_view, IndexID> sStringViewMap;
    };

    template<typename Belong>
    std::unordered_map<std::string_view, typename IDString<Belong>::IndexID> IDString<Belong>::sStringViewMap;

    template<typename Belong>
    std::vector<std::string*> IDString<Belong>::sStringArray{ new std::string("v^v TezError IDString ~^~") };

    template<typename Belong>
    std::ostream& operator << (std::ostream& out, IDString<Belong>& idString)
    {
        return out << idString.getString();
    }

    // template<typename Belong>
    // bool operator == (const IDString<Belong>& a, const IDString<Belong>& b)
    // {
    // 	return a.getUID() == b.getUID();
    // }

    // template<typename Belong>
    // bool operator != (const IDString<Belong>& a, const IDString<Belong>& b)
    // {
    // 	return a.getUID() != b.getUID();
    // }
}
