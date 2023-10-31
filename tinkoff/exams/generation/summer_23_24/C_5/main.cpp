#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::string str;
    std::cin >> str;
    std::vector<std::string> vec;
    vec.reserve(str.size());
    for (std::uint32_t i = 0; i < str.size(); ++i) {
        if (i + 1 < str.size() && str[i] == str[i + 1])
            vec.emplace_back(std::move(str.substr(i, 2)));
        if (i + 2 < str.size() && str[i] == str[i + 2])
            vec.emplace_back(std::move(str.substr(i, 3)));
    }
    std::sort(vec.begin(), vec.end(), [](const std::string &a, const std::string &b) { return a.size() < b.size(); });
    auto _it = std::find_if(vec.begin(), vec.end(), [](const std::string &a) { return a.size() == 3; });
    auto it1 = std::min_element(vec.begin(), _it);
    auto it2 = std::min_element(_it, vec.end());
    if (it1 != _it) std::cout << *it1;
    else if (it2 != vec.end()) std::cout << *it2;
    else std::cout << -1;
    return 0;
}
