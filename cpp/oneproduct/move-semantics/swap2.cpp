// https://www.learncpp.com/cpp-tutorial/15-4-stdmove/

#include <iostream>

template<class T>
void swap_copy(T& a, T& b)
{
    //T t{a};
    T t(a);
    a = b;
    b = t;
}

template<class T>
void swap_move(T& a, T& b)
{
    //T t{a};
    T t(static_cast<T&&>(a));
    a = static_cast<T&&>(b);
    b = static_cast<T&&>(t);
}

int main(int argc, char *argv[])
{
    bool use_move = false;
    auto cnt = 1;
    if (argc == 2 && argv[1][0] == '+') {
        cnt = 1'000'000'001;
    } else if (argc == 3 && argv[1][0] == '+' && argv[2][0] == 'm') {
        use_move = true;
        std::cout << "++ use_move ++\n";
    }
    //-----------------------------------------------------

    std::string x = "hello world";
    std::string y = "goodbye the cruel one!";

    std::cout << "x: " << x << "\n";
    std::cout << "y: " << y << "\n";

    while (cnt--)
    {
        if (use_move)
            swap_move(x, y);
        else
            swap_copy(x, y);
    }

    std::cout << "x: " << x << "\n";
    std::cout << "y: " << y << "\n";
}
