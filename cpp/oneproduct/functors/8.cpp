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

    bool operator==(int age) const {
        return m_age == age;
    }

    void print() const
    {
        std::cout << "age: " << m_age << ", weight: " << m_weight << "\n";
    }

    //private:
    int m_age;
    int m_weight;
};

struct FindByWeightFunctor
{
    FindByWeightFunctor(int w) : m_weight(w) {}
    bool operator()(const Dog &x) {
        return x.m_weight == m_weight;
    }

    private: int m_weight;
};

#if 0
// this is not used and not needed.
struct FindByAgeFunctor
{
    FindByAgeFunctor(int a) : m_age(a) {}
    bool operator()(const Dog &x) {
        return x.m_age == m_age;
    }

    private: int m_age;
};
#endif

int main() {
    std::vector<Dog> v = { Dog(3, 8), Dog(1, 5), Dog(5, 2), Dog(2, 10), Dog(4, 4) };

    std::cout << "vector<Dog>:\n";
    for(auto &d: v) d.print();

    std::cout << "\n";
    auto f_weight = find_if(std::begin(v), std::end(v), FindByWeightFunctor(4));
    std::cout << "Found by weight: "; f_weight->print();

    //auto f_age = find_if(v.begin(), v.end(), FindByAgeFunctor(5));
    auto f_age = find_if(v.begin(), v.end(), [](const Dog &d) -> bool { return d == 5; });
    if (f_age != v.end()) {
        std::cout << "Found by age: ";
        f_age->print();
    } else {
        std::cout << "Can't find the dog by age 5\n";
    }
    auto f_age2 = find(v.begin(), v.end(), 13);
    if (f_age2 != v.end()) {
        std::cout << "Found by age2: ";
        f_age2->print();
    } else {
        std::cout << "Can't find the dog by age 13\n";
    }
}
