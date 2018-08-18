// Fold expressions

// Since C++17, there is a feature to compute the result of using a binary operator
// over all the argument of a parameter pack

// binary operators:
//  ,        Comma
//  !=       Inequality
//  %        Modulus
//  %=       Modulus/assignment
//  &        Bitwise AND
//  &&       Logical AND
//  &=       Bitwise AND/assignment
//  *        Multiplication
//  *=       Multiplication/assignment
//  +        Addition
//  +=       Addition/assignment
//  -        Subtraction
//  -=       Subtraction/assignment
//  ->       Member selection   
//  .*       Pointer-to-member selection 
//  ->*      Pointer-to-member selection
//  /        Division
//  /=       Division/assignment
//  <        Less than
//  <<       Left shift
//  <<=      Left shift/assignment
//  <=       Less than or equal to
//  =        Assignment
//  ==       Equality
//  >        Greater than
//  >>       Right shift
//  >>=      Right shift/assignment
//  ^        Exclusive OR
//  ^=       Exclusive OR/assignment
//  |        Bitwise inclusive OR
//  |=       Bitwise inclusive OR/assignment
//  ||       Logical OR



// If the parameter pack is empty, the expression is usually ill-formed
// (with the exception that for operator && the value is true, 
//  for operator || the value is false, and
//  for the comma operator the value for an empty parameter pack is void())


template<typename... T>
auto foldMultiply(T... m)
{
    return (m *= ...);
}

template<typename... T>
auto foldSumAssign(T... s)
{
    return (... += s);
}


template<typename... T>
auto foldSum(T... s) {
    return (... + s);
}

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int i = 0) : value(i), left(nullptr), right(nullptr) {}
};

auto left = &Node::left;
auto right = &Node::right;

template<typename T, typename ... TP>
Node* traverse(T np, TP... paths) {
    return (np ->* ... ->* paths);
}

#include <iostream>

template<typename T>
class AddSpace
{
private:
    T const& ref;
public:
    AddSpace(T const& r) : ref(r) {}
    friend std::ostream& operator<< (std::ostream& os, AddSpace<T> s) {
        return os << s.ref << ' ';
    }
};

template<typename... Types>
void print(Types const&... args)
{
    (std::cout << ... << AddSpace(args)) << '\n';
}

int main()
{
    Node* root = new Node{0};
    root->left = new Node{1};
    root->left->right = new Node{2};

    Node* node = traverse(root, left, right);

    print("hello", "hi", "hi there");

    std::cout << foldSum(1, 2, 3);
}