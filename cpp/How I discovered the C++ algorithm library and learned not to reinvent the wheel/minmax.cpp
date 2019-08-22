#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void print_collection(T const& co)
{
    for (auto const& x: co)
        std::cout << " " << x;
    std::cout << "\n";
}

int main()
{
    int a = 9, b = 12;
    auto out = std::minmax(a ,b);
    std::cout << "out: { " << out.first << ", " << out.second << " }\n";

    std::vector<int> collection = { 6, 5, 3, 2, 1, 4, 6, 7 };
    print_collection(collection);

    auto result = std::minmax_element(begin(collection), end(collection));
    std::cout << "result: { " << (result.first - begin(collection))
              << ", " << (result.second - begin(collection)) << " }\n";
    std::cout << "*result: { " << *result.first << ", " << *result.second << " }\n";
}
