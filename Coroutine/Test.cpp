#include "Test.h"


template<typename T>
struct MyCoroutine
{
	struct MyAwaitable;
	struct MyPromise
	{
		T value;

		std::suspend_always initial_suspend()
		{
			std::cout << "initial_suspend" << std::endl;
			return {};
		}
		std::suspend_never final_suspend() noexcept
		{
			std::cout << "final_suspend" << std::endl;
			return {};
		}

		void return_void()
		{
			std::cout << "return_void" << std::endl;
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
			std::cout << "yield_value" << std::endl;
			this->value = value;
			return { this };
		}

		MyCoroutine get_return_object()
		{
			std::cout << "get_return_object" << std::endl;
			return { std::coroutine_handle<MyPromise>::from_promise(*this) };
		}
	};
	using promise_type = MyPromise;

	struct MyAwaitable
	{
		promise_type* promise;

		constexpr bool await_ready() const noexcept
		{
			std::cout << "await_ready" << std::endl;
			return false;
		}

		constexpr void await_suspend(std::coroutine_handle<> handle) const noexcept
		{
			std::cout << "await_suspend" << std::endl;
		}

		T await_resume() const noexcept
		{
			std::cout << "await_resume" << std::endl;
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
	std::cout << "----------------------" << std::endl;

	for (int i = 0; i < 6; i++)
	{
		if (cor2.next())
		{
			std::cout << cor2.getValue() << std::endl;
			std::cout << "----------------------" << std::endl;
		}
	}
}

int main()
{
	test();

	system("pause");
	return 0;
}