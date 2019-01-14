// https://www.learncpp.com/cpp-tutorial/15-4-stdmove/

#include <iostream>

static bool DISABLE_OUTPUT = false;

class Foo
{
    public:
        Foo()
        {
            if (!DISABLE_OUTPUT)
            std::cout << "[default constructor]\n";
        }

        Foo(int i)
            : m_i(i)
        {
            if (!DISABLE_OUTPUT)
            std::cout << "[int constructor]\n";
        }

        Foo(Foo const& other)
            : m_i(other.m_i)
        {
            if (!DISABLE_OUTPUT)
            std::cout << "[copy constructor]\n";
        }

        Foo& operator=(Foo const& other)
        {
            if (!DISABLE_OUTPUT)
            std::cout << "[assign operator]\n";
            m_i = other.m_i;
            return *this;
        }

        Foo(Foo&& other)
        {
            if (!DISABLE_OUTPUT)
            std::cout << "[move constructor]\n";
            m_i = other.m_i;
            other.m_i = 0;
        }

        Foo& operator=(Foo&& other)
        {
            if (!DISABLE_OUTPUT)
            std::cout << "[move operator]\n";
            m_i = other.m_i;
            other.m_i = 0;
            return *this;
        }

        int value() const {
            return m_i;
        }

    private:
        int m_i = 42;
};

template<class T>
void swap_copy(T& a, T& b)
{
    //T t{a};
    T t(a);
    a = b;
    b = t;
}

template<class T>
void swap_move(T& a, T& b)
{
    //T t{a};
    T t(static_cast<T&&>(a));
    a = static_cast<T&&>(b);
    b = static_cast<T&&>(t);
}

int main(int argc, char *argv[])
{
    auto cnt = 1;
    if (argc == 2 && argv[1][0] == '+') {
        cnt = 100'000'001;
        DISABLE_OUTPUT = true;
    }
    //-----------------------------------------------------

    Foo x(16);
    Foo y(13);

    std::cout << "x: " << x.value() << "\n";
    std::cout << "y: " << y.value() << "\n";

    while (cnt--)
    {
        swap_copy(x, y);
    }

    std::cout << "x: " << x.value() << "\n";
    std::cout << "y: " << y.value() << "\n";
}
