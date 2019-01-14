#include <iostream>
#include <vector>
#include <utility>

using namespace std;

static int PERF_TEST = 0;

struct Foo
{
    Foo()
    {
        if (!PERF_TEST) std::cout << "[default constructor] Foo::Foo()\n";
    }

    Foo(int i)
        : m_i(i)
    {
        if (!PERF_TEST) std::cout << "[constructor] Foo::Foo(int i: " << i << ")\n";
    }

    Foo(int i, bool b, float f)
        : m_i(i)
        , m_b(b)
        , m_f(f)
    {
        if (!PERF_TEST) std::cout << "[constructor] Foo::Foo(int i: " << i << ", bool b: " << (b ? "true" : "false") << ", float f: " << f << ")\n";
    }

    Foo(int i, bool b, float f, vector<int> const& v)
        : m_i(i)
        , m_b(b)
        , m_f(f)
        , m_v(v)
    {
        if (!PERF_TEST) std::cout << "[constructor] Foo::Foo(int i: " << i << ", bool b: " << (b ? "true" : "false") << ", float f: " << f
                                  << ", vector<int> const& v)\n";
    }

    Foo(int i, bool b, float f, vector<int>&& v)
        : m_i(i)
        , m_b(b)
        , m_f(f)
        , m_v(move(v))
    {
        if (!PERF_TEST) std::cout << "[constructor] Foo::Foo(int i: " << i << ", bool b: " << (b ? "true" : "false") << ", float f: " << f
                                  << ", vector<int>&& v)\n";
    }

    Foo(Foo const& other)
        : m_i(other.m_i)
        , m_b(other.m_b)
        , m_f(other.m_f)
    {
        m_v = other.m_v;
        if (!PERF_TEST) std::cout << "[copy constructor] Foo::Foo(Foo const& other)\n";
    }

    Foo(Foo&& other)
        : m_i(other.m_i)
        , m_b(other.m_b)
        , m_f(other.m_f)
        , m_v(move(other.m_v))
    {
        other.m_i = 0;
        other.m_b = false;
        other.m_f = 0.0f;

        if (!PERF_TEST) std::cout << "[move constructor] Foo::Foo(Foo&& other)\n";
    }

    int m_i = 0;
    bool m_b = false;
    float m_f = 0.0f;
    vector<int> m_v;
};

struct Bar
{
    Bar() {
        v.reserve(20);
    }
    // variadic template
    template<typename ... Args>
    void add_foo(Args&& ... args) // forwarding reference (universal reference)
    {
        //v.push_back(foo);
        //v.emplace_back(foo);
        v.emplace_back(forward<Args>(args)...);
    }

    private:
    vector<Foo> v;
};

int main(int argc, char *argv[])
{
    if (argc == 2 && argv[1][0] == '+')
    {
        PERF_TEST = 1;
    }

    auto cnt = 1;
    if (PERF_TEST) cnt = 1000;

    Bar b;
    //Foo f(1, true, 2.f);

    vector<int> v = {1,2,3,4,5};
    b.add_foo(55);
    b.add_foo(1, true, 2.5f, move(v));
    b.add_foo(1, true, 2.5f, v);
    b.add_foo(23, false, 3.14159265f);
    //b.add_foo(4);
}
