// https://www.youtube.com/watch?v=LY2Q9ej9Zn8
// C++ Templates - Part 3: Type Deduction

#include <cstdio>

#if 0
template<typename T>
void Foo(T t) {
    std::printf("Foo(T t)\n");
}
#endif

#if 1
template<typename T>  // if T -> int const
void Foo(T &t) {      // then t -> int const &
    std::printf("Foo(T& t)\n");
    //T x = 44;
    //++x;
}
#endif

#if 1
template<typename T>
void Foo(T const&t) {
    std::printf("Foo(const T& t)\n");
}
#endif

#if 1
template<typename T>
void Foo(T *t) {
    std::printf("Foo(T *t)\n");

    //T x = 28;
    //++x;
}
#endif

int main() {
    //std::printf("Foo(42) --> ");
    //Foo(42);

    int x = 13;
    std::printf("Foo(x) --> ");
    Foo(x);

    std::printf("Foo(&x) --> ");
    Foo(&x);

    const int cx = 169;
    std::printf("Foo(cx) --> ");
    Foo(cx);

    std::printf("Foo(&cx) --> ");
    Foo(&cx);

    //std::printf("Foo(&x) --> ");
    //Foo(&x);
}
