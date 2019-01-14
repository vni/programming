// https://pagefault.blog/2018/03/01/common-misconception-with-cpp-move-semantics/?blogsub=confirming#blog_subscription-5

#include <iostream>
#include <vector>
#include <algorithm>

class Data
{
    public:
        Data(const std::vector<int>&data) : m_vec(data) {
            std::cout << "[lvalue-ref constructor]\n";
        }

        Data(std::vector<int>&&data) : m_vec(std::move(data)) {
            std::cout << "[rvalue-ref constructor]\n";
        }
        std::size_t size() const { return m_vec.size(); }

    private:
        std::vector<int> m_vec;
};

int main()
{
    std::vector<int>a = { 1,2,3,4,5 };
    //auto d = Data(a);
    //auto d = Data(std::move(a));
    auto d = Data(static_cast<std::vector<int>&&>(a));

    auto c = Data({1,2,3,4});

    std::cout << "a: " << a.size() << "\n";
    std::cout << "d: " << d.size() << "\n";
    std::cout << "c: " << c.size() << "\n";
}
