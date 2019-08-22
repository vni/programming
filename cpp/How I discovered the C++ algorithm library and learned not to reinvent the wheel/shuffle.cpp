#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

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
    std::vector<int> collection = { 1, 2, 13, 5, 12, 3, 4 };
    print_collection(collection);

    std::random_device rd;
    std::mt19937 rand_gen(rd());
    std::shuffle(collection.begin(), collection.end(), rand_gen);

    std::cout << "after std::shuffle(collection, rand_gen\n";
    print_collection(collection);
}
