#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <string_view>
#include <vector>
#include <ostream>
#include <iostream>


template<typename Belong>
class IDString
{
	struct CompareHash
	{
		std::size_t operator() (const IDString& str) const
		{
			return str.getUID();
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
	template<typename Value>
	using UMap = std::unordered_map<IDString, Value, CompareHash, Comparer>;

	template<typename Value>
	using USet = std::unordered_set<IDString, CompareHash, Comparer>;

public:
	IDString()
		: m_ID(-1)
	{

	}

	IDString(const char* string)
		: m_ID(-1)
	{
		this->init(string);
	}

	IDString(std::string&& string)
		: m_ID(-1)
	{
		this->init(std::forward<std::string>(string));
	}

	IDString(const std::string& other)
		: m_ID(-1)
	{
		this->init(other);
	}

	IDString(const IDString& other)
		: m_ID(other.m_ID)
	{

	}

	IDString(IDString&& other) noexcept
		: m_ID(other.m_ID)
	{
		other.m_ID = -1;
	}

	~IDString()
	{

	}

	inline const int getUID() const
	{
		return m_ID;
	}

	const char* getStringData() const
	{
		return s_StringWithID[m_ID].data();
	}

	const std::string_view& getString() const
	{
		return s_StringWithID[m_ID];
	}

	IDString& operator = (const char* data)
	{
		this->init(data);
		return *this;
	}

	IDString& operator = (const std::string& data)
	{
		this->init(data);
		return *this;
	}

	IDString& operator = (std::string&& data)
	{
		this->init(std::forward<std::string>(data));
		return *this;
	}

	IDString& operator = (IDString&& idString)
	{
		m_ID = idString.m_ID;
		idString.m_ID = -1;
		return *this;
	}

	bool operator == (const IDString& other) const
	{
		return m_ID == other.m_ID;
	}

	bool operator != (const IDString& other) const
	{
		return m_ID != other.m_ID;
	}

	operator int()
	{
		return m_ID;
	}

	operator const char* ()
	{
		return s_StringWithID[m_ID].data();
	}

private:
	void init(const std::string& data)
	{
		auto pair = s_IDWithString.try_emplace(data, m_ID);
		if (pair.second)
		{
			m_ID = static_cast<int>(s_StringWithID.size());
			pair.first->second = m_ID;
			s_StringWithID.emplace_back(pair.first->first);
		}
		else
		{
			m_ID = pair.first->second;
		}
	}

	void init(std::string&& data)
	{
		auto pair = s_IDWithString.try_emplace(std::forward<std::string>(data), m_ID);
		if (pair.second)
		{
			m_ID = static_cast<int>(s_StringWithID.size());
			pair.first->second = m_ID;
			s_StringWithID.emplace_back(pair.first->first);
		}
		else
		{
			m_ID = pair.first->second;
		}
	}

private:
	int m_ID;

public:
	static auto allStringCount() { return s_StringWithID.size(); }

private:
	static std::vector<std::string_view> s_StringWithID;
	static std::unordered_map<std::string, int> s_IDWithString;
};

template<typename Belong>
std::unordered_map<std::string, int> IDString<Belong>::s_IDWithString;

template<typename Belong>
std::vector<std::string_view> IDString<Belong>::s_StringWithID;


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