// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

// type deduction (for function templates)

#include <iostream>

template<typename T>
T abs(T x)
{
    return (x >= 0) ? x : -x;
}

int main()
{
    //double (*foo)(double) = abs;
    std::cout << "double (*foo)(double) = abs<double>;\n";
    double (*foo)(double) = abs<double>;

    std::cout << "foo(-28): " << foo(-28) << "\n";
    std::cout << "foo(-3.14159265f): " << foo(-3.14159265f) << "\n";
    std::cout << "foo(-3.14159265): " << foo(-3.14159265) << "\n";

    std::cout << "\n\n";
    std::cout << "abs<int>(-42): " << abs<int>(-42) << "\n";
    std::cout << "abs(-42): " << abs(-42) << "\n";
}
