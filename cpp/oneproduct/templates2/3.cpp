#include <cstdio>
#include <cmath>

using namespace std;

// templates -> parametric polymorphism
template<typename T>
bool Equals(T lhs, T rhs)
{
    return lhs == rhs;
}

// template specialization
template<>
bool Equals<float>(float lhs, float rhs)
{
    printf("Equals<float>\n");
    // implement something that takes floating point imprecission into account
    return lhs == rhs;
}

template<>
bool Equals<double>(double lhs, double rhs)
{
    printf("Equals<doule>\n");
    // implement something that takes floating point imprecission into account
    return lhs == rhs;
}

int main()
{
    printf("Equals(1, 1): %s\n", Equals(1, 1) ? "true" : "false");
    printf("Equals(1.f, 1.f): %s\n", Equals(1.f, 1.f) ? "true" : "false");
    printf("Equals(3.14, 3.14): %s\n", Equals(3.14, 3.14) ? "true" : "false");
    printf("Equals(1u, 1u): %s\n", Equals(1u, 1u) ? "true" : "false");

    printf("\n\n");
    // the author has 0.199999, not 0.2f. Can't repeat this for myself.
    printf("0.02f: %f, 0.42f - 0.4f: %f\n", 0.02f, static_cast<float>(0.42f - 0.4f));
    printf("Equals(0.42f - 0.4f, 0.02f): %s\n", Equals(0.42f - 0.4f, 0.02f) ? "true" : "false");
    printf("0.02: %f, 0.42 - 0.4: %f\n", 0.02, 0.42 - 0.4);
    printf("Equals(0.42 - 0.4, 0.02): %s\n", Equals(0.42 - 0.4, 0.02) ? "true" : "false");

    printf("Equals(2.f, 1.9987f + 0.0013f): %s\n", Equals(2.f, 1.98f + 0.02f) ? "true" : "false");
}
