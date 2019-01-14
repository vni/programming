#include <cstdio>
#include <cmath>

using namespace std;

template<typename T>
bool Equals(T lhs, T rhs)
{
    return lhs == rhs;
}

int main()
{
    printf("Equals(1, 1): %s\n", Equals(1, 1) ? "true" : "false");
    printf("Equals(1.f, 1.f): %s\n", Equals(1.f, 1.f) ? "true" : "false");
    printf("Equals(3.14, 3.14): %s\n", Equals(3.14, 3.14) ? "true" : "false");
    printf("Equals(1u, 1u): %s\n", Equals(1u, 1u) ? "true" : "false");

    // would not compile due to a type mismatch
    //printf("Equals(1, 1.): %s\n", Equals(1, 1.) ? "true" : "false");
    //printf("Equals(1.f, 1.): %s\n", Equals(1.f, 1.) ? "true" : "false");

    printf("\n\n");
    printf("Equals(1.25f, 1.f + 0.25f): %s\n", Equals(1.25f, 1.f + 0.25f) ? "true" : "false");

    printf("Equals(2.f, 1.9987f + 0.0013f): %s\n", Equals(2.f, 1.98f + 0.02f) ? "true" : "false");
}
