#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    //std::vector<int> collection = { 1, 2, 5, 5, 5, 6, 9, 12 };
    // why the code below prints [2 ~ 13) ???
    std::vector<int> collection = { 1, 2, 5, 5, 5, 6, 9, 5, 5, 5, 5, 5, 5, 12 };
    auto range = std::equal_range(begin(collection), end(collection), 5);

    std::cout << "equal_range: [" << (range.first - begin(collection))
              << " ~ " << (range.second - begin(collection)) << ")\n";

    auto lb = std::lower_bound(begin(collection), end(collection), 5);
    std::cout << "lower_bound: " << lb - begin(collection) << "\n";

    auto ub = std::upper_bound(begin(collection), end(collection), 5);
    std::cout << "upper_bound: " << ub - begin(collection) << "\n";
}
