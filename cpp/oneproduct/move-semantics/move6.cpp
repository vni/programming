#include <stdio.h>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> a = { 1, 2, 3, 4, 5, 6 };
    std::vector<int> b;

    printf("a.size() %ld\n", a.size());
    printf("b.size() %ld\n", b.size());

    printf("b = std::move(a) =======\n");
    b = std::move(a);

    printf("a.size() %ld\n", a.size());
    printf("b.size() %ld\n", b.size());
}
