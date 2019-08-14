// https://www.freecodecamp.org/news/some-awesome-modern-c-features-that-every-developer-should-know-5e3bf6f79a3c/

#include <map>
#include <vector>
#include <iostream>

void populate(auto &data)
{
    data.insert({"a", {1,4}});
    data.insert({"b", {3,1}});
    data.insert({"c", {2,3}});
}

auto merge(auto data, auto upcoming_data)
{
    auto result = data;
    //for (auto &it: upcoming_data) {
    for (auto it: upcoming_data) {
        result.insert(it);
    }
    return result;
}

int main()
{
    std::map<std::string, std::pair<int, int>> data;
    populate(data);

    std::map<std::string, std::pair<int, int>> upcoming_data;
    upcoming_data.insert({"d", {5,3}});

    auto final_data = merge(data, upcoming_data);

    //for (auto &itr: final_data) {
    for (auto itr: final_data) {
        //auto &[v1, v2] = itr.second;
        auto [v1, v2] = itr.second;
        std::cout << itr.first << " " << v1 << " " << v2 << std::endl;
    }
}
