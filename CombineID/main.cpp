#include <stdint.h>
#include <iostream>


class MyClass
{
public:
	MyClass():
		mID(0)
	{}

	union
	{
		uint64_t mID;

		struct Type1
		{
			uint64_t id0_7 : 8;
			uint64_t id8_15 : 8;
			uint64_t id16_31 : 16;
			uint64_t id32_47 : 16;
			uint64_t id48_63 : 16;
		} mCombineID;
	};
};




int main()
{
	MyClass my;
	my.mCombineID.id0_7 = 1;
	my.mCombineID.id48_63 = 0;

	std::cout << my.mCombineID.id0_7 << std::endl;
	std::cout << my.mCombineID.id8_15 << std::endl;
	std::cout << my.mCombineID.id16_31 << std::endl;
	std::cout << my.mCombineID.id32_47 << std::endl;
	std::cout << my.mCombineID.id48_63 << std::endl;

	std::cout << my.mID << std::endl;

	std::cout << std::endl;

	my.mCombineID.id0_7 = 0;
	my.mCombineID.id48_63 = 1;

	std::cout << my.mCombineID.id0_7 << std::endl;
	std::cout << my.mCombineID.id8_15 << std::endl;
	std::cout << my.mCombineID.id16_31 << std::endl;
	std::cout << my.mCombineID.id32_47 << std::endl;
	std::cout << my.mCombineID.id48_63 << std::endl;

	std::cout << my.mID << std::endl;

	return 0;
}