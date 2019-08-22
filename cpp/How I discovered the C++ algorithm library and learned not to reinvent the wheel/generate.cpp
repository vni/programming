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

    int counter = 0;
    std::generate(collection.begin(), collection.end(), [&counter]() { return counter++; });
    print_collection(collection);
}
