// Execution Path Selection with Partial Specialization

template<int sz, bool = isPrime(sz)>
struct Helper;

template<int sz>
struct Helper<sz, false>
{

};

template<int sz>
struct Helper<sz, true>
{

};

template<typename T, std::size_t sz>
long foo(std::array<T, sz> const& coll)
{
	Helper<sz> h;
}