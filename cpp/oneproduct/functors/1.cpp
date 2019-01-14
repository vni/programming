#include <iostream>

//functors -> function object
//function

struct Object
{
    int operator()(int i) const
    {
        return i;
    }
};

int Foo(int i)
{
    return i;
}

int main() {
    std::cout << "Foo(42): " << Foo(42) << "\n";

    Object o;
    std::cout << "Object o; o(18): " << o(18) << "\n";
}
