// Class templates Arguments Deduction with String Literals
#include <vector>
#include <iostream>
#include <string>
#include <string_view>

// By providing construtors that pass some initial arguments
// you can support deduction of the element type of a stack

// Note that, unlike for function templates,
// class template arguments may not be deduced only partially


// In general, when passing arguments of a template type T 
// by reference, the parameter doesn't decay

// Instead of declaring the constructor to be called by value
// You can define specific deduction guides
// A deduction guide is not a function and does not have a body




template<typename T>
class Stack {
private:
    std::vector<T> elems;
public:
    Stack() = default;
    Stack(const T& elem) : elems({elem})
    {
        std::cout << "Copy constructor called \n";
    }

};
// whenever a string literal or C string is passed,
// the Stack is instantiated for std::string
Stack(const char*) -> Stack<std::string>;


int main()
{
    // T deduced as const char[6] if we not define deduction guides
    Stack stringStack = {"hello"};
    
    // call copy constructor and declare the same type
    Stack stack2{stringStack}; // Stack<std::string> deduced
    Stack stack3(stringStack); // Stack<std::string> deduced
    Stack stack4 = {stringStack}; // Stack<std::string> deduced
}