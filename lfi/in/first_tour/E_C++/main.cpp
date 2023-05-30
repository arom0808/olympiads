#include <iostream>

int main() {
    std::uint32_t g, y, r, n;
    std::cin >> g >> y >> r >> n;
    std::uint32_t full_cycle_time = g + y + r;
    std::int32_t min_start_k = -static_cast<std::int32_t>(full_cycle_time) + 1, max_start_k =
            static_cast<std::int32_t>(full_cycle_time) - 1;
    std::uint32_t t;
    char c;
    for (std::uint32_t i = 0; i < n; ++i) {
        std::cin >> t >> c;
//        if (t < full_cycle_time) {
//
//        }
        t = t % full_cycle_time;
        if (c == 'y') {
            now_min_start_k = static_cast<std::int32_t>(t) - g - y + 1;
            now_max_start_k = static_cast<std::int32_t>(t) - g;
        }
    }
    return 0;
}
