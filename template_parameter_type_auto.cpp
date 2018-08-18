// Template Parameter Type auto

// Since C++17 you can define a nontype template parameter
// to generically accept any type that is allowed for a nontype parameter
// Even template<decltype(auto) N> is possible, which allows instantiation of N as
// a reference


#include <array>
#include <cassert>

template<typename T, auto MaxSize>
class Stack
{
public:
    using size_type = decltype(MaxSize);
private:
    std::array<T, MaxSize> elems;
    size_type numElems;
public:
    Stack();
    auto push(T const& elem);
    auto pop();
    T const& top() const;
    auto empty() const {
        return numElems == 0;
    }
    auto size() const {
        return numElems;
    }
};

template<typename T, auto MaxSize>
Stack<T, MaxSize>::Stack() : numElems(0)
{

}

template<typename T, auto MaxSize>
auto Stack<T, MaxSize>::push(T const& elem)
{
    assert(numElems < MaxSize);
    elems[numElems] = elem;
    ++numElems;
}

template<typename T, auto MaxSize>
auto Stack<T, MaxSize>::pop()
{
    assert(!elems.empty());
    --numElems;
}

template<typename T, auto MaxSize>
T const& Stack<T,MaxSize>::top() const
{
    assert(!elems.empty());
    return elems[numElems-1];
}

int main()
{

}