
// std::enable_if
// is a metafunction used as 
// - an additional function argument (not applicable to operator overloads)
// - a return type (not applicable to constructors and destructors)
// - a class template or a function template parameter

// std::enable_if is a convenient way to to use the maximum advantage of
// SFINAE to conditionally remove functions from overload resolution
// based on type traits and to provide separate function overloads
// and specializations for different type traits

// SFINAE - "Substitution Failure Is Not An Error"


// It is illegal to declare two function templates that differ only in their
// default template arguments
// because default template arguments are not part of function templete's signature

#include <type_traits>

template<typename T> typename std::enable_if<(sizeof(T) > 4)>::type
foo() {}

// if Condition is true, std::enable_if has a public member typedef type
// equal to T which is void by default if not defined the second template argument
// , otherwise, there is no member typedef


// the definition of foo<>() is ignored if sizeof(T) > 4 yields false
// If sizeof(T) > 4 yields true, the function template instance expands
// to void foo() {}


template<typename T>
std::enable_if_t<(sizeof(T) > 4)> foo
{

}

// if a second argument is passed to enable_if<> or enable_if_t<>
template<typename T>
std::enable_if_t<(sizeof(T) > 4), T> foo()
{
	return T();
}

// having the enable_if expression in the middle of a declaration is pretty clumsy
// For this reason, the common way to use std::enable_if<> is to use an
// additional function template argument with a default value:

template<typename T> typename std::enable_if<(sizeof(T) > 4)>::type
foo() {}


template<typename T, typename = std::enable_if_t<(sizeof(T) > 4)>>
void foo() {

}

template<typename = std::enable_if_t<(sizeof(size_t) == 8)>>
void foo64()
{
}

int main()
{
	 foo64();
}

// We can use enable_if<> to solve problem with the constructor template
template<typename T>
using EnableIfString = std::enable_if<std::is_convertible_v<T, std::string>>;

template<typename STR,
		 typename = EnbaleIfString<STR>>
Person(STR&& n);

// We can disable special member functions
// Normally we can't use enable_if<> to disable the predefined copy/move
// constructors and/or assignment operators
// Because member function templates never count as special member functions
// and are ignored when, for example, a copy constructor is needed

class C {
public:
	template<typename T>
	C(T const&) {
		std::cout << "tmpl copy constructor\n";
	}
};

// the predefined copy constructor is still used, when a copy is requested
C x;
C y{x};	// still uses the predefined copy constructor (not the member template)

// Deleting the predefined copy constructor is no solution, because
// then the trial to copy a C results in an error

// But we can declare a copy constructor for const volatile arguments
// and mark it "deleted". Doing so prevents another copy constructor
// from being implicitly declared.
// So we can define a constructor template that will be preferred over the (deleted)
// copy constructor for nonvolatile types

// We also can prevent to copy objects of class template C<>
// if the template parameter is an integral type
class C
{
public:
	C(C const volatile&) = delete;
	template<typename T>
	
	template<typename U, typename = std::enable_if_t<!std::is_integral<U>::value>>
	C(C<U> const&) {
		
	}
};

// Now the template constructors are used even for "normal" copying
C x;
C y{x};

