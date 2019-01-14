// https://www.youtube.com/watch?v=LY2Q9ej9Zn8
// C++ Templates - Part 3: Type Deduction

#include <cstdio>

template<typename T>
bool Equals(T lhs, T rhs)
{
    return lhs == rhs;
}

int main() {
    std::printf("Equals(1, static_cast<int>(1.f)): %s\n", Equals(1, static_cast<int>(1.f)) ? "true" : "false");
    std::printf("Equals<int>(1, 1.f): %s\n", Equals<int>(1, 1.f) ? "true" : "false");
}
