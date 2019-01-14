// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

// alias templates

#include <type_traits>
#include <vector>
#include <iostream>

typedef std::vector<int> myvec_int; // C++03 alias syntax

using myvec_double = std::vector<double>; // C++11 syntax

template<typename T>
using myvec = std::vector<T>; // C++11 syntax

int main()
{
    static_assert(std::is_same_v<myvec_int, std::vector<int>>, "myvec_int and std::vector<int> is not the same types");

    static_assert(std::is_same_v<myvec_double, std::vector<double>>);

    static_assert(std::is_same_v<myvec<float>, std::vector<float>>);

    std::cout << "done\n";
};
