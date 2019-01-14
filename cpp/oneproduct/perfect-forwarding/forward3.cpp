#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <utility>

using namespace std;

static int PERF_TEST = 0;

struct Foo
{
    Foo(int i, bool b, float f)
        : m_i(i)
        , m_b(b)
        , m_f(f)
    {
        if (!PERF_TEST) std::cout << "[default constructor] Foo::Foo()\n";
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    Foo(Foo const& other)
        : m_i(other.m_i)
        , m_b(other.m_b)
        , m_f(other.m_f)
    {
        if (!PERF_TEST) std::cout << "[copy constructor] Foo::Foo(Foo const& other)\n";
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    Foo(Foo&& other)
        : m_i(other.m_i)
        , m_b(other.m_b)
        , m_f(other.m_f)
    {
        other.m_i = 0;
        other.m_b = false;
        other.m_f = 0.0f;

        if (!PERF_TEST) std::cout << "[move constructor] Foo::Foo(Foo&& other)\n";
    }

    int m_i;
    bool m_b;
    float m_f;
};

int main(int argc, char *argv[])
{
    if (argc == 2 && argv[1][0] == '+')
    {
        PERF_TEST = 1;
    }

    auto cnt = 1;
    if (PERF_TEST) cnt = 1000;
    vector<Foo> v1;
    {
        while(cnt--)
        {
            //Foo f1(10, true, 2.23f);
            //v1.push_back(f1);
            //v1.push_back(move(f1));
            //v1.push_back(Foo(1, true, 2.2f));
            //v1.emplace_back(move(f1));
            //v1.emplace_back(Foo(1, true, 2.42f));

            v1.emplace_back(1, true, 2.42f);
        }
    }
}
