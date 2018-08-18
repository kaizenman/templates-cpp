// Overloading Variadic and Nonvariadic templates

#include <iostream>
#include <string>



// if two function templates only differ by a trailing parameter pack,
// the function template without the trailing parameter pack is preffered
// Initially, in C++11 and C++14 this was an ambiguity, but then it was fixed
// in all compiler versions

// Operator sizeof...

// C++11 also introduced a new for of the sizeof opertor for variadic templates

// in general both branches of all if statements in function templates are instantiated.
// Whether the instantiated code is useful is a run-time decision
// while the instantiation of the call is a compile-time decision.
// For this reason, if you call the print() function template for one (last)
// argument, the statement with the call of print(args...) still is instantiated
// for no argument, and if there is no function print() for no arguments provided
// this is an error

// with C++17 you can use compile-time if (if constexpr)

template<typename T>
void print(T arg)
{
    std::cout << arg << '\n';
}

template<typename T, typename ... Types>
void print(T firstArg, Types... args)
{
    print(fistArg);
    if constexpr (sizeof...(args) > 0)
    {
        print(args...);
    }
}



int main()
{
    print("hi", "hello", "hi there");
}