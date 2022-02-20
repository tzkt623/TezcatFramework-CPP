#include "IDString.h"
#include <iostream>

struct Uniform1 {};
struct Uniform2 {};

using MyUniform1 = IDString<Uniform1>;
using MyUniform2 = IDString<Uniform2>;


int main()
{
	MyUniform1::UMap<int> map;

	MyUniform1 str1("uniform");
	MyUniform1 str2("vec3");
	std::cout << (str1 == str2) << std::endl;
	std::cout << str1 << std::endl;
	std::cout << str2 << std::endl;

 	map.try_emplace("uniform", 1);
 	map.try_emplace("sampler2D", 2);
 	map.try_emplace(str1, 3);
 	map.try_emplace(str2, 4);


	std::cout << map.size() << std::endl;
	std::cout << (map.find("uniform") != map.end()) << std::endl;
	std::cout << map[str1] << std::endl;


	{
		str2 = "hahaha";
	}
	std::cout << str2 << std::endl;

	{
		str1 = std::string("ooooooo");
	}
	std::cout << str1 << std::endl;

	MyUniform2 str21("vec4");
	MyUniform2 str22("vec3");

	system("pause");

	return 0;
}