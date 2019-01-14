#include <cstdio>

template <typename T>
void Foo(T t)
{
    std::printf("Foo(T t)\n");
}

#if 1
template <typename T>
//const reference will be abiguous with Foo(T t) in Foo(32) call
//void Foo(T const&t)
void Foo(T &t)
{
    std::printf("Foo(T &t)\n");
}
#endif

template <typename T>
void Foo(T *t)
{
    std::printf("Foo(T *t)\n");
}

int main() {
    std::printf("Foo(32): ");
    Foo(32);

    int x = 13;
    //std::printf("Foo(x): ");
    //Foo(x);

    std::printf("Foo(&x): ");
    Foo(&x);
}
