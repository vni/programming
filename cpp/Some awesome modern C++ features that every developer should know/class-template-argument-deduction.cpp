// https://www.freecodecamp.org/news/some-awesome-modern-c-features-that-every-developer-should-know-5e3bf6f79a3c/

#include <tuple>
#include <string>
#include <iostream>

int main()
{
    std::pair<std::string, int> user1 = { "M", 25 };
    std::cout << "user1: {" << user1.first << ", " << user1.second << "}\n";

    std::pair user2 = { "J", 13 }; // C++17
    std::cout << "user2: {" << user2.first << ", " << user2.second << "}\n";

    std::tuple<std::string, std::string, int> user3("A", "Chy", 44);
    std::cout << "user3: {" << std::get<0>(user3) << ", "
                            << std::get<1>(user3) << ", "
                            << std::get<2>(user3) << "}\n";

    std::tuple user4("Chuck", "Shuldener", 38); // C++17
    std::cout << "user4: {" << std::get<0>(user4) << ", "
                            << std::get<1>(user4) << ", "
                            << std::get<2>(user4) << "}\n";
}
