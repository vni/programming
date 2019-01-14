// https://www.youtube.com/watch?v=7-nHdQjSRe0
// C++ Templates - Part 4 : Curiously Recurring Template Pattern

#include <iostream>

struct Shape
{
    virtual ~Shape() = default;
};

struct Square : public Shape
{
    Square *Clone() { return new Square(*this); }

    int x = 1;
};

struct Rectangle : public Shape
{
    Rectangle *Clone() { return new Rectangle(*this); }

    int x = 1;
    int y = 2;
};

int main()
{
    Square x;
    std::cout << "&x: " << &x << ".  x.x: " << x.x << '\n';

    auto y = x.Clone(); // y is Square*
    std::cout << "y: " << y << ".  y->x: " << y->x << '\n';

    auto *z = y->Clone();
    std::cout << "z: " << z << ".  z->x: " << z->x << '\n';

    std::cout << '\n';
    Rectangle rect;
    std::cout << "&rect: " << &rect << ".  rect: { " << rect.x << ", " << rect.y << " }\n";
    auto r2 = rect.Clone();
    std::cout << "r2: " << r2 << ".  r2: { " << r2->x << ", " << r2->y << " }\n";
    auto r3 = rect.Clone();
    std::cout << "r3: " << r3 << ".  r3: { " << r3->x << ", " << r3->y << " }\n";
}
