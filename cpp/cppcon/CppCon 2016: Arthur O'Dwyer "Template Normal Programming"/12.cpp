// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

// rules of template type deduction

#include <cstdio>
#include <string>

template<typename T, typename U>
void f(T x, U y)
{
    std::puts(__PRETTY_FUNCTION__); // MSVC: __FUNCSIG__
}

template<typename T>
void g(T x, T y)
{
    std::puts(__PRETTY_FUNCTION__);
}

int main()
{
    std::puts("f(1, 2)");
    f(1, 2);

    std::puts("\nf(1, 2u)");
    f(1, 2u);

    std::puts("\ng(1, 2)");
    g(1, 2);

    /* will not compile. 1 and 2u has different types.
    std::puts("\ng(1, 2u)");
    g(1, 2u);
    */
}
