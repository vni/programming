// https://www.freecodecamp.org/news/some-awesome-modern-c-features-that-every-developer-should-know-5e3bf6f79a3c/

#include <iostream>

constexpr double fib(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return fib(n-1) * n;
}

int main()
{
    const long long bigval = fib(20);
    std::cout << bigval << std::endl;
}
