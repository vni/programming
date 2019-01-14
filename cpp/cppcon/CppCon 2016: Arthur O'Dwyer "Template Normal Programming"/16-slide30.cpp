// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

#include <algorithm>
#include <iostream>

short f() { return 54; }

int main()
{
    int x = 42;

    // compilation error. f() and x have different types.
    // works only with type conversion from short to int
    //return std::max(f(), 15); // f() is short, 15 is int.


    std::cout << "std::max(static_cast<int>(f()), x): " << std::max(static_cast<int>(f()), x) << "\n";
    std::cout << "std::max<int>(f(), x): " << std::max<int>(f(), x) << '\n';
}
