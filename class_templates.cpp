// Class templates

// By using class templates, you can implement container classes
//    while the element type is still open

// the type of this class is Stack<T>, with T being a template parameter
// Thus, you have to use Stack<T> whenever you use the type of this class
// in a declaration except in cases where the template arguments can be deduced
// However, inside a class template using a class name not followed by template
// arguments represents the class with its template parameters as its arguments

// unlike nontemplate classes, you can't declare or define class
// templates inside functions or block scope

// In general, templates can only be defined in global/namespace scope or inside
// class declarations

// To use an object of a class template, until C++17 you must always specify the
// template arguments explicitly

// By declaring type Stack<int>, int is used as type T inside the class template

// The code is instantiated only for template(member) functions that are called.
// For class templates, member functions are instantiated only if they are used.

// An instantiated class template's type can be used just like any other type.
// You can qualify it with const or volatile or derive array and reference
// types from it
// You can also use it as part of type definition with typedef or using

void foo(Stack<int> const & s)
{
    using IntStack = Stack<int>;
    Stack<int> istack[10];
    IntStack istack2[10];
}

#include <vector>
#include <cassert>

template<typename T>
class Stack
{
private: 
    std::vector<T> elems;
public:
    void push(T const & elem);
    void pop();
    T const& top() const;
    bool empty() const 
    {
        return elems.empty();
    }
    Stack(Stack const&);
    Stack& operator=(Stack const&);
};

template<typename T>
bool operator== (Stack<T> const& lhs, Stack<T> const& rhs)
{

}

template<typename T>
void Stack<T>::push(T const& elem)
{
    elems.push_back(elem);
}

template<typename T>
void Stack<T>::pop()
{
    assert(!elems.empty());
    elems.pop_back();
}

template<typename T>
T const& Stack<T>::top() const
{
    assert(!elems.empty());
    return elems.back();
}


// Friends -----------------------------------------------------------
template<typename T>
class Stack1
{
    friend std::ostream& operator<< (std::ostream& strm, Stack<T> const& s)
    {
        s.printOn(strm);
        return strm;
    }

};

template<typename T>
class Stack2 {
    template<typename U>
    friend std::ostream& operator<< (std::ostream&, Stack2<U> const&);
};

template<typename T>
class Stack3;
template<typename T>
std::ostream& operator<< (std::ostream&, Stack3<T> const&);


template<typename T>
class Stack3 {
    friend std::ostream& operator<< <T> (std::ostream&, Stack<T> const &);
};
//-----------------------------------------------------------------


// Specializations of Class Templates -----------------------------

// You can specialize a class template for certain template parameters.
// Similar to the overloading of function templates, specializing class templates
// allows you to optimize implementations for certain types or to fix a misbehavior of certain
// types for an instantiation of the class template

// However if you specialize a class template, you must also specialize all member functions
// To specialize a class template, you have to declare the class with a leading template<>
// and a specification of the types for which the class template is specialized.
// The types are used as a template argument and must be specified directly following the name
// of the class

template<>
class Stack<std::string> {

};

// Any definition of a member function must be defined as an "ordinary" member function,
// whith each occurence of T being replaced by the specialized type:

void Stack<std::string>::push(std::string const & elem)
{
    elems.push_back(elem);
}

// Partial Specialization ----------------------------------------

// You can provide special implementations for particular circumstances,
// but some template parameters must still be defined by the user
// For example, we can define a special implementation of class Stack<> for pointers

template<typename T>
class Stack<T*> {
private:
    std::vector<T*> elems;
public:
    void push(T*);
    T* pop();
    T* top() const;
    bool empty() const {
        return elems.empty();
    }
};

template<typename T>
void Stack<T*>::push(T* elem)
{
    elems.push_back(elem);
}

template<typename T>
void Stack<T*>::pop()
{
    assert(!elems.empty());
    T * p = elems.back();
    return p;
}

template<typename T>
T* Stack<T*>::top() const
{
    assert(!elems.empty());
    return elems.back();
}

// Note again that the specialization might provide a (slightly) different interface

// Partial specialization with Multiple Parameters

template<typename T1, typename T2>
class MyClass {
};

// partial specialization: both template parameters have same type
template<typename T>
class MyClass<T,T> {

};

// patial specialization: second type is int
template<typename T>
class MyClass<T, int> {

};

// partial specialization: both template parameters are pointer types
template<typename T1, typename T2>
class MyClass<T1*, T2*> {

};

// If more than one partial specialization matches equally well, the declaration is
// ambiguous
MyClass<int, int> m;
MyClass<int*, int*> m;

// To resolve the second ambiguity, you could provide an additional partial specialization
// for pointers of the same type:

template<typename T>
class MyClass<T*, T*> {

};




// Default class template arguments
// As for function templates, you can define default values for class template parameters
template<typename T, typename Cont = std::vector<T>>
class Stack {
private:
    Cont elems;
public:
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const {
        return elems.empty();
    }
};

template<typename T, typename Cont>
void Stack<T, Cont>::push(T const& elem)
{
    elems.push_back(elem);
}

template<typename T, typename Cont>
void Stack<T, Cont>::pop()
{
    assert(!elems.empty();
    elems.pop_back();
}

template<typename T, typename Cont>
T const& Stack<T,Cont>::top() const
{
    assert(!elems.empty());
    return elems.back();
}

// Note that we now have two template parameters, so each definition of a member function must
// be defined with these two parameters


// Type aliases

// 1. By using keyword typedef
typedef Stack<int> IntStack;
void foo(IntStack const& s);
IntStack istack[10];
// 2. By using the keyword using (C++11)
using IntStack = Stack<int>;
void foo(IntStack const& s);
IntStack istack[10];

template<typename T>
using DequeStack = Stack<T, std::deque<T>>;

// Alias template simply gives a new name to an existing type
// Note that, in general, templates can only be declared in global/namespace scope or inside class
//  declarations


// Alias templates for Member Types

template<typename T>
using Invoke = typename T::type;


// Class Template Argument Deduction

// Since C++17 you can skip to define the templates argument explicitly,
// if the constructor is able to deduce all template parameters

Stack<int> intStack1;               
Stack<int> intStack2 = intStack1;   // OK in all versions
Stack intstack3 = intStack1;        // OK since C++17


template<typename T>
class Stack {
private:
    std::vector<T> elems;
public:
    Stack() = default;
    Stack(T const& elem) : elems({elem}) {}
};

int main()
{
    Stack intStack = 0;
}