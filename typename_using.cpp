#include <iostream>
#include <type_traits>

template<typename T>
struct Container 
{ 
public:
    virtual void f() {}
    using value_type = T; 
};
template<typename Container>
void g(const Container& c) { typename Container::value_type n;}


template<typename T>
using Invoke = typename T::type;

template<typename Condition>
using EnableIf = Invoke<std::enable_if<Condition::value>>;

//template<typename T, typename = EnableIf<std::is_polymorphic<T>>>
template<typename T,
		   typename EnableIf<std::is_polymorphic_v<T>>
         //typename EnableIfPoly = typename std::enable_if_t<std::is_polymorphic_v<T>>>
int fpoly_only(T t)
{
    return 1;
}

int main()
{
    Container<int> c;
    g(c);

    // should be polymorphic
    fpoly_only(c);
}