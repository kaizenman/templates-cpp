
// Passing by value

// Before C++17 a compiler that doesn't optimze the copying away,
// must at least have to try to use move semantics

// Since C++17, the copying optimization is required

// Passing by value decays
// - raw arrays get converted to pointers
// - and qualifiers such as const and volatile are removed


// Passing by reference

// - No copy get's created
// - Passing the argument never decays
// - Sometimes passing is not possible


// Passing by constant reference

// - avoid any (unnecessary) copying when
//   passing nontemporary objects

// Under the hood, passing an argument by reference is implemented
// by passing the address of the argument. Addresses are encoded
// compactly, and therefore passing an address
// can create uncertainties for the compiler when it compiles the caller's code
// Compile has to assume that all the values it may have cached are invalid after
// the call

// If the compiler can expand the call inline, in many cases it can see that address
// is not used for anything but passing the underlying value.



// Passing by reference does not decay
// However, because the call parameter is declared as T const&, the template parameter T
// itself is not deduced as const

template<typename T>
void printR(T const& arg) {}

std::string const c = "hi";
printR(c); 					// printR<std::string>(std::string const&)
printR("hi");				// printR<char[3]>(char const(&)[3]);

int arr[4];
printR(arr);				// print<int[4]>(int const (&)[4])
// Thus, local objects declared with the type T in printR() are not constant




// Passing by Nonconstant Reference
// - if you want to return values through passed arguments (out/inout parameters)
// - no copy gets created
std::string returnString();
std::string s = "hi";
outR(s);					// outR<std::string>(std::string&)
outR(std::string("hi"));	// ERROR: not allowed to pass a temporary (prvalue)
outR(returnString());		// ERROR: not alloved to pass a temporary (prvalue)
outR(std::move(s));			// ERROR: not allowed to pass an xvalue

// If you pass a const argument, the deduction might result in arg becoming
// a declaration of a constant reference, which means that passing an rvalue is
// suddenly allowed, where an lvalue is expected

std::string const c = "hi";
outR(c);

// in such cases any attempt to modify the passed argument inside the function template
// is an error

// if you want to disable passing constant objects to nonconstant references

// - use a static assertion to trigger a compile-time error
template<typename T>
void outR(T& arg) {
	static_assert(!std::is_const<T>::value, "out parameter of foo<T>(T&) is const");
}
// - disable the template for this case either by using std::enable_if<> or concepts
template<typename T, typename = std::enable_if_t<!std::is_const<T>::value>
void outR(T& arg) {	}

// One reason to use call-by reference is to be able to perfect forward a parameter


// when a template is declared to take arguments by value, the caller can use
// - std::cref()
// - std::ref()
// to pass the argument by reference

// it wraps an argument by an object that acts like a reference
// The wrapper more or less supports only one operation: an implicit type conversion
// back to the original type, yielding the original object

// Effect of class std::reference_wrapper<> is to be able to use a reference as a
// "first class object", which you can copy and therefore pass by value to 
// function templates