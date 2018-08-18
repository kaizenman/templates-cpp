// SFINAE (sfee-nay)

// Substitution failure is not an error

// When a compiler sees a call to an overloaded function, it must therefore
// consider each candidate separately, evaluating the arguments of the call
// and picking the candidate that matches best.
// In cases where the set of candidates for a call includes function templates,
// the compiler has to determine what template arguments should be used for that
// candidate, then substitute those arguments in the function parameter list and its
// return type, and then evaluate how well it matches.
// This process could produce constructs that make no sense, so

// Rather than deciding that such meaningless substitutions lead to errors, 
// the language rules instead say that candidates with such substituation problems are simply
// ignored 

// Substitution of the constructs appearing directly in the declaration of the function
// (but not its body)

template<typename T, unsigned N>
std::size_t len(T(&)[N])
{
	return N;
}

template<typename T>
typename T::size_type len(T const& t)
{
	return t.size();
}

template<typename T>
auto len(T const& T) -> decltype((void)(t.size()), T::size_type())
{
	return t.size();
}