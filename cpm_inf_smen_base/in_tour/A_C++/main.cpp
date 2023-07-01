#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<bool> taps(20);
    bool temp_bool;
    for (auto &&tap: taps) {
        std::cin >> temp_bool;
        tap = temp_bool;
    }
    std::uint32_t min_res = 100;
    for (auto f_it = taps.begin(); f_it != taps.end(); ++f_it) {
        if (!*f_it) continue;
        auto s_it = std::find(std::next(f_it), taps.end(), false);
        if (s_it != taps.end() && std::distance(f_it, s_it) < min_res) min_res = std::distance(f_it, s_it);
    }
    if (min_res == 100) std::cout << -1;
    else std::cout << min_res - 1;
    return 0;
}
