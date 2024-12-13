#include "Coroutine.h"


template<typename T>
struct MyCoroutine
{
    struct MyAwaitable;
    struct MyPromise
    {
        T value;

        std::suspend_always initial_suspend()
        {
            MY_CONSOLE_WRITE_LINE("initial_suspend");
            return {};
        }
        std::suspend_never final_suspend() noexcept
        {
            MY_CONSOLE_WRITE_LINE("final_suspend");
            return {};
        }

        void return_void()
        {
            MY_CONSOLE_WRITE_LINE("return_void");
        }

        // 		void return_value(T value)
        // 		{
        // 			std::cout << "return_value" << std::endl;
        // 			this->value = value;
        // 		}

        void unhandled_exception() { }

        MyAwaitable yield_value(T value)
        {
            //在这里保存你计算好的值
            //或者你也可以在这里计算
            MY_CONSOLE_WRITE_LINE("yield_value");
            this->value = value;
            return { this };
        }

        MyCoroutine get_return_object()
        {
            MY_CONSOLE_WRITE_LINE("get_return_object");
            return { std::coroutine_handle<MyPromise>::from_promise(*this) };
        }
    };
    using promise_type = MyPromise;

    struct MyAwaitable
    {
        promise_type* promise;

        constexpr bool await_ready() const noexcept
        {
            MY_CONSOLE_WRITE_LINE("await_ready");
            return false;
        }

        constexpr void await_suspend(std::coroutine_handle<> handle) const noexcept
        {
            MY_CONSOLE_WRITE_LINE("await_suspend");
        }

        T await_resume() const noexcept
        {
            MY_CONSOLE_WRITE_LINE("await_resume");
            return promise->value;
        }
    };

    std::coroutine_handle<promise_type> handle;

    ~MyCoroutine()
    {
        handle.destroy();
    }

    bool next()
    {
        this->handle.resume();
        return !this->handle.done();
    }

    bool next(T value)
    {
        this->handle.promise().value = value;
        this->handle.resume();
        return !this->handle.done();
    }

    T getValue()
    {
        return this->handle.promise().value;
    }
};


MyCoroutine<int> create()
{
    //做一些计算
    //然后利用下面的表达式保存值
    int m = 50;
    m *= 13;
    //co_yield m = co_await promise.yield_value(m)
    //co_await可以有返回值,为await_resume()函数的返回值,也可以为void;
    auto result = co_yield m;
    co_yield result;
    co_yield 777;

    std::cout << m << std::endl;

    //如果你只是想等待一帧,可以直接用std的类
    //这里co_await得到的值为上面的777
    co_await std::suspend_always();

    int i = 0;
    while (true)
    {
        auto k = co_yield i;
        i = k + 10;
    }
}


void test()
{
    // 	auto cor = create();
    // 
    // 	for (int i = 0; i < 10; i++)
    // 	{
    // 		std::cout << cor.getNextValue() << std::endl;
    // 	}

// 	auto creator = []()->MyCoroutine<int>
// 	{
// 		co_yield 0;
// 		co_yield 1;
// 		co_yield 2;
// 
// 		int i = 6;
// 		while (true)
// 		{
// 			//			co_yield i++;
// 			auto k = co_yield i;
// 			i = k + 10;
// 		}
// 	};
// 
// 	auto cor2 = creator();
    auto cor2 = create();
    MY_CONSOLE_WRITE_LINE("----------------------");

    for (int i = 0; i < 6; i++)
    {
        if (cor2.next())
        {
            std::cout << cor2.getValue() << std::endl;
            MY_CONSOLE_WRITE_LINE("----------------------");
        }
    }
}

int main()
{
    test();

    MY_PAUSE;
    return 0;
}
