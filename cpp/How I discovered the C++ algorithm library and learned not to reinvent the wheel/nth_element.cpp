#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void print_collection(T const& collection)
{
    std::cout << "collection:";
    std::for_each(collection.begin(), collection.end(), [](auto x) { std::cout << " " << x; });
    std::cout << "\n";
}

int main()
{
    std::vector<int> collection{ 1, 2, 13, 5, 12, 3, 4 };
    //std::vector<int> collection{ 100, 19, 13, 5, 12, 3, 4 };
    print_collection(collection);

    auto median_pos = collection.begin() + collection.size() / 2;
    std::nth_element(collection.begin(), median_pos, collection.end());
    //std::nth_element(collection.begin(), collection.begin()+5, collection.end());
    print_collection(collection);
}
