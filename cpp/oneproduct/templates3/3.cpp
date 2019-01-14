// https://www.youtube.com/watch?v=LY2Q9ej9Zn8
// C++ Templates - Part 3: Type Deduction

#include <cstdio>
#include <vector>

template<typename It>
bool Contains(It first, It last, bool (*pred)(typename It::value_type const&))
{
    for (; first != last; ++first)
        if (pred(*first))
            return true;
    return false;
}

bool HasATwo(int const& i) { return i == 2; }
bool HasEight(int const& i) { return i == 8; }

int main()
{
    std::vector<int> v = { 1,2,3,4,5/*,6,7,8,9*/ };
    bool res = Contains(v.begin(), v.end(), HasATwo);
    std::printf("Contains(v.begin(), v.end(), HasATwo): %s\n", res ? "true" : "false");

    res = Contains(v.begin(), v.end(), HasEight);
    std::printf("Contains(v.begin(), v.end(), HasEight): %s\n", res ? "true" : "false");
}
