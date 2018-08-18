// Variadic Class Templates

// Examples:
//		Tuple
//		Variant
//		...

// You can define a class that as a type represents a list of indicies
// Even deduction guides can be variadic

#include <vector>
#include <string>
#include <array>

template<typename T>
class Stack
{
public:
	Stack() = default;
	Stack(const T & elem) : elems({elem}) {} 
private:
	std::vector<T> elems;
};
// deduction guide
// deduce const char * to std::string
Stack(const char *) -> Stack<std::string>;



// Variadic deduction guides

template <typename T, size_t Size>
class Array
{

};

// Deduce 
template<typename T, typename ... Args>
Array(T, Args...) -> Array<T, 1 + sizeof...(Args)>
{

}


// Variadic Base Classes





int main()
{
	std::array
	Stack intStack = 0;
	Stack cstringStack = {"hello"};
}