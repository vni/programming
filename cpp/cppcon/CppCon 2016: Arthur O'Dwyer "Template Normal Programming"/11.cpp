// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

// rules of template type deduction

#include <cstdio>
#include <string>

template<typename T>
void foo(T x)
{
    std::puts(__PRETTY_FUNCTION__); // MSVC: __FUNCSIG__
}

int main()
{
    std::printf("foo(4)\n");
    foo(4);

    std::printf("\nfoo(4.2)\n");
    foo(4.2);

    std::printf("\nfoo(4.2f)\n");
    foo(4.2f);

    std::printf("\nfoo(\"hello\")\n");
    foo("hello");

    std::printf("\nfoo(std::string(\"hello\"))\n");
    foo(std::string("hello"));
}
