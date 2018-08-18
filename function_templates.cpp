// Function templates

//  Provide a functional behavior that can be called for different types
//      The representation looks a lot like an ordinary function,
//      except that some elements of the function are left undetermined:
//      These elements are parameterized

// type of these parameters is left open as template parameter T

//  Templates aren't compiled into single entities that can handle any type.
//  Instead, different entities are generated from the template for every type
//  for which the template is used.

//  The process of replacing template parameters by concrete types is called instantiation
//  It results in an instance of a template

//  An attempt to instantiate a template for a type that doesn't support all the operations
//  used within it will result in a compile-time error

//  Templates are "compiled" in two phases:
//      1. Without instantiation at definition time, the template code itself is checked for
//          correctness ignoring the template parameters. This includes:
//          - syntax errors are discovered, such as missing semicolons.
//          - using unkown names (type names, function names, ...) that don't depend on
//            template parameters are discovered
//          - static assertions that don't depend on template parameters are checked
//      2. At instantiation time, the template code is checked (again) to ensure that all
//          code is valid


template<typename T>
T max( T a, T b )
{
    return b < a ? a : b;
}


// names are checked twice is called two-phase lookup
template<typename T>
void foo(T t)
{
    undeclared(); // first-phase compile-time error if undeclared() unknown
    undeclared(t); // second-phase compile-time error if undeclared(T) unknown
    static_assert(sizeof(int) > 10, "int too small"); // always fails if sizeof(int) <= 10
    static_assert(sizeof(T) > 10, "T too small"); // fails if instantiated for T with size <= 10;
}


// When declaring call parameters by reference, even trivial conversions do not apply
//  to type deduction. Two argumetns declared with the same template parameter T must match exactly
// When declaring call parameters by value, only trivial conversions that decay are supported.
//  Qualifications with const or volatile are ignored, references convert to the referenced type,
//  and raw arrays or functions convert to the corresponding pointer type.
//  For two arguments declared with the same template parameter T the decayed types must match

// Type deduction does not work for default call arguments
template<typename T>
void f(T = "");

f<int>(1); // OK: deduced T to be int, so that it calls f<int>
f();; // ERROR: cannot deduce T

// To support this case, you also have to declare a default argument for the template
template<typename T = std::string>
void f2(T = "");

f2(); // OK



// Function templates have distinct two parameters:
//  - template parameters, which are declared in angle brackets before the function template name
template<typename T>
//  - call parameters, which are declared in parentheses after the function template name:
T max2(T a, T b);


// Template parameters for return types
//  In cases when there is no connection between template and call parameters and
//  when template parameters cannot be determinded, you must specify the template argument
//  explicitly with the call
template<typename T1, typename T2, typename RT>
RT max(T1 a, T2 b);
// Template argument deduction does not take return types into account, and RT does not appear
// in the types of the function call parameters. Therefore, RT cannot be deduced.
// As a consequence, you have to specify the template argument list explicitly
template<typename T1, typename T2, typename RT>
RT max(T1 a, T2 b);
::max<int, double, double>(4, 7.2);
// Another approach is to specify only the first arguments explicitly and to allow the 
//  deduction process to derive the rest. In general, you must specify all the argument
//  types up to the last argument type that cannot be determined implicitly
// Thus, if you change the order of the template parameters, the caller needs to specify only
//  the return type
template<typename RT, typename T1, typename T2>
RT max(T1 a, T2 b)
::max<double>(4, 7.2);        // OK: return type is double, T1 and T2 are deduced


// If a return type depends on template parameters, the simplest and best approach to
// deduce the return type is to let the compiler find out.
// This is possible by simply not declaring any return type
template<typename T1, typename T2>
auto max(T1 a, T2 b)
{
    return b < a ? a : b;
}
// In fact, the use of auto for the return type without a corresponding trailing return type
// indicates that the actual return type must be deduced from the return statements in the function
// body
// The code must be available and multiple return statements have to match

// Here the resulting type is determined by the rules for operator ?: which are fairly elaborate
// but generally produce an intuitively expected result
template<typename T1, typename T2>
auto max(T1 a, T2 b) -> decltype(b < a ? a : b)
{
    return b < a ? a : b;
}

// It is a declaration, so that the compiler uses the rules of operator ?: called for parameters
// a and b to find out the rturn type of max() at compile time.
// In fact, ussing true as the condition for operator ?: in the declaration is enough
template<typename T1, typename T2>
auto max(T1 a, T2 b) -> decltype(true ? a : b);
// However, in any cace this definition has a significant drawback: It might happen that the 
//  return type is a reference type, because under some conditions T might be a reference.
//  For this reason you should return the type decayed from T
#include <type_traits>
template<typename T1, typename T2>
auto max(T1 a, T2 b) -> typename std::decay<decltype(true? a : b)>::type
{
    return b < a ? a : b;
}
// Because the member type is a type, you have to qualify the expression with typename to access it
// Note that an initialization of type auto always decays.
//  This also applies to return values when the return type is just auto.


// Since C++11, the C++ standard library provides a means to specify choosing "the more general type"
// std::common_type<>::type yields the "common type" of two (or more) different types passed as template
// arguments
template<typename T1, typename T2>
std::common_type_t<T1,T2> max(T1 a, T2 b)
{
    return b < a ? a : b;
}


// Default template arguments
// These values are called default template arguments and can be used with any kind of template
// They may even refer to previous template parameters

// 1. We can use opertor?: directly. However, because we have to apply operator?:
//   before the call parameters a and b are declared, we can only use their types
//   This version requeres that we are able to call default constructors for the passed types
template<typename T1, typename T2, typename RT = std::decay_t<decltype(true ? T1() : T2())>>
RT max(T1 a, T2 b)
{
    return b < a ? a : b;
}
// 2. We can also use std::common_type<> type trait to specify the default value for the return type:
template<typename T1, typename T2, typename RT = std::common_type_t<T1,T2>
RT max(T1 a, T2 b)
{
    return b < a ? a : b;
}

// In all cases, as a caller, you can now use the default value for the return type
auto a = ::max(4,7.2);
// or to specify the return type after all other argument types explicitly:
auto b = ::max<double, int, long double>(7.2, 4);


// Like ordinary functions, function templates can be overloaded.
int max(int a, int b)
{
    return b < a ? a : b;
}

template<typename T>
T max(T a, T b)
{
    return b < a ? a : b;
}

int main()
{
    ::max(7,42);            // nontemplate for two ints
    ::max(7.0, 42.0);       // max<double> (by argument deduction)
    ::max('a', 'b');        // max<char> (by argument deduction)
    ::max<>(7, 42);         // max<int> (by argument deduction)
    ::max<double>(7, 42);   // max<double> (no argument deduction)
    ::max('a', 42.7);       // nontemplate for two ints
}


// In general, passing by reference is recommended for types other than cheap simple types
// (such as fundamental types or std::string_view), because no unnecessary copies are created
// However, for a couple of reasons, passing by value in general is often better
//  - the syntax is simple
//  - compilers optimize better
//  - move semantics often makes copies cheap
//  - and sometimes there is no copy or move at all

// A template might be used for both simple and complex types, so choosing the
//  approach for complex types might be counter-productive for simple types
// As a caller you can often still decide to pass arguments by reference, using
//  std::ref() and std::cref()
// Although passing string literals or raw arrays always can become a problem, passing
// them by reference often is considered to become the bigger problem.


template<typename T1, typename T2>
constexpr auto max(T1 a, T2 b)
{
    return b < a ? a : b;
}

#include <iostream>
#include <string>

int main()
{
    int i = 42;
    std::cout << "max(7,i): " << ::max(7,i) << '\n';

    double f1 = 3.4;
    double f2 = -6.7;
    std::cout << "max(f1,f2): " << ::max(f1,f2) << '\n';

    std::string s1 = "mathematics";
    std::string s2 = "math";
    std::cout << "max(s1,s2): " << ::max(s1,s2) << '\n';
}