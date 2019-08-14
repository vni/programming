// https://www.freecodecamp.org/news/some-awesome-modern-c-features-that-every-developer-should-know-5e3bf6f79a3c/

#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> data = {2, 4, 4, 1, 1, 3, 9};
    int factor = 7;
    for_each(begin(data), end(data), [&factor](int &val) {
            val *= factor;
            factor--;
    });

    // 14 24 20 4 3 6 9
    for (int val: data) {
        std::cout << val << ' ';
    }
    std::cout << '\n';
}
