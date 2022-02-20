#pragma once
#include <vector>
#include <utility>  
#include <string>
#include <iostream>
#include <typeindex>

/*
* 注意注释
* 这里有两种Component结构
* 一种是每一个对象都包含一个type信息
* 
* 一种是每种对象包含同一个type信息
* 
* 也就是静态信息和动态信息的区别
* 
* 静态com:
* 占用空间少
* 不用每次都初始化
* 可以有静态类型取得方法搞骚操作
* 每个com都必须由模板诞生,否则无法生成type信息
* 
* 动态type信息:
* 类型判断直接
* 占用空间多
* 每个对象都要初始化
* 可以随时修改type信息
* 继承结构没有硬性要求
*/


class Component
{
public:
	// 	Component(std::type_index&& index) :
	// 		m_TypeIndex(std::forward<std::type_index>(index))
	// 	{
	// 
	// 	}

	Component()
	{

	}
	virtual ~Component() {}

	template<class Com>
	bool is() { return this->is(std::type_index(typeid(Com))); }

	// 	template<class Com>
	// 	bool is() { return std::type_index(typeid(Com)) == m_TypeIndex; }

	virtual const std::type_index& getComponentType() = 0;

protected:
	// 	template<typename T>
	// 	void setTypeIndex() { m_TypeIndex = typeid(T); }

	virtual bool is(const std::type_index& type) = 0;

protected:
	//	std::type_index m_TypeIndex;
};

template<typename Com>
class ComponentT : public Component
{
public:
	// 	ComponentT() : Component(typeid(Com))
	// 	{
	// 
	// 	}

	ComponentT() {}
	virtual ~ComponentT() {}

	const std::type_index& getComponentType() override { return s_TypeIndex; }
	bool is(const std::type_index& type) override { return s_TypeIndex == type; }

public:
	static const std::type_index& getComponentTypeStatic() { return s_TypeIndex; }

private:
	static std::type_index s_TypeIndex;
};

template<typename Com>
std::type_index ComponentT<Com>::s_TypeIndex = typeid(Com);

class Com1 : public ComponentT<Com1>
{
public:
	Com1(std::string name, int i) {}
	~Com1() {}


};

class Com2 :public ComponentT<Com2>
{
public:
	Com2(void* p, double d) {}
	~Com2() {}


};


class Com3 : public ComponentT<Com3>
{
public:
	Com3()
	{
		//		m_TypeIndex = typeid(*this);
	}
	~Com3() {}


};

template<typename T>
class Com3_5 : public ComponentT<T>
{

};


class Com4 : public Com3_5<Com4>
{
public:
	Com4()
	{
		//		this->setTypeIndex<Com4>();
	}
};


class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() {}

	void addChild(GameObject* gameObject)
	{
		m_Children.push_back(gameObject);
	}

public:
	template<class Com>
	Com* getComponent()
	{
		for (auto com : m_ComponentList)
		{
			if (com->is<Com>())
			{
				return (Com*)com;
			}
		}

		return nullptr;
	}

	template<class Com>
	Com* getComponentInChildren()
	{
		for (auto com : m_ComponentList)
		{
			if (com->is<Com>())
			{
				return (Com*)com;
			}
		}

		for (auto child : m_Children)
		{
			auto result = child->getComponentInChildren<Com>();
			if (result != nullptr)
			{
				return result;
			}
		}

		return nullptr;
	}

	template<typename Com, typename... Args>
	Com* addComponent(Args&&... args)
	{
		auto component = new Com(std::forward<Args>(args)...);
		m_ComponentList.push_back(component);
		return component;
	}

	void addComponent(Component* component)
	{
		m_ComponentList.push_back(component);
	}

private:
	std::vector<Component*> m_ComponentList;
	std::vector<GameObject*> m_Children;
};