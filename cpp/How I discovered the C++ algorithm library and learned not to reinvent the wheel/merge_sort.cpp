#include <iostream>
#include <vector>
#include <algorithm>

void merge_sort(auto l, auto r)
{
    if (r - l > 1)
    {
        auto mid = l + (r-l) / 2;
        merge_sort(l, mid);
        merge_sort(mid, r);
        std::inplace_merge(l, mid, r);
    }
}

template<typename T>
void print_collection(T const& co)
{
    for (auto const& x: co)
    {
        std::cout << " " << x;
    }
    std::cout << "\n";
}

int main()
{
    std::vector<int> collection = { 2, 4, 4, 1, 1, 3, 9 };

    std::cout << "collection: ";
    print_collection(collection);

    merge_sort(begin(collection), end(collection));
    std::cout << "after merge_sort collection: ";
    print_collection(collection);
}
