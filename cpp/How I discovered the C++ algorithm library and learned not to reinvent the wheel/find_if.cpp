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
    std::vector<int> collection = { 1, 2, 0, 5, 0, 3, 4 };
    print_collection(collection);

    auto itr = std::find_if(collection.begin(), collection.end(), [](auto x) { return x != 0 && x % 5 == 0; });
    std::cout << "find_if (x != 0 && x % 5 == 0) itr is at pos: " << itr - collection.begin() << ", *itr: " << *itr << "\n";
}
