// https://www.freecodecamp.org/news/some-awesome-modern-c-features-that-every-developer-should-know-5e3bf6f79a3c/

#include <iostream>
#include <vector>

int main() {
    auto a = { 1, 2, 3};
    for (auto &x: a) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}
