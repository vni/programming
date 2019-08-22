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
    std::vector<int> collection = { 2, 4, 4, 1, 1, 3, 9 };
    print_collection(collection);

    std::for_each(begin(collection), end(collection), [](int &x) { x += 26; });

    print_collection(collection);
}
