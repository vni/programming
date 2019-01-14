#include <iostream>

//functors -> function object
//function

struct AddFunctor
{
    int operator()(int x, int y) const
    {
        return x + y;
    }
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

    AddFunctor af;
    std::cout << "\n\nAddFunctor af;\n";
    std::cout << "af(i, 3): " << af(i, 3) << "\n";
    std::cout << "af(j, -8): " << af(j, -8) << "\n";
}
