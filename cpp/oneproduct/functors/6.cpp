#include <iostream>
#include <vector>
#include <algorithm>

struct Dog
{
    Dog(int age)
        : m_age(age)
    {}

    bool operator<(Dog const &other) const
    {
        return m_age < other.m_age;
    }

    void print() const
    {
        std::cout << "age: " << m_age << "\n";
    }

    private:
    int m_age;
};

int main() {
    std::vector<Dog> v = { Dog(3), Dog(1), Dog(5), Dog(2), Dog(4) };
    std::cout << "vector<Dog>:\n";
    for(auto &d: v) d.print();
    sort(std::begin(v), std::end(v));

    std::cout << "\nsorted vector<Dog>:\n";
    for(auto &d: v) d.print();
}
