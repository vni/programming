// SFINAE -> Substitution Failure Is Not An Error EXAMPLE

#include <cstdio>
#include <cmath>
#include <type_traits>

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
    std::printf("\n\n");

    std::printf("Equals(1, 1): %s\n", Equals(1, 1) ? "true" : "false");
    std::printf("Equals(1.f, 1.f): %s\n", Equals(1.f, 1.f) ? "true" : "false");
    std::printf("Equals(3.14, 3.14): %s\n", Equals(3.14, 3.14) ? "true" : "false");
    std::printf("Equals(1u, 1u): %s\n", Equals(1u, 1u) ? "true" : "false");

    std::printf("\n\n");
    // the author has 0.199999, not 0.2f. Can't repeat this for myself.
    std::printf("0.02f: %f, 0.42f - 0.4f: %f\n", 0.02f, static_cast<float>(0.42f - 0.4f));
    std::printf("Equals(0.42f - 0.4f, 0.02f): %s\n", Equals(0.42f - 0.4f, 0.02f) ? "true" : "false");
    std::printf("0.02: %f, 0.42 - 0.4: %f\n", 0.02, 0.42 - 0.4);
    std::printf("Equals(0.42 - 0.4, 0.02): %s\n", Equals(0.42 - 0.4, 0.02) ? "true" : "false");

    std::printf("Equals(2.f, 1.9987f + 0.0013f): %s\n", Equals(2.f, 1.98f + 0.02f) ? "true" : "false");

}
