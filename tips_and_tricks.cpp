// TIPS and TRICKS

// 1. Typename has to be used whenever a name that depends on a template parameter
// 	is a type

#include <iostream>
#include <vector>

template<typename T>
void printcoll (T const& coll)
{
	typename T::const_iterator pos;
	typename T::const_iterator end(coll.end());
	for (pos = coll.begin(); pos != end; ++pos) {
		std::cout << *pos << ' ';
	}
	std::cout << '\n';
}

int main()
{
	std::vector<int> v = {1, 2, 3, 4, 5};
	printcoll(v);
}

// 2. Zero initialization

// For fundamental types there is no default constructor that initializes
// them with a useful default value;

// It is possible to call explicitly a default constructor for build-in types
// that initializes them with zero

// Default arguments cannot use that syntax

template<typename T>
void foo()
{
	T x{};
}

template<typename T>
void foo(T p{}) {}	// ERROR

template<typename T>
void foo(T p = T{}) {} // OK


// 3. Using this->
// Always qualify any symbol that is declared in Base<T>::
//	using a name x not always equivalent to this->x,
//  even though a member x is inherited 
// To access members of bases classes that depend on template parameters,
// you have to qualify the access by this-> on their class name.



// Template versions of constructors or assignment operators don't replace
// predefined constructors or assignment operators




// 4. Templates for Raw Arrays and String Literals
// If the template parameters are declared as references
// the arguments doen't decay
// "hello" has type char const [6]
// Only when passing the argument by value, the types decay
// so "hello" -> char const *

template<typename T, int N, int M>
bool less (T (&)[N], T(&b)[M])
{
	for(int i = 0; i < N && i < M; ++i)
	{
		if (a[i] < b[i]) return true;
		if (b[i] < a[i]) return false;
		return N < M;
	}
}


int x[] = {1, 2, 3};
int y[] = {1, 2, 3, 4, 5};
std::cout << less(x,y) << '\n';


// if you want to provide a function template for string literals:
template<int N, int M>
bool less (const char (&)[N], const char(&b)[M])
{
	for(int i = 0; i < N && i < M; ++i)
	{
		if (a[i] < b[i]) return true;
		if (b[i] < a[i]) return false;
		return N < M;
	}
}

// Sometimes you have to overload or partially specialize for arrays of unknown bounds

template<typename T>
struct MyClass;

template<typename T, std::size_t SZ>
struct MyClass<T[SZ]>				// partial specialization for arrays of known bounds
{

};


template<typename T, std::size_t SZ>
struct MyClass<T(&)[SZ]>			// partial specialization for references to arrays
									// of known bounds
{};

template<typename T>
struct MyClass<T[]>					// partial specialization for arrays of unknown bounds
{};

template<typename T>
struct MyClass<T(&)[]>				// partial specialization for references to arrays
									// of known bounds
{};

template<typename T>
struct MyClass<T*>					// partial specialization for pointers
{};


// 5. Member templatess
// By defining an assignment operator as a template you can enable
// the assignment of stacks with elements for which an appropriate type conversion
// is defined

template<typename T>
class Stack {
private:
	std::deque<T> elems;

public:
	void push(T const&);
	void pop();
	T const& top() const;
	bool empty() const {
		return elems.empty();
	}

	template<typename T2>
	Stack& operator= (Stack<T2> const&);
	// to get access to private members of Stack<T2> for any type T2;
	template<typename> friend class Stack;
};

template<typename T>
template<typename T2>
Stack<T>& Stack<T>::operator= (Stack<T2> const& op2)
{
	elems.clear();
	elems.insert(elems.begin(), op2.elems.begin(), op2.elems.end());
	return *this;
}

// 6. The .template Construct
// Sometimes, it is necessary to explicitly qualify template arguments
// when calling a member template
// In that case, you have to use the template keyword to ensure that 
// a < is the beginning of the template argument list.

// to_string() is a member function template for the bitset
// Withouth that extra use of .template, the compiler does not known
// that the less-than token (<) that follows is not really less-than
// but the beginning of a template argument list.
// This is a problem only if the construct period depends on a template
// parameter.
// bs depends on the template parameter N
// The .template notation and ->template and ::template
// should be used only inside templates only if the follow something
// that depends on a template parameter
template<unsigned long N>
void printBitset(std::bitset<N> const& bs) {
	std::cout << bs.template to_string<char, std::char_traits<char>, std::allocator<char>>()>;
}


// 7. Generic Lambdas and Member Templates
// Generic lambdas are shortcuts for member templates

// 8. Variable Templates
template<typename T>
constexpr T pi {3.141592};

// The following code uses two different variables of the scope where pi<>
// is declared
// You always have to specify the angle brackets
std::cout << pi<double>;
std::cout << pi<float>;

// Variable templates can be parameterezied by nontype parameters
template<int N>
std::array<int, N> arr {};	// array with N elements, zero-initialized
template<auto N>
constexpr decltype(N) dval = N; // type of dval depends on passed value

std::cout << dval<'c'>;			// N has value 'c'
arr<10>[0] = 42;				// sets first
for(std::size_t i = 0; i < arr<10>.size(); ++i) {
	std::cout << arr<10>[i];	// uses values set in arr
}

// 9. Variable templates for Data members

template<typename T>
class Mylass {
public:
	static constexpr int max = 10000;
};
// allows you to define different values for different specializations of 
// MyClass<>
template<typename T>
int myMax = MyClass<T>::max;

// so instead of
auto i = MyClass<std::string>::max;
// you can write
auto i = myMax<std::string>;

// instead of
std::numeric_limits<char>::is_signed
// write
isSigned<char>


// 10. Type Traits Suffic_v

// instead of
std::is_const<T>::value
// write
std::is_const_v<T>


// 11. Template template parameers
// Allow a template parameter itself to be a class template

Stack<int, std::vector<int>> vStack; // integer stack that uses a vector


// the difference is the second template parameter is declared as being a 
// class template
// the default value has changed from std::deque<T> to std::deque
template<typename T, template<typename Elem> class Cont = std::deque>
class Stack {
private:
	Cont<T> elems;
public:
	void push(T const&);
	void pop();
	...
};

// with C++17 you can write
template<typename T, template<typename Elem> typename Cont = std::deque>
// because tye template paramter of the template template parameter is not used
template<typename T, template<typename> typename Cont = std::deque>
// Member functions must be modified accordingly

template<typename T, template<typename> typename Cont>
void Stack<T, Cont>::push(T const& elem)
{
	elems.push_back(elem);
}

// Template template argument matching
