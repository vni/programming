#include <iostream>

//functors -> function object
//function

struct AddFunctor
{
    explicit AddFunctor(int x) : m_x(x) {}
    int operator()(int y) const
    {
        return m_x + y;
    }
    int operator()(int x, int y) const
    {
        return x + y;
    }

    private:
    int m_x;
};
int Add(int x, int y)
{
    return x + y;
}

int main() {
    int i = 13;
    int j = 26;
    std::cout << "i: " << i << ", j: " << j << "\n\n";

    std::cout << "Add(i, 3): " << Add(i, 3) << "\n";
    std::cout << "Add(j, -8): " << Add(j, -8) << "\n";

    //AddFunctor af = 11; // do not work due to an 'explicit' keyword
    AddFunctor af(11);
    std::cout << "\n\n//AddFunctor af = 11; // doesn't compile due to an 'explicit' keyword\n";
    std::cout << "AddFunctor af(11);\n";
    std::cout << "af(i, 3): " << af(i, 3) << "\n";
    std::cout << "af(j, -8): " << af(j, -8) << "\n";
    std::cout << "af(3): " << af(3) << "\n";
    std::cout << "af(-8): " << af(-8) << "\n";
}
