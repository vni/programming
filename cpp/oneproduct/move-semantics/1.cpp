#include <iostream>

struct Foo {
    Foo() = default;

    Foo(Foo const& other) {
        std::cout << "Foo::Foo(const Foo &other{" << other.i << ": " << *other.i << "}\n";
        if (other.i != nullptr) {
            i = new int(*other.i);
        }
    }

    Foo& operator=(Foo const& other) {
        std::cout << "Foo::operator=(Foo const& other)\n";
        if (other.i != nullptr) {
            i = new int(*other.i);
        }
        return *this;
    }

    Foo& operator=(Foo const& other) {
        std::cout << "Foo::operator=(Foo && other)\n";
        if (other.i != nullptr) {
            i = new int(*other.i);
        }
        return *this;
    }

    ~Foo() {
        std::cout << "Foo::~Foo() i: " << i << ", *i: " << *i << "\n";

        if (i != nullptr) {
            delete i;
            i = nullptr;
        }
    }

    int *i = nullptr;
};

void FuncByValue(Foo other); // value semantics -> copy
void FuncByRef(Foo &other);  // reference semantics

int main() {
    Foo f1;
    {
        Foo f2;
        f2.i = new int(42);

        f1 = f2;
    }
}
