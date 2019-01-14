// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

// default template parameters

#include <iostream>

template<typename T = char *>
void foo()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

int main()
{
    std::cout << "foo<int>():  ";
    foo<int>();

    std::cout << "foo<>():  ";
    foo<>();

    std::cout << "foo():  ";
    foo();
}
