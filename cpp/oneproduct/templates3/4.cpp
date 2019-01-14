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

struct S
{
    bool operator()(const int & i) const { return i == 2; }
};

int main()
{
    std::vector<int> v = { 1,2,3,4,5/*,6,7,8,9*/ };
    bool res = Contains(v.begin(), v.end(), HasATwo);
    std::printf("Contains(v.begin(), v.end(), HasATwo): %s\n", res ? "true" : "false");

    res = Contains(v.begin(), v.end(), HasEight);
    std::printf("Contains(v.begin(), v.end(), HasEight): %s\n", res ? "true" : "false");

    res = Contains(v.begin(), v.end(), [](const int &i) { return i == 4; });
    std::printf("Contains(v.begin(), v.end(), [](const int &i) { return i == 4; }): %s\n", res ? "true" : "false");

    //S s;
    /*
     *std::printf("\n\n");
     *res = Contains(v.begin(), v.end(), S());
     *std::printf("bool S::opeartor()(const int & i) const { return i == 2; }\n");
     *std::printf("Contains(v.begin(), v.end(), S()): %s\n", res ? "true" : "false");
     */
}
