#include <iostream>
#include <algorithm>
#include <vector>

template<typename Collection>
void print_collection(const Collection &collection)
{
    std::cout << "collection: ";
    for (const auto &x: collection) {
        std::cout << x << " ";
    }
    std::cout << "\n\n";
}

int main()
{
    std::vector<int> collection = { 1, 9, 9, 4, 2, 6 };
    print_collection(collection);

    int nines = std::count(begin(collection), end(collection), 9);
    std::cout << "count nines: " << nines << "\n";

    int evens = std::count_if(collection.begin(), collection.end(), [](auto x) { return x % 2 == 0; });
    std::cout << "count_if evens: " << evens << "\n";
}
