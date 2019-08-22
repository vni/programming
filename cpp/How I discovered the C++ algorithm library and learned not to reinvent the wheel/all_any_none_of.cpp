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
    std::vector<int> collection = { 3, 6, 12, 6, 9, 12 };
    print_collection(collection);


    bool divby3 = std::all_of(begin(collection), end(collection), [](int x)
                              { return x % 3 == 0; }
                             );
    std::cout << "all_of divby3: " << divby3 << "\n";


    bool divby2 = std::any_of(begin(collection), end(collection), [](auto x)
                              { return x % 2 == 0; }
                             );
    std::cout << "any_of divby2: " << divby2 << "\n";


    bool divby6 = std::none_of(begin(collection), end(collection), [](auto x)
                               { return x % 6 == 0; }
                              );
    std::cout << "none_of divby6: " << divby6 << "\n";


    bool none_of_4 = std::none_of(begin(collection), end(collection), [](auto x)
                                  { return x == 4; }
                                 );
    std::cout << "none_of 4: " << none_of_4 << "\n";
}
