#pragma once
#include <functional>
#include <vector>


template<typename... Args>
class Event
{
	class Data
	{
	public:
		void* master;
		std::function<void(Args...)> callback;
	};
public:
	Event() { }
	~Event()
	{
		for (auto d : m_List)
		{
			delete d;
		}
	}

public:
	void addListener(void* master, const std::function<void(Args...)>& function)
	{
		m_List.push_back(new Data{ master, std::move(function) });
	}

	bool removeListener(void* master)
	{
		auto result = std::find(m_List.begin(), m_List.end(), master);
		if (result != m_List.end())
		{
			m_List.erase(result);
			return true;
		}

		return false;
	}

	void dispatch(Args... args)
	{
		for (auto d : m_List)
		{
			//			d->callback(std::forward<Args>(args)...);
			d->callback(args...);
		}
	}

private:
	std::vector<Data*> m_List;
};