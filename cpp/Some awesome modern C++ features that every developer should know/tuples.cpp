// https://www.freecodecamp.org/news/some-awesome-modern-c-features-that-every-developer-should-know-5e3bf6f79a3c/

#include <iostream>
#include <tuple>

int main()
{
    auto user_info = std::make_tuple("M", "Chowdhury", 25);

    auto first_name1 = std::get<0>(user_info);
    auto last_name1 = std::get<1>(user_info);
    auto age1 = std::get<2>(user_info);
    std::cout << "first_name1: " << first_name1 << "\n"
              << "last_name1: " << last_name1 << "\n"
              << "age1: " << age1 << "\n\n";

    std::string first_name2, last_name2; int age2;
    std::tie(first_name2, last_name2, age2) = user_info;
    std::cout << "first_name2: " << first_name2 << "\n"
              << "last_name2: " << last_name2 << "\n"
              << "age2: " << age2 << "\n\n";

    auto [first_name3, last_name3, age3] = user_info;
    std::cout << "first_name3: " << first_name3 << "\n"
              << "last_name3: " << last_name3 << "\n"
              << "age3: " << age3 << "\n\n";
}
