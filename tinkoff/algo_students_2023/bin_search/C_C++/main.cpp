#include <iostream>
#include <vector>
#include <functional>

std::uint32_t FindNum(std::uint32_t l, std::uint32_t r, const std::function<bool(std::uint32_t num)> &check_f) {
    if (l > r) std::swap(l, r);
    while (r != l) {
        std::uint32_t mid = (l + r) / 2 + ((l + r) % 2);
        if (check_f(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

int main() {
    std::string temp_str;
    std::getline(std::cin, temp_str);
    std::uint32_t n = std::stoi(temp_str);
    auto check_f = [&temp_str](std::uint32_t num) {
        std::cout << num << std::endl;
        std::flush(std::cout);
        std::getline(std::cin, temp_str);
        return temp_str == ">=";
    };
    std::uint32_t result = FindNum(1, n, check_f);
    std::cout << "! " << result << std::endl;
    return 0;
}
