#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void print_collection(T const &co, std::string const& prefix = "")
{
    if (!prefix.empty())
    {
        std::cout << prefix;
    }

    for(const auto &x: co)
    {
        std::cout << " " << x;
    }
    std::cout << "\n";
}

int main()
{
    std::vector<int> c1 = { 1, 2, 5, 5, 5, 6, 9, 12 };
    print_collection(c1, "c1:");

    std::vector<int> c2 = { 2, 4, 4, 5, 7, 15 };
    print_collection(c2, "c2:");

    std::vector<int> result;

    std::merge(c1.begin(), c1.end(), c2.begin(), c2.end(), std::back_inserter(result));
    print_collection(result, "result after merge:");
}
