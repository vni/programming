#include <iostream>
#include <vector>
#include <algorithm>

struct Dog
{
    Dog(int age, int weight)
        : m_age(age)
        , m_weight(weight)
    {}

    bool operator<(Dog const &other) const
    {
        return m_age < other.m_age;
    }

    void print() const
    {
        std::cout << "age: " << m_age << ", weight: " << m_weight << "\n";
    }

    //private:
    int m_age;
    int m_weight;
};

struct SortByWeightFunctor
{
    bool operator()(const Dog &lhs, const Dog &rhs) const {
        return lhs.m_weight < rhs.m_weight;
    }
};

int main() {
    std::vector<Dog> v = { Dog(3, 20), Dog(1, 5), Dog(5, 2), Dog(2, 10), Dog(4, 4) };

    std::cout << "vector<Dog>:\n";
    for(auto &d: v) d.print();

    std::cout << "\n\nsort by default, by age:\n";
    sort(std::begin(v), std::end(v));
    for(auto &d: v) d.print();

    std::cout << "\n\nsort with SortByWeightFunctor:\n";
    sort(std::begin(v), std::end(v), SortByWeightFunctor());
    for(auto &d: v) d.print();
}
