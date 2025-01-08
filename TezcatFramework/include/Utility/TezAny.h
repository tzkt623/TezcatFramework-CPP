#pragma once
#include "../TezConfig.h"

namespace tezcat
{
    class TezAny
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
        TezAny() : mTypeIndex(typeid(void)), mContainer(nullptr)
        {
        }

        TezAny(const TezAny& other) : mTypeIndex(other.mTypeIndex), mContainer(other.clone())
        {
        }

        TezAny(TezAny&& other) noexcept : mTypeIndex(other.mTypeIndex), mContainer(other.mContainer)
        {
            other.mContainer = nullptr;
        }

        template<typename T>
        TezAny(T& value) : mTypeIndex(typeid(T)), mContainer(new ContainerT<T>(value))
        {
        }

        template<typename T>
        TezAny(T&& value) : mTypeIndex(typeid(T)), mContainer(new ContainerT<T>(std::forward<T>(value)))
        {
        }

        ~TezAny()
        {
            delete mContainer;
        }

    private:
        Container* clone() const
        {
            if (mContainer != nullptr)
            {
                return mContainer->clone();
            }

            return nullptr;
        }

    public:
        bool empty() { return mContainer == nullptr; }

        template<class U>
        bool is() const
        {
            return mTypeIndex == std::type_index(typeid(U));
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
                return dynamic_cast<ContainerT<U>*>(mContainer)->m_Value;
            }
        }

        TezAny& operator=(const TezAny& other)
        {
            if (mContainer == other.mContainer)
            {
                return *this;
            }

            mContainer = mContainer->clone();
            mTypeIndex = other.mTypeIndex;
            return *this;
        }

        TezAny& operator=(TezAny&& other) noexcept
        {
            mContainer = other.mContainer;
            mTypeIndex = other.mTypeIndex;

            other.mContainer = nullptr;
            return *this;
        }

        template <class T>
        TezAny& operator=(T& value)
        {
            delete mContainer;

            mContainer = new ContainerT<T>(value);
            mTypeIndex = std::type_index(typeid(T));

            return *this;
        }

        template <class T>
        TezAny& operator=(T&& value)
        {
            delete mContainer;

            mContainer = new ContainerT<T>(std::forward<T>(value));
            mTypeIndex = std::type_index(typeid(T));

            return *this;
        }

    public:
        std::string toString()
        {
            return mContainer->toString();
        }

    private:
        std::type_index mTypeIndex;
        Container* mContainer;
    };

}
