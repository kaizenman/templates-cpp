// Nontype Template Parameters

// For function and class templates, template parameters don't have to be types
// They also can be ordinary values

// Example:
// You can implement a stack by using a fixed_size array for the elements


// Nontype template parameters carry some restrictions
//  - they can only be constant integral values (including enumerations)
//      pointers to objects/functions/members,
//      lvalue references to objects or functions
//      or std::nullptr_t(the type of nullptr)
//  - floating-point numbers and class-type objects are not allowed
//      as nontype template paramters
//  - when passing template arguments to pointers or references, the objects
//      must not be string literals, temporaries, or data members and other subobjects
// with each and every C++ version before C++17 these restictions were relaxed
//  - in C++11, the objeccts also had to have external linkage
//  - in C++14, the objects also had to have external or internal linkage

// Arguments for nontype template parameters might be any compile-time expressions



#include <array>
#include <cassert>
#include <iostream>
#include <string>


template<int I, bool B>
class C;

C<sizeof(int) + 4, sizeof(int)==4> c;




template<typename T, std::size_t MaxSize>
class Stack {
private:
    std::array<T, MaxSize> elems;
    std::size_t numElems;
public:
    Stack();
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const {
        return numElements == 0;
    }
    std::size_t size() const {
        return numElems;
    }
};

template<typename T, std::size_t MaxSize>
Stack<T, MaxSize>::Stack() : numElems(0)
{

}

template<typename T, std::size_t MaxSize>
void Stack<T, MaxSize>::push(T const& elem)
{
    assert(numElems < MaxSize);
    elems[numElems] = elem;
    ++numElems;
}

template<typename T, std::size_t MaxSize>
void Stack<T, MaxSize>::pop()
{
    assert(!elems.empty());
    --numElems;
}

template<typename T, std::size_t MaxSize>
T const& Stack<T,MaxSize>::top() const
{
    assert(!elems.empty());
    return elems[numElems-1];
}




template<const char* name>
class MyClass
{

};

extern char const s03[] = "hi";
char const s11[] = "hi";



int main()
{
    Stack<int, 20> int20Stack;
    Stack<int, 40> int40Stack;
    Stack<std::string, 40> stringStack;

    int20Stack.push(7);
    std::cout << int20Stack.top() << '\n';
    int20Stack.pop();

    stringStack.push("hello");
    std::cout << stringStack.top() << '\n';
    stringStack.pop();

   
    MyClass<s03> m03;


}