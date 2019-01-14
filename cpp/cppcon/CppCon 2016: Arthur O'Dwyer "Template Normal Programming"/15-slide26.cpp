// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

#include <cstdio>

template<typename R, typename A>
void foo(R (*fptr)(A))
{
    std::puts(__PRETTY_FUNCTION__);
}

int main()
{
    // Captureless lambda types are always implicitly convertible to function pointer type.
    // But being implicitly convertible to a thing doesn't mean actually being that thing!
    //
    // Here is captureless lambda is not implicitly converted to function pointer.
    // To make careless lambda a function pointer add '+' before '[]'.
    //
    // error: no matching function for call to ‘foo(main()::<lambda(double)>)’ foo(  [](double x) { return int(x); } )
    //
    //foo(  [](double x) { return int(x); } );

    foo( +[](double x) { return int(x); } );
    foo( +[](unsigned long x) -> bool { return x >= 5000; } );
}
