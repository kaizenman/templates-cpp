#include <iostream>
#include <string>
#include <vector>


template<typename T>
void print(T param)
{
	std::cout << param << '\n';
}

template<typename T, typename ... Types>
void print(T first, Types const &... args)
{
	std::cout << first << '\n';
	if constexpr (sizeof...(Types) ==  0)
	{
		return;
	}
	else
	{
		print(args...);
	}
}

template<typename ... T>
void doublePrint(T const& ... args)
{
	print(args + args ... );
}

template<typename ... T>
void addOne(T const&... args)
{
	print((args + 1 )...);
}

// variadic indices
template<typename C, typename ... Idx>
void printElems(C const& coll, Idx... idx)
{
	print(coll[idx]...);
}




int main()
{
	std::string s1 = "hello";
	std::string s2 = "hi";
	std::string s3 = "hi threre";

	addOne(10, false, 16.3, -10, 3);

	std::vector<std::string> coll = {"good", "times", "say", "bye"};
	printElems(coll, 2, 0, 3);
}
