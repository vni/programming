#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <utility>

using namespace std;

static int PERF_TEST = 0;

struct Foo
{
    Foo() {
        if (!PERF_TEST) std::cout << "[default constructor] Foo::Foo()\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    Foo(Foo const& other) {
        if (!PERF_TEST) std::cout << "[copy constructor] Foo::Foo(Foo const& other)\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    Foo(Foo&&) {
        if (!PERF_TEST) std::cout << "[move constructor] Foo::Foo(Foo&& other)\n";
    }
};

int main(int argc, char *argv[])
{
    if (argc == 2 && argv[1][0] == '1')
    {
        PERF_TEST = 1;
    }

    auto cnt = 1;
    if (PERF_TEST) cnt = 1000;
    vector<Foo> v1;
    {
        while(cnt--)
        {
            //Foo f1;
            //v1.push_back(f1);
            //v1.push_back(move(f1));
            v1.push_back(Foo());
            //v1.emplace_back(Foo());
            //v1.emplace_back(move(f1));
        }
    }
}
