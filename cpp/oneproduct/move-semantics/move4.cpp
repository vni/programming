#include <vector>
#include <utility>

using namespace std;

#if 0
struct Foo {
    int *i = nullptr;
};
#endif

int main() {
    int cnt = 10000000;
    while (cnt--) {
        std::vector<int> v1;
        {
            std::vector<int> v2 = { 1,2,3,4,5 };
            //v1 = v2;
            v1 = std::move(v2);
        }
    }
}
