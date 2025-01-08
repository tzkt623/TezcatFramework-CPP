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
            return sStringWithID[mID].data();
        }

        const std::string_view& getString() const
        {
            return sStringWithID[mID];
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
            return sStringWithID[mID].data();
        }

    private:
        void init(const std::string& data)
        {
            auto pair = sIDWithString.try_emplace(data, 0);
            if (pair.second)
            {
                mID = sStringWithID.size();
                pair.first->second = mID;
                sStringWithID.emplace_back(pair.first->first);
            }
            else
            {
                mID = pair.first->second;
            }
        }

        void init(std::string&& data)
        {
            auto pair = sIDWithString.try_emplace(std::forward<std::string>(data), 0);
            if (pair.second)
            {
                mID = sStringWithID.size();
                pair.first->second = mID;
                sStringWithID.emplace_back(pair.first->first);
            }
            else
            {
                mID = pair.first->second;
            }
        }

    private:
        IndexID mID{ 0 };

    public:
        static auto allStringCount() { return sStringWithID.size(); }

    private:
        static std::vector<std::string_view> sStringWithID;
        static std::unordered_map<std::string, IndexID> sIDWithString;
    };

    template<typename Belong>
    std::unordered_map<std::string, typename IDString<Belong>::IndexID> IDString<Belong>::sIDWithString;

    template<typename Belong>
    std::vector<std::string_view> IDString<Belong>::sStringWithID{ std::string_view("v^v TezError IDString ~^~") };

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
