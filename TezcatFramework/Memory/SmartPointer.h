#pragma once

#include "../TezConfig.h"

#include <memory>
#include <concepts>
#include <type_traits>

#include <iostream>

namespace tezcat
{
    namespace type_tool
    {
        template<class T>
        struct PointerDeleter
        {
            constexpr PointerDeleter() noexcept = default;

            void operator()(T* pointer) const noexcept
            {
                static_assert(0 < sizeof(T), "can't delete an incomplete type");
                delete pointer;
            }
        };

        template<class T>
        struct PointerDeleter<T[]>
        {
            constexpr PointerDeleter() noexcept = default;

            void operator()(T* pointer) const noexcept
            {
                static_assert(0 < sizeof(T), "can't delete an incomplete type");
                delete[] pointer;
            }
        };

        template<class T>
        struct GetDeleter
        {
            using Deleter = PointerDeleter<T>;
        };

        template<class T>
        struct GetDeleter<T[]>
        {
            using Deleter = PointerDeleter<T[]>;
        };
    }

#pragma region Unique
    template<class T, class Deleter = type_tool::PointerDeleter<T>>
    class UniquePointer
    {
    public:
        using ElementType = typename std::remove_extent_t<T>;
        using ElementDeleter = typename type_tool::GetDeleter<ElementType>::Deleter;

    private:
        template<class U, class UDeleter>
        friend class UniquePointer;

        ElementType* mPointer{ nullptr };

    public:
        UniquePointer(const UniquePointer& other) = delete;

        UniquePointer()
        {

        }

        UniquePointer(ElementType* pointer) : mPointer(pointer)
        {

        }

        UniquePointer(UniquePointer&& other) noexcept
        {
            mPointer = std::exchange(other.mPointer, nullptr);
        }

        template<class Derived, class DerivedDeleter>
            requires(std::is_convertible_v<Derived, ElementType>)
        UniquePointer(UniquePointer<Derived, DerivedDeleter>&& other) noexcept
        {
            mPointer = static_cast<ElementType*>(std::exchange(other.mPointer, nullptr));
        }

        ~UniquePointer() noexcept
        {
            ElementDeleter{}(mPointer);
            mPointer = nullptr;
        }

        template<class Base, class BaseDeleter>
            requires(std::is_convertible_v<ElementType, Base>)
        void convertFormBaseClass(UniquePointer<Base, BaseDeleter>&& other) noexcept
        {
            if (mPointer)
            {
                ElementDeleter{}(mPointer);
            }

            mPointer = static_cast<ElementType*>(std::exchange(other.mPointer, nullptr));
        }

        template<class Derived, class DerivedDeleter>
            requires(std::is_convertible_v<Derived, ElementType>)
        void convertFromDerivedClass(UniquePointer<Derived, DerivedDeleter>&& other) noexcept
        {
            if (mPointer)
            {
                ElementDeleter{}(mPointer);
            }

            mPointer = static_cast<ElementType*>(std::exchange(other.mPointer, nullptr));
        }

    public:
        UniquePointer& operator=(const UniquePointer& other) = delete;

        UniquePointer& operator=(UniquePointer&& other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            if (mPointer)
            {
                ElementDeleter{}(mPointer);
                mPointer = nullptr;
            }

            mPointer = std::exchange(other.mPointer, nullptr);
        }

        ElementType* operator->() const noexcept { return mPointer; }

        ElementType& operator*() const noexcept { return *mPointer; }

    public:
        ElementType* release() noexcept
        {
            return std::exchange(mPointer, nullptr);
        }

        ElementType* get() noexcept { return mPointer; }

        ElementType* get() const noexcept { return mPointer; }

        void reset(ElementType* value)
        {
            if (mPointer)
            {
                ElementDeleter{}(mPointer);
            }

            mPointer = value;
        }

        ElementDeleter& getDeleter() noexcept
        {
            return ElementDeleter{};
        }

        ElementDeleter& getDeleter() const noexcept
        {
            return ElementDeleter{};
        }
    };

    template<class T, class Deleter>
    class UniquePointer<T[], Deleter>
    {
    public:
        using ElementType = typename std::remove_extent_t<T>;
        using ElementDeleter = typename type_tool::GetDeleter<ElementType[]>::Deleter;

    private:
        template<class U, class UDeleter>
        friend class UniquePointer;

        ElementType* mPointer{ nullptr };

    public:
        UniquePointer(const UniquePointer& other) = delete;

        UniquePointer() noexcept
        {

        }

        UniquePointer(ElementType* pointer) noexcept
            : mPointer(pointer)
        {

        }

        UniquePointer(UniquePointer&& other) noexcept
        {
            mPointer = std::exchange(other.mPointer, nullptr);
        }

        /// <summary>
        /// 基类转换
        /// </summary>
        template<class Derived, class DerivedDeleter>
        requires (std::is_convertible_v<Derived, ElementType>)
        UniquePointer(UniquePointer<Derived[], DerivedDeleter>&& other) noexcept
        {
            mPointer = dynamic_cast<ElementType*>(std::exchange(other.mElement, nullptr));
        }

        ~UniquePointer() noexcept
        {
            ElementDeleter{}(mPointer);
            mPointer = nullptr;
        }

        template<class Base, class BaseDeleter>
            requires(std::is_convertible_v<ElementType, Base>)
        void convertFormBaseClass(UniquePointer<Base, BaseDeleter>&& other) noexcept
        {
            if (mPointer)
            {
                ElementDeleter{}(mPointer);
            }

            mPointer = static_cast<ElementType*>(std::exchange(other.mPointer, nullptr));
        }

        template<class Derived, class DerivedDeleter>
            requires(std::is_convertible_v<Derived, ElementType>)
        void convertFromDerivedClass(UniquePointer<Derived, DerivedDeleter>&& other) noexcept
        {
            if (mPointer)
            {
                ElementDeleter{}(mPointer);
            }

            mPointer = static_cast<ElementType*>(std::exchange(other.mPointer, nullptr));
        }

    public:
        UniquePointer& operator=(const UniquePointer& other) = delete;

        UniquePointer& operator=(UniquePointer&& other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            if (mPointer)
            {
                Deleter{}(mPointer);
                mPointer = nullptr;
            }

            mPointer = std::exchange(other.mPointer, nullptr);
        }

        ElementType* operator->() const noexcept {
            return mPointer;
        }

        ElementType& operator*() const noexcept { return *mPointer; }

    public:
        ElementType* release() noexcept
        {
            return std::exchange(mPointer, nullptr);
        }

        ElementType* get() noexcept { return mPointer; }

        ElementType* get() const noexcept { return mPointer; }

        void reset(ElementType* value)
        {
            if (mPointer)
            {
                this->getDeleter()(mPointer);
            }

            mPointer = value;
        }

        ElementDeleter& getDeleter() noexcept
        {
            return ElementDeleter{};
        }

        ElementDeleter& getDeleter() const noexcept
        {
            return ElementDeleter{};
        }
    };
#pragma endregion

#pragma region Shared
    template<class T>
    class WeakPointer;

    struct SharedPointerBaseMetaData
    {
        int32_t mRefrenceCount{ 0 };
        int32_t mWeakRefrenceCount{ 0 };
        void* mPointer{ nullptr };


        SharedPointerBaseMetaData() = default;
        virtual ~SharedPointerBaseMetaData() = default;

        SharedPointerBaseMetaData(const SharedPointerBaseMetaData&) = delete;
        SharedPointerBaseMetaData(SharedPointerBaseMetaData&&) = delete;

        virtual void closeSharedPointer() = 0;
        virtual void closeWeakPointer() = 0;
    };

    struct SharedPointerDefaultMetaData : SharedPointerBaseMetaData
    {
        virtual void closeSharedPointer() override final
        {

        }

        virtual void closeWeakPointer() override final
        {

        }

        static SharedPointerBaseMetaData* getInstacne()
        {
            static SharedPointerDefaultMetaData instance;
            //std::cout << "SharedPointerMetaData Instacne\n";
            return &instance;
        }

    private:
        using SharedPointerBaseMetaData::SharedPointerBaseMetaData;
        SharedPointerDefaultMetaData() {}
        virtual ~SharedPointerDefaultMetaData() {}
    };

    template<class T, class Deleter>
    struct SharedPointerMetaData : public SharedPointerBaseMetaData
    {
        using SharedPointerBaseMetaData::SharedPointerBaseMetaData;

        SharedPointerMetaData() = default;
        virtual ~SharedPointerMetaData() = default;

        SharedPointerMetaData(const SharedPointerMetaData&) = delete;
        SharedPointerMetaData(SharedPointerMetaData&&) = delete;

        virtual void closeSharedPointer() override
        {
            if ((--mRefrenceCount) <= 0)
            {
                mRefrenceCount = 0;
                if (mPointer)
                {
                    Deleter{}((T*)mPointer);
                    mPointer = nullptr;
                }

                //如果还有弱引用存在,不删除元数据类
                if (mWeakRefrenceCount == 0)
                {
                    mWeakRefrenceCount = 0;
                    delete this;
                }
            }
        }

        virtual void closeWeakPointer() override
        {
            if ((--mWeakRefrenceCount) <= 0)
            {
                mWeakRefrenceCount = 0;
                //持有对象被删除了,才会删除元数据类
                if (mRefrenceCount == 0 && mWeakRefrenceCount == 0)
                {
                    delete this;
                }
            }
        }
    };

    template<class T>
    class SharedPointer
    {
    public:
        using ElementType = typename std::remove_extent_t<T>;
        using ElementDeleter = typename type_tool::GetDeleter<ElementType>::Deleter;

    private:
        template<class U>
        friend class SharedPointer;

        template<class U>
        friend class WeakPointer;

        SharedPointerBaseMetaData* mMetaData{ nullptr };

    public:
        SharedPointer()
            : mMetaData(SharedPointerDefaultMetaData::getInstacne())
        {

        }

        SharedPointer(ElementType* ptr)
            : mMetaData(new SharedPointerMetaData<ElementType, ElementDeleter>())
        {
            mMetaData->mPointer = ptr;
            mMetaData->mRefrenceCount = 1;
        }

        SharedPointer(const SharedPointer& other)
        {
            mMetaData = other.mMetaData;
            mMetaData->mRefrenceCount++;
        }

        SharedPointer(SharedPointer&& other) noexcept
        {
            mMetaData = other.mMetaData;
            other.reset();
        }

        ~SharedPointer() noexcept
        {
            mMetaData->closeSharedPointer();
            mMetaData = nullptr;
        }

    public:
        SharedPointer& operator=(const SharedPointer& other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }


            mMetaData->closeSharedPointer();
            mMetaData = other.mMetaData;
            mMetaData->mRefrenceCount++;

            return *this;
        }

        SharedPointer& operator=(SharedPointer&& other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            mMetaData = other.mMetaData;
            other.reset();

            return *this;
        }

        ElementType* operator->() const noexcept { return this->get(); }

        ElementType& operator*() const noexcept { return *this->get(); }

        explicit operator bool() const noexcept
        {
            return mMetaData->mPointer != nullptr;
        }

    public:

        /*
        * Before C++ 20
        * template<class Base, std::enable_if_t<std::is_convertible_v<ElementType, Base>, int> = 0>
        */
        template<class Base>
            requires(std::is_convertible_v<ElementType, Base>)
        void convertFromBaseClass(const SharedPointer<Base>& other) noexcept
        {
            mMetaData->closeSharedPointer();
            mMetaData = other.mMetaData;
            mMetaData->mRefrenceCount++;
        }

        template<class Derived>
            requires(std::is_convertible_v<Derived, ElementType>)
        void convertFromDerivedClass(const SharedPointer<Derived>& other) noexcept
        {
            mMetaData->closeSharedPointer();
            mMetaData = other.mMetaData;
            mMetaData->mRefrenceCount++;
        }


    public:
        ElementType* get() const noexcept { return static_cast<ElementType*>(mMetaData->mPointer); }

        auto refCount() const noexcept { return mMetaData->mRefrenceCount; }

        void reset() noexcept
        {
            mMetaData->closeSharedPointer();
            mMetaData = SharedPointerDefaultMetaData.getInstacne();
        }

        template<class U>
        void reset(U* ptr)
        {
            mMetaData->closeSharedPointer();
            mMetaData = new SharedPointerMetaData<U, type_tool::GetDeleter<U>::Deleter>();
            mMetaData->mPointer = ptr;
            mMetaData->mRefrenceCount = 1;
        }

        template<class U, class UDeleter>
        void reset(U* ptr)
        {
            mMetaData->closeSharedPointer();
            mMetaData = new SharedPointerMetaData<U, UDeleter>();
            mMetaData->mPointer = ptr;
            mMetaData->mRefrenceCount = 1;
        }

        ElementDeleter& getDeleter() noexcept
        {
            return ElementDeleter{};
        }

        ElementDeleter& getDeleter() const noexcept
        {
            return ElementDeleter{};
        }
    };

    template<class T>
    class SharedPointer<T[]>
    {
    public:
        using ElementType = typename std::remove_extent_t<T>;
        using ElementDeleter = typename type_tool::GetDeleter<ElementType[]>::Deleter;

    private:
        template<class U>
        friend class SharedPointer;

        template<class U>
        friend class WeakPointer;

        SharedPointerBaseMetaData* mMetaData{ nullptr };
        size_t mArraySize{ 0 };

    public:
        SharedPointer()
            : mMetaData(SharedPointerDefaultMetaData::getInstacne())
        {

        }

        SharedPointer(size_t size, ElementType* ptr)
            : mMetaData(new SharedPointerMetaData<ElementType, ElementDeleter>())
        {
            mMetaData->mPointer = ptr;
            mMetaData->mRefrenceCount = 1;
            mArraySize = size;
        }

        SharedPointer(const SharedPointer& other)
        {
            mMetaData = other.mMetaData;
            mMetaData->mRefrenceCount++;
            mArraySize = other.mArraySize;
        }

        SharedPointer(SharedPointer&& other) noexcept
        {
            mMetaData = other.mMetaData;
            mArraySize = other.mArraySize;

            other.reset();
        }

        ~SharedPointer() noexcept
        {
            mArraySize = 0;

            mMetaData->closeSharedPointer();
            mMetaData = nullptr;
        }

    public:
        SharedPointer& operator=(const SharedPointer& other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }


            mMetaData->closeSharedPointer();
            mMetaData = other.mMetaData;
            mArraySize = other.mArraySize;

            mMetaData->mRefrenceCount++;

            return *this;
        }

        SharedPointer& operator=(SharedPointer&& other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            mMetaData = other.mMetaData;
            mArraySize = other.mArraySize;

            other.reset();

            return *this;
        }

        ElementType* operator->() const noexcept { return this->get(); }

        ElementType& operator*() const noexcept { return *this->get(); }

        ElementType& operator[](size_t index)
        {
            if (index >= mArraySize)
            {
                throw std::out_of_range("array index out of range");
            }

            return this->get()[index];
        }

        explicit operator bool() const noexcept
        {
            return mMetaData->mPointer != nullptr;
        }

    public:
        template<class Base>
            requires(std::is_convertible_v<ElementType, Base>)
        void convertFromBaseClass(const SharedPointer<Base>& other) noexcept
        {
            mMetaData->closeSharedPointer();
            mMetaData = other.mMetaData;
            mArraySize = other.mArraySize;

            mMetaData->mRefrenceCount++;
        }

        template<class Derived>
            requires(std::is_convertible_v<Derived, ElementType>)
        void convertFromDerivedClass(const SharedPointer<Derived>& other) noexcept
        {
            mMetaData->closeSharedPointer();
            mMetaData = other.mMetaData;
            mArraySize = other.mArraySize;

            mMetaData->mRefrenceCount++;
        }


    public:
        ElementType* get() const noexcept { return static_cast<ElementType*>(mMetaData->mPointer); }

        auto refCount() const noexcept { return mMetaData->mRefrenceCount; }

        auto arraySize() const noexcept { return mArraySize; }

        void reset() noexcept
        {
            mMetaData->closeSharedPointer();
            mMetaData = SharedPointerDefaultMetaData.getInstacne();
            mArraySize = 0;
        }

        template<class U>
        void reset(size_t size, U* ptr)
        {
            mMetaData->closeSharedPointer();
            mMetaData = new SharedPointerMetaData<U, type_tool::GetDeleter<U[]>::Deleter>();
            mMetaData->mPointer = ptr;
            mMetaData->mRefrenceCount = 1;
            mArraySize = size;
        }

        template<class U, class UDeleter>
        void reset(size_t size, U* ptr)
        {
            mMetaData->closeSharedPointer();
            mMetaData = new SharedPointerMetaData<U, UDeleter>();
            mMetaData->mPointer = ptr;
            mMetaData->mRefrenceCount = 1;
            mArraySize = size;
        }

        ElementDeleter& getDeleter() noexcept
        {
            return ElementDeleter{};
        }

        ElementDeleter& getDeleter() const noexcept
        {
            return ElementDeleter{};
        }
    };
#pragma endregion Shared

#pragma region Weak
    template<class T>
    class WeakPointer
    {
        SharedPointerBaseMetaData* mMetaData{ nullptr };

    public:
        WeakPointer()
            : mMetaData(SharedPointerDefaultMetaData::getInstacne())
        {

        }

        WeakPointer(const SharedPointer<T>& sharedPointer) noexcept
        {
            mMetaData = sharedPointer.mMetaData;
            mMetaData->mWeakRefrenceCount++;
        }

        WeakPointer(const WeakPointer<T>& other) noexcept
        {
            mMetaData = other.mMetaData;
            mMetaData->mWeakRefrenceCount++;
        }

        WeakPointer(WeakPointer<T>&& other) noexcept
        {
            mMetaData = other.mMetaData;
            other.reset();
        }

        ~WeakPointer()
        {
            mMetaData->closeWeakPointer();
            mMetaData = nullptr;
        }

    public:
        WeakPointer& operator=(const SharedPointer<T>& sharedPointer) noexcept
        {
            mMetaData->closeWeakPointer();
            mMetaData = sharedPointer.mMetaData;
            mMetaData->mWeakRefrenceCount++;

            return *this;
        }

        WeakPointer& operator=(const WeakPointer<T>& other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            mMetaData->closeWeakPointer();
            mMetaData = other.mMetaData;
            mMetaData->mWeakRefrenceCount++;

            return *this;
        }

        WeakPointer& operator=(WeakPointer<T>&& other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            mMetaData->closeWeakPointer();
            mMetaData = other.mMetaData;
            other.reset();

            return *this;
        }

    public:
        void reset() noexcept
        {
            mMetaData->closeWeakPointer();
            mMetaData = SharedPointerDefaultMetaData::getInstacne();
        }

    public:
        bool lock() const noexcept
        {
            return mMetaData->mPointer != nullptr;
        }

        T* get() const noexcept { return static_cast<T*>(mMetaData->mPointer); }

        T* operator->() const noexcept { return this->get(); }

        T& operator*() const noexcept { return *this->get(); }
    };

    template<class T>
    class WeakPointer<T[]>
    {
        SharedPointerBaseMetaData* mMetaData{ nullptr };
        size_t mArraySize{ 0 };

    public:
        WeakPointer()
            : mMetaData(SharedPointerDefaultMetaData::getInstacne())
        {

        }

        WeakPointer(const SharedPointer<T[]>& sharedPointer) noexcept
        {
            mMetaData = sharedPointer.mMetaData;
            mMetaData->mWeakRefrenceCount++;
            mArraySize = sharedPointer.mArraySize;
        }

        WeakPointer(const WeakPointer<T[]>& other) noexcept
        {
            mMetaData = other.mMetaData;
            mArraySize = other.mArraySize;

            mMetaData->mWeakRefrenceCount++;
        }

        WeakPointer(WeakPointer<T[]>&& other) noexcept
        {
            mMetaData = other.mMetaData;
            mArraySize = other.mArraySize;

            other.reset();
        }

        ~WeakPointer()
        {
            mMetaData->closeWeakPointer();
            mArraySize = 0;
            mMetaData = nullptr;
        }

    public:
        WeakPointer& operator=(const SharedPointer<T[]>& sharedPointer) noexcept
        {
            mMetaData->closeWeakPointer();
            mMetaData = sharedPointer.mMetaData;
            mArraySize = sharedPointer.mArraySize;

            mMetaData->mWeakRefrenceCount++;

            return *this;
        }

        WeakPointer& operator=(const WeakPointer<T[]>& other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            mMetaData->closeWeakPointer();
            mMetaData = other.mMetaData;
            mArraySize = other.mArraySize;

            mMetaData->mWeakRefrenceCount++;

            return *this;
        }

        WeakPointer& operator=(WeakPointer<T[]>&& other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            mMetaData->closeWeakPointer();
            mMetaData = other.mMetaData;
            mArraySize = other.mArraySize;

            other.reset();

            return *this;
        }

    public:
        void reset() noexcept
        {
            mMetaData->closeWeakPointer();
            mMetaData = SharedPointerDefaultMetaData::getInstacne();
            mArraySize = 0;
        }

        size_t arraySize() const noexcept
        {
            return mArraySize;
        }

    public:
        bool lock() const noexcept
        {
            return mMetaData->mPointer != nullptr;
        }

        T* get() const noexcept { return static_cast<T*>(mMetaData->mPointer); }

        T* operator->() const noexcept { return this->get(); }

        T& operator*() const noexcept { return *this->get(); }

        T& operator[](size_t index)
        {
            if (index >= mArraySize)
            {
                throw std::out_of_range("array index out of range");
            }

            return this->get()[index];
        }
    };
#pragma endregion

}
