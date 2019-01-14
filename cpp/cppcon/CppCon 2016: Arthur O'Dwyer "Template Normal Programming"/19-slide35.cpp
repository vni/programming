// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

// default template parameters

#include <iostream>

template<typename T>
void foo()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

int main()
{
    std::cout << "foo<int>():  ";
    foo<int>();

#if 0
    // compilation error: error: no matching function for call to ‘foo()’
    // note: candidate: template<class T> void foo()
    //
    // note:   template argument deduction/substitution failed:
    // note:   couldn't deduce template parameter ‘T’

    std::cout << "foo<>():  ";
    foo<>();

    std::cout << "foo():  ";
    foo();
#endif
}
