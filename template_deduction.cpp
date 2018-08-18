#include <vector>
#include <iostream>


// By providing construtors that pass some initial arguments
// you can support deduction of the element type of a stack

// Note that, unlike for function templates,
// class template arguments may not be deduced only partially
template<typename T>
class Stack {
private:
    std::vector<T> elems;
public:
    Stack() = default;
    // int will be number of elements to create, so we need 
    // to create temporary vector<int> object {elem} 
    Stack(T const& elem) : elems({elem}) 
    {
        std::cout << "Copy constructor called";
    }
};

int main()
{
    Stack intStack = 0;
}