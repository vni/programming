// https://www.youtube.com/watch?v=vwrXHznaYLA
// CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)”
//

// literally the same type

#include <cstdint>
#include <vector>
//#include <iostream>

using myint = int;

template<typename T>
using myvec = std::vector<T>;

void f(const myint &mv);
void g(const myvec<int> &mv);

int main()
{
    int i;
    f(i);

    // TVOYU MATJ
    short int si;
    long int li;
    int64_t i64;
    f(si);
    f(li);
    f(i64);

    std::vector<int> v = { 1, 2, 3, 4 };
    g(v);

    /* At least this doesn't compile
    std::vector<short int> v_si = { 1, 2, 3, 4 };
    g(v_si);

    std::vector<int64_t> v_i64 = { 1, 2, 3, 4 };
    g(v_i64);

    std::vector<uint64_t> v_ui64 = { 1, 2, 3, 4 };
    g(v_ui64);
    */
};
