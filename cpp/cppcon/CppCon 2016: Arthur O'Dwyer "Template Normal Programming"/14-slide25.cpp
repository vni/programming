// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

#include <cstdio>
#include <array>

template<typename T, typename U>
void foo(std::array<T, sizeof(U)> x,
         std::array<U, sizeof(T)> y,
         int z)
{
    std::puts(__PRETTY_FUNCTION__);
    std::printf("sizeof(T): %zu\n", sizeof(T));
    std::printf("sizeof(U): %zu\n", sizeof(U));
}

int main()
{
    foo(std::array<int, 8>{}, std::array<double, 4>{}, 0.0);

    // error: could not convert ‘std::array<int, 9>{}’ from ‘std::array<int, 9>’ to ‘std::array<int, 8>’
    //foo(std::array<int, 9>{}, std::array<double, 4>{}, 0.0);
}
