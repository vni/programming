#include <cstdio>
#include <cmath>
#include <type_traits>

//using namespace std;

// tag dispatch
// SFINAE -> Substitution Failure Is Not An Error

// templates -> parametric polymorphism

template<typename T>
bool Equals(T lhs, T rhs, std::true_type)/*Floating*/
{
    std::printf("Equals *Floating*\n");
    // impresiction handling
    return lhs == rhs;
}

template<typename T>
bool Equals(T lhs, T rhs, std::false_type)/*NonFloating*/
{
    std::printf("Equals *NonFloating*\n");
    return lhs == rhs;
}

template<typename T>
bool Equals(T lhs, T rhs)
{
    //return Equals(lhs, rhs, std::conditional_t<std::is_floating_point<T>::value, std::true_type, std::false_type>{});
    return Equals(lhs, rhs, typename std::conditional<std::is_floating_point<T>::value, std::true_type, std::false_type>::type {});
}

int main()
{
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
