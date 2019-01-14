// https://www.youtube.com/watch?v=Vkck4EU2lOU

// SFINAE -> Substitution Failure Is Not An Error EXAMPLE

#include <cstdio>
#include <cmath>
#include <type_traits>

struct Foo
{
    bool operator==(const Foo &other) {
        std::printf("bool Foo::operator==() { return true; }\n");
        return true;
    }
};

template<>
struct std::is_floating_point<Foo> : std::true_type
{
};

template<typename T>
typename std::enable_if<!std::is_floating_point<T>::value, bool>::type
Equals(T lhs, T rhs)
{
    //std::printf("Equals()\n");
    return lhs == rhs;
}

#if 1
template<typename T>
std::enable_if_t<std::is_floating_point<T>::value, bool>
/*bool*/ Equals(T lhs, T rhs)
{
    std::printf("Equals *FLOATING POINT*\n");
    // handle floating point imprecision
    return lhs == rhs;
}
#endif

int main()
{
    std::printf("Equals(1, 1): %s\n", Equals(1, 1) ? "true" : "false");
    std::printf("Equals(1.f, 1.f): %s\n", Equals(1.f, 1.f) ? "true" : "false");
    std::printf("Equals(1u, 1u): %s\n", Equals(1u, 1u) ? "true" : "false");
    std::printf("\n\n");
    std::printf("Equals(Foo(), Foo()): %s\n", Equals(Foo(), Foo()) ? "true" : "false");
}
