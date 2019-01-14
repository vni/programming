// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

#include <algorithm>

short f() { return 44; }

int main()
{
    int x = 42;

    // compilation error. f() and x have different types.
    // works only with type conversion from short to int
    //return std::max(f(), 15); // f() is short, 15 is int.
    return std::max(static_cast<int>(f()), x);
}
