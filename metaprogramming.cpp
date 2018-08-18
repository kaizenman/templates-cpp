// p: number to check, d: current divisor
template<unsigned p, unsigned d>
struct DoIsPrime {
	static constexpr bool value = (p%d != 0) && DoIsPrime<p, d-1>::value;
};

// end recusion if divisor is 2
template<unsigned p>
struct DoIsPrime<p,2> {
	static constexpr bool value = (p % 2 != 0);
};

// primary template
// start recursion with divisor from p / 2
template<unsigned p>
struct IsPrime {
	static constexpr bool value = DoIsPrime<p, p/2>::value;
};

// to avoid endless recursion with template instantiation
template<>
struct IsPrime<0> { static constexpr bool value = false; };

template<>
struct IsPrime<1> { static constexpr bool value = false; };

template<>
struct IsPrime<2> { static constexpr bool value = true; };

template<>
struct IsPrime<3> { static constexpr bool value = true; };


// IsPrime<9>;:value

// expands to DoIsPrime<9, 4>::value
// expands to 9%4 != 0 && DoIsPrime<9,3>::value
// expands to 9%4 != 0 && 9%3 != 0 && DoIsPrime<9,2>::value
// expands to 9%4 != 0 && 9%3 != 0 && 9%2 != 0  

// 9%3 != 0 (false), 