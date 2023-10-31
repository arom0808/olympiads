#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

const std::int32_t sqrt_coord = 1e3;
const std::int32_t zip_table_size = 1e6 / sqrt_coord + 1;

struct Point {
    std::int32_t id, y;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::int32_t n;
    std::cin >> n;
    std::vector<std::vector<Point>> table(zip_table_size);
    for (std::int32_t i = 0, x, y; i < n; ++i) {
        std::cin >> x >> y;
        table[x / sqrt_coord].emplace_back(i, y);
    }
    bool dir = false;
    for (auto it1 = table.begin(); it1 != table.end(); ++it1, dir = !dir) {
        std::sort(it1->begin(), it1->end(),
                  [dir](const Point &a, const Point &b) { return (dir ? a.y < b.y : a.y > b.y); });
        for (auto &it2: *it1) std::cout << it2.id + 1 << " ";
    }
    return 0;
}
