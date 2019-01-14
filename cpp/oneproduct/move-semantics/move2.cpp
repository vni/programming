#include <utility>

struct Foo
{
    // special member functions
    // WTF? Foo() = default;                            // constructor
    Foo() = default;
    Foo(Foo const& other) = default;            // copy constructor
    Foo& operator=(Foo const& other) = default; // assignment operator
    Foo(Foo&& other) = default;                 // move constructor
    Foo& operator=(Foo&& other) = default;      // move [assignment] operator
    /*virtual*/ ~Foo() = default;                           // destructor;

    int *i = nullptr;
};

int main()
{
    Foo f1;
    Foo f2(f1);
}
