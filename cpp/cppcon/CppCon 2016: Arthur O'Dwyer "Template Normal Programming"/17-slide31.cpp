// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

#include <iostream>

template<typename T>
T x_abs(T x)
{
    std::cout << __PRETTY_FUNCTION__ << ' ';
    return (x >= 0) ? x : -x;
}

int main()
{
    std::cout << "x_abs('x'): " << x_abs('x') << '\n';
    std::cout << "x_abs<int>('x'): " << x_abs<int>('x') << '\n';
    std::cout << "x_abs(3): " << x_abs(3) << '\n';
    std::cout << "x_abs<>(3): " << x_abs<>(3) << '\n';
    std::cout << "x_abs(-3): " << x_abs(-3) << '\n';
    std::cout << "x_abs<double>(3): " << x_abs<double>(3) << '\n';
}
