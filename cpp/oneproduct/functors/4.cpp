#include <iostream>

//functors -> function object
//function

void DoSomething(int i, bool b, float f, double d, unsigned u, char c)
{
    std::cout << "DoSomething(i: " << i << ", b: " << b << ", f: " << f
              << ", d: " << d << ", u: " << u << ", c: " << c << ");\n";
}

struct DoSomethingFunctor
{
    explicit DoSomethingFunctor(int i, bool b, float f, double d, unsigned u)
        : m_i(i), m_b(b), m_f(f), m_d(d), m_u(u)
    {
        std::cout << "DoSomethingFunctor::DoSomethingFunctor(...)\n";
    }
    void operator()(char c) const
    {
        std::cout << "DoSomethingFunctor::operator(char)\n";
        std::cout << "i: " << m_i << ", b: " << m_b << ", f: " << m_f
                  << ", d: " << m_d << ", u: " << m_u << ", c: " << c << "\n";
    }

    private:
    int m_i;
    bool m_b;
    float m_f;
    double m_d;
    unsigned m_u;
};

int main() {
    DoSomething(1, true, 2.f, 3.14, 4u, 'a');
    DoSomething(1, true, 2.f, 3.14, 4u, 'b');

    std::cout << "\n\nCreate a functor to be able partially apply a function.\n";
    DoSomethingFunctor dsf(1, true, 2.f, 3.14, 4u);
    dsf('a');
    dsf('b');
}
