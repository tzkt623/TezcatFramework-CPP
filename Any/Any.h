#pragma once
#include "../Utility/Utility.h"


class Any
{
    struct Container
    {
        virtual ~Container() {}
        virtual Container* clone() = 0;
        virtual std::string toString() const = 0;
    };

    template<typename T>
    struct ContainerT : Container
    {
        T m_Value;

        //此处的T&& 是万能引用
        ContainerT(T&& other) : m_Value(std::forward<T>(other)) { }

        ContainerT(T& other) : m_Value(other) { }

        virtual ~ContainerT()
        {

        }

        Container* clone() final
        {
            return new ContainerT<T>(m_Value);
        }

        std::string toString() const
        {
            if constexpr (std::is_arithmetic_v<T>)
            {
                return std::to_string(m_Value);
            }
            else if constexpr (std::is_same_v<T, std::string>)
            {
                return m_Value;
            }
            else if constexpr (std::is_class_v<T>)
            {
                return typeid(T).name();
            }
            else if constexpr (std::is_union_v<T>)
            {
                return typeid(T).name();
            }
            else if constexpr (std::is_enum_v<T>)
            {
                return typeid(T).name();
            }
            else if constexpr (std::is_function_v<T>)
            {
                return typeid(T).name();
            }
            else if constexpr (std::is_pointer_v<T>)
            {
                return typeid(T).name();
            }
            else
            {
                return "UnKnown Type";
            }
        }

        ContainerT& operator=(const ContainerT&) = delete;
    };
public:
    Any() : m_TypeIndex(typeid(void)), m_Container(nullptr)
    {
    }

    Any(const Any& other) : m_TypeIndex(other.m_TypeIndex), m_Container(other.clone())
    {
    }

    Any(Any&& other) noexcept : m_TypeIndex(other.m_TypeIndex), m_Container(other.m_Container)
    {
        other.m_Container = nullptr;
    }

    template<typename T>
    Any(T& value) : m_TypeIndex(typeid(T)), m_Container(new ContainerT<T>(value))
    {
    }

    template<typename T>
    Any(T&& value) : m_TypeIndex(typeid(T)), m_Container(new ContainerT<T>(std::forward<T>(value)))
    {
    }

    ~Any()
    {
        delete m_Container;
    }

private:
    Container* clone() const
    {
        if (m_Container != nullptr)
        {
            return m_Container->clone();
        }

        return nullptr;
    }

public:
    bool empty() { return m_Container == nullptr; }

    template<class U>
    bool is() const
    {
        return m_TypeIndex == std::type_index(typeid(U));
    }

    template<class U>
    U& cast()
    {
        if (!this->is<U>())
        {
            throw std::bad_cast();
        }
        else
        {
            return dynamic_cast<ContainerT<U>*>(m_Container)->m_Value;
        }
    }

    Any& operator=(const Any& other)
    {
        if (m_Container == other.m_Container)
        {
            return *this;
        }

        m_Container = m_Container->clone();
        m_TypeIndex = other.m_TypeIndex;
        return *this;
    }

    Any& operator=(Any&& other) noexcept
    {
        m_Container = other.m_Container;
        m_TypeIndex = other.m_TypeIndex;

        other.m_Container = nullptr;
        return *this;
    }

    template <class T>
    Any& operator=(T& value)
    {
        delete m_Container;

        m_Container = new ContainerT<T>(value);
        m_TypeIndex = std::type_index(typeid(T));

        return *this;
    }

    template <class T>
    Any& operator=(T&& value)
    {
        delete m_Container;

        m_Container = new ContainerT<T>(std::forward<T>(value));
        m_TypeIndex = std::type_index(typeid(T));

        return *this;
    }

public:
    std::string toString()
    {
        return m_Container->toString();
    }

private:
    std::type_index m_TypeIndex;
    Container* m_Container;
};

