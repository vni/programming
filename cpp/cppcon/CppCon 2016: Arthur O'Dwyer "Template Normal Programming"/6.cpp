// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

// variable template

#include <stdio.h>

template<typename T>
const bool is_void_v = false;

template<>
const bool is_void_v<void> = true;


int main()
{
    printf("is_void_v<int>: %d\n", is_void_v<int>);
    printf("is_void_v<void>: %d\n", is_void_v<void>);
}
