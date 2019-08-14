//https://www.freecodecamp.org/news/some-awesome-modern-c-features-that-every-developer-should-know-5e3bf6f79a3c/

#include <vector>
#include <iostream>

auto do_something(auto a, auto b)
{
    auto a_size = a.size();
    auto b_size = b.size();
    //std::vector<int> result;
    auto result = a;

    for (auto i = 0; i < a_size && i < b_size; ++i) {
        //result.emplace_back(a[i] + b[i]);
        result[i] += b[i];
    }

    return result;
}

auto merge(auto a, auto b)
{
    //std::vector<int> c = do_something(a, b);
    //return c;
    return do_something(a, b);
}

int main()
{
    std::vector<float> a = { 10.93, 20.73, 30.53 };
    std::vector<float> b = { 90.07, 80.27, 70.47 };
    auto c = merge(a, b);

    for (auto &x: c) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}
