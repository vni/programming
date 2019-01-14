// perfect forwarding

#include <vector>

using namespace std;

int main()
{
    vector<int> v1;
    {
        vector<int> v2 = { 1,2,3,4,5 };
        v1 = move(v2);
    }
}
