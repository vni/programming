#include <cstdio>
#include <cmath>
#include <type_traits>

//using namespace std;

// SFINAE -> Substitution Failure Is Not An Error

// templates -> parametric polymorphism

// std::enable_if_t by default uses the ```void``` type. So if you need void, you can skeep the type argument.
// Actually, it doesn't matter which type the third argument will be and which default value will be as soon as we do not uses it in the calling code.

template<typename T>
// bool Equals(T lhs, T rhs, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr)
bool Equals(T lhs, T rhs, std::enable_if_t<!std::is_floating_point<T>::value, void>* = nullptr)
{
    std::printf("Equals()\n");
    return lhs == rhs;
}

#if 1
template<typename T>
//bool Equals(T lhs, T rhs, std::enable_if_t<std::is_floating_point<T>::value, int> = 12)
//bool Equals(T lhs, T rhs, std::enable_if_t<std::is_floating_point<T>::value, void>* = (void*)0x12)
bool Equals(T lhs, T rhs, std::enable_if_t<std::is_floating_point<T>::value, void>* = 0)
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
#if 1
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
#endif
}
