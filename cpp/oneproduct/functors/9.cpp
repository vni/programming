#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

template<typename T>
struct MatchFirstFunctor
{
    MatchFirstFunctor(T const& v) : m_value(v) {}

    template<typename U>
    bool operator()(U const& p) const { return p.first == m_value; };

    private:
        T m_value;
};

int main() {

    vector<pair<int, bool>> v = { make_pair(1, true), make_pair(2, false), make_pair(3, true), make_pair(4, false) };
    vector<pair<bool, float>> vbf = { make_pair(true, 3.14159265f), make_pair(false, 2.f) };

    auto it = find(begin(v), end(v), make_pair(1, true));
    std::cout << "find(begin(v), end(v), make_pair(1, true)): {" << it->first << ", " << it->second << "}\n";

    it = find_if(begin(v), end(v), MatchFirstFunctor<int>(3));
    if (it != v.end())
        std::cout << "find_if(begin(v), end(v), MatchFirstFunctor(3)): {" << it->first << ", " << it->second << "}\n";

    cout << "\n\nvector<pair<bool, float>>\n";
    auto it2 = find_if(vbf.begin(), vbf.end(), MatchFirstFunctor<bool>(true));
    if (it2 != vbf.end())
        std::cout << "find_if(vbf.begin(), vbf.end(), MatchFirstFunctor(true)) {" << it2->first << ", " << it2->second << "}\n";
}
