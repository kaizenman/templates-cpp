// Templatized Aggregates

// Aggregate classes
//      classes/structs with
//      - no user-provided, explicity, or inherited constructors
//      - no private or protected nonstatic data members,
//      - no virtual functions
//      - no virtual, private, or protected base classes

// Since C++17, you can even define deduction guides for aggregate class
// template

// Btw, std::array<> is also an aggregate, parameterized for both the element type
//  and the size

#include <string>

template<typename T>
struct ValueWithComment {
    T value;
    std::string comment;
};
// deduction guide for aggregate class template
ValueWithComment(char const*, char const*) -> ValueWithComment<std::string>;

int main()
{
    ValueWithComment<int> vc;
    vc.value = 42;
    vc.comment = "initial value";

    ValueWithComment vc2 = {"hello", "initial value"};
}