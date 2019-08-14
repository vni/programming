// https://www.freecodecamp.org/news/some-awesome-modern-c-features-that-every-developer-should-know-5e3bf6f79a3c/

#include <set>
#include <iostream>

int main()
{
    std::set<int> input = {1, 5, 3, 6};

    if (auto it = input.find(7); it == input.end())
    {
        std::cout << 7 << " not found!\n";
    }
    else
    {
        std::cout << 7 << " is there!\n";
    }
}
