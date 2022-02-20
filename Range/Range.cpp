#include "Range.h"
#include <regex>

void regexTest()
{
	std::string hello("Hello world TINY_END_HEAD hahaha ; test split");

	std::regex ws_re("TINY_END_HEAD|;");
	std::vector<std::string> v(std::sregex_token_iterator(hello.begin(), hello.end(), ws_re, 1), std::sregex_token_iterator());
	for (auto&& s: v)
	{
		std::cout << s << std::endl;
	}
}

int main()
{
	regexTest();


	std::string hello("Hello world test split");
	auto sv = hello
		| std::ranges::views::split(" ");

	system("pause");

	return 0;
}