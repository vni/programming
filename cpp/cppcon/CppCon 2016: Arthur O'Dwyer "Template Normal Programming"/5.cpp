// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

// class template

#include <stdio.h>

template<typename T>
struct is_void
{
    static const bool value = false;
};

#if 1
template<>
struct is_void<void>
{
    static const bool value = true;
};
#endif

int main()
{
    printf("is_void<int>::value: %d\n", is_void<int>::value);
    printf("is_void<void>::value: %d\n", is_void<void>::value);
}
