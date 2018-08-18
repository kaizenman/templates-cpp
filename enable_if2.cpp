#include <type_traits>
#include <deque>
#include <iostream>

template<typename = std::enable_if_t<(sizeof(size_t) == 8)>>
void foo64()
{
}

int main()
{
	 foo64();
}