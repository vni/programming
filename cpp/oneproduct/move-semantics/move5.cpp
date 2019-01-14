#include <vector>
#include <utility>

using namespace std;

struct Foo {
    vector<int> v;

    Foo(vector<int>&& vv) // is actually an lvalue within the scope of a function
        : v(move(vv))
    {
        // maybe I want to use vv
        vv.front();
        //vv.push_back(10);
        //vv.erase(...);
    }

    // lot of expensive other data
    // Bar b; // Bar has a *very* expensive constructor
};

void fill_vector(vector<int>& v) {
    // fills v conditionally
}

int main() {
#if 0
    Foo f;
    fill_vector(f.v);

    if (!f.v.empty())
    {
        // do something
    }
    else
    {
        // we made Foo for nothing
    }
#endif

    vector<int> v;
    fill_vector(v);

    if (!v.empty())
    {
        Foo f1(std::move(v));
        //valid but unspecified state
        v.front(); // not safe! Because we're in an unspecified state
        v.clear(); // this is fine. Because it doesn't depent on a state
    }
    else
    {
    }
}
