// Variadic templates

// Templates can have parameters that accept a variable number
// of template arguments

// When you have to pass an arbitrary number of arguments of arbitrary
// types

// Example:
// 1. Pass an arbitrary number of parameters of arbitrary type through a
//  class or framework.
// 2. Application is to provide generic code to process any number of parameters
//  of any type

// Template parameters can be defined to accept an unbounded number of template arguments

#include <iostream>
#include <string>


// Nontemplate overload of print() is provided to end the recursion
// which is issued when the parameter pack is empty
void print()
{

}

// args are a function parameter pack
// template parameter pack: typename... Types
template<typename T, typename... Types>
void print(T firstArg, Types... args)
{
    std::cout << firstArg << '\n';
    print(args...); // call print() for remaining arguments
}

int main()
{
    std::string s("world");
    print(7.5, "hello", s);
}

// the first call expands to 
// print<double, char const*, std::string>(7.5, "hello", s);
// firstArg having the value 7.5, so that T is double
// and args being a variadic template argument having the values "hello"
// of type const char* and "world" of type std::string

// After that, it calls print() again for remaining arguments
// print<char const*, std::string>("hello", s)
// with firstArg having the value "hello" so that type T is a char const*
// and args being a variadic template argument having the value of type
// std::string

// After that, it calls print() again for the remaining arguments
// print<std::string>(s)
// with firstArg having the value "world" so that T is a std::string
// and args being an empty variadic template argument having no value

// Then print() is called with no arguments, which results in calling the
// nontemplate overload of print() doing nothing