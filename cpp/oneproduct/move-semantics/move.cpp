// move semantics

#include <stdio.h>
#include <utility>

constexpr int TIME_TEST = 1;

struct Foo
{
    Foo(const char *s)
        :str(s)
    {
        if (!TIME_TEST) printf("Foo::Foo(this: %p, str: %s)\n", this, str);
    }

    Foo(int i, const char *s)
        :i(new int(i)), str(s)
    {
        if (!TIME_TEST) printf("Foo::Foo(this: %p, i: %d, str: %s)\n", this, i, str);
    }

    Foo(Foo const& other, const char *s)
        :str(s)
    {
        if (!TIME_TEST) printf("Foo::Foo(this: %p, other.i: %p, *other.i: %d, str: %s)\n", this, other.i, *other.i, str);
        if (other.i != nullptr)
        {
            i = new int(*other.i);
        }
    }

    Foo& operator=(Foo const& other)
    {
        if (!TIME_TEST) printf("Foo& operator=(Foo const& (other.i: %p, *other.i: %d) str: %s\n", other.i, *other.i, str);
        if (other.i != nullptr)
        {
            i = new int(*other.i);
        }
        return *this;
    }

    Foo& operator=(Foo&& other) // rvalue reference
    {
        if (!TIME_TEST) printf("Foo& operator=(Foo&& (other.i: %p, *other.i: %d) str: %s\n", other.i, *other.i, str);
        if (other.i != nullptr)
        {
            i = other.i;
            other.i = nullptr;
        }
        return *this;
    }

    ~Foo()
    {
        if (!TIME_TEST) printf("Foo::~Foo(this: %p, i: %p, str: %s)\n", this, i, str);
        if (i != nullptr)
        {
            delete i;
            i = nullptr;
        }
    }

    int *i = nullptr;
    const char *str = nullptr;
};


// lvalue -> left value
// rvalue -> right value
//       prvalue -> pure right value | a value without a name (a literal or a return value)
//       xrvalue -> eXpiring value

void FuncByValue(Foo other); // value semantics -> copy
void FuncByRef(Foo &other);  // reference semantics

int return_prvalue() { return 42; }

int main()
{
    42; // pure rvalue
    int i = 42; // prvalue
    int j = return_prvalue();
    int cnt = 1;
    if (TIME_TEST) cnt = 100000000;
    while (cnt--) {
        Foo f1("f1");
        {
            //Foo f2("f2");
            //f2.i = new int(42);

            //f1 = f2;
            //f1 = std::move(f2); // expiring value | xvalue
            //f1 = static_cast<struct Foo &&>(f2); // std::move by hand


            f1 = Foo(14, "Foo(14)"); // prvalue. Instead of Foo f2("f2"); f2.i = new int(42);
        }
    }
}
