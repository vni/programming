// https://www.learncpp.com/cpp-tutorial/15-4-stdmove/

#include <iostream>
#include <vector>
#include <string>

int main(int argc, char *argv[])
{
    bool use_move = false;
    auto cnt = 1;
    if (argc == 2 && argv[1][0] == '+') {
        cnt = 1'000'000'0;
    } else if (argc == 3 && argv[1][0] == '+' && argv[2][0] == 'm') {
        use_move = true;
        std::cout << "++ use_move ++\n";
    }
    //-----------------------------------------------------

    std::vector<std::string> vec;

    std::string x = "goodbye the cruel one! What is your last wish?";

    std::cout << "x: " << x << "\n";

    while (cnt--)
    {
        if (use_move)
            vec.push_back(std::move(x));
        else {
            vec.push_back(x);
        }
    }

    std::cout << "x: " << x << "\n";
    std::cout << "vec.size(): " << vec.size() << "\n";
}
