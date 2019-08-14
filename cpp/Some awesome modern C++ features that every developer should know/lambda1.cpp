// https://www.freecodecamp.org/news/some-awesome-modern-c-features-that-every-developer-should-know-5e3bf6f79a3c/

#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<std::pair<int, int>> data = {{1, 3}, {7, 6}, {12, 4}};
    std::sort(begin(data), end(data), [](auto a, auto b) {
            return a.second < b.second;
    });

    for (auto x: data) {
        std::cout << "{" << x.first << ", " << x.second << "} ";
    }
    std::cout << '\n';
}
