// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

// how to call a specialization explicitly

#include <iostream>

template<typename T, typename U>
void foo(T x, U y)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

int main()
{
    std::cout << "foo<int, int>('x', 3.1):  ";
    foo<int, int>('x', 3.1);

    std::cout << "foo<int>('x', 3.1):  ";
    foo<int>('x', 3.1);

    std::cout << "foo<>('x', 3.1):  ";
    foo<>('x', 3.1);

    std::cout << "foo('x', 3.1):  ";
    foo('x', 3.1);
}
