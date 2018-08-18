#include <iostream>

template<typename T>
void print(T param)
{
	std::cout << param << " ";
}

template<typename T, typename ... Types>
void print(T first, Types ... args)
{
	print(first);
	print(args...);
}



int main()
{
	print("hello", "hi", "hi there");
}
