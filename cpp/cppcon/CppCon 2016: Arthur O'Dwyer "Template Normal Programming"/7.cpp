// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

// in the STL: the best of both worlds

#include <stdio.h>

template<typename T>
struct is_void
{
    static constexpr bool value = false;
};

template<>
struct is_void<void>
{
    static constexpr bool value = true;
};

template<typename T>
constexpr bool is_void_v = is_void<T>::value;


int main()
{
    printf("is_void<int>::value: %d\n", is_void<int>::value);
    printf("is_void<void>::value: %d\n", is_void<void>::value);
    printf("is_void_v<int>: %d\n", is_void_v<int>);
    printf("is_void_v<void>: %d\n", is_void_v<void>);
}
