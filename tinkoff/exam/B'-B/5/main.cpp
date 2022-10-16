#include <iostream>
#include <vector>

enum class color {
    not_filled = 0u,
    a = 1u,
    b = 2u,
    c = 3u,
    d = 4u,
    e = 5u
};

void PrintDesk(const std::vector<std::vector<color>> &desk, std::uint32_t n, std::uint32_t m) {
    for (std::uint32_t y = 0; y < m; ++y) {
        for (std::uint32_t x = 0; x < n - 1; ++x) std::cout << static_cast<std::uint32_t>(desk[y][x]) << ' ';
        std::cout << static_cast<std::uint32_t>(desk[y][n - 1]) << std::endl;
    }
}

bool IsOk(const std::vector<std::vector<color>> &desk, std::uint32_t n, std::uint32_t m) {
    for (std::uint32_t y = 1; y < m - 1; ++y) {
        for (std::uint32_t x = 1; x < n - 1; ++x) {
            bool colors[] = {false, false, false, false, false};
            for (std::uint32_t l_y = y - 1; l_y <= y + 1; ++l_y)
                for (std::uint32_t l_x = x - 1; l_x <= x + 1; ++l_x)
                    if (desk[l_y][l_x] == color::not_filled) return false;
            colors[static_cast<std::uint32_t>(desk[y - 1][x]) - 1] = true;
            colors[static_cast<std::uint32_t>(desk[y][x - 1]) - 1] = true;
            colors[static_cast<std::uint32_t>(desk[y][x]) - 1] = true;
            colors[static_cast<std::uint32_t>(desk[y][x + 1]) - 1] = true;
            colors[static_cast<std::uint32_t>(desk[y + 1][x]) - 1] = true;
            for (const bool &col: colors) if (!col) return false;
            for (auto &&color: colors) color = false;
            for (std::uint32_t l_y = y - 1; l_y <= y + 1; ++l_y)
                for (std::uint32_t l_x = x - 1; l_x <= x + 1; ++l_x)
                    if (l_x != x || l_y != y)
                        colors[static_cast<std::uint32_t>(desk[l_y][l_x]) - 1] = true;
            std::uint32_t false_cnt = 0;
            for (const bool &col: colors) if (!col) ++false_cnt;
            if (false_cnt < 1) return false;
        }
    }
    return true;
}

int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::vector<color>> desk(m, std::vector<color>(n, color::not_filled));
    std::vector<color> numbers_pos{static_cast<color>(2u), static_cast<color>(0u), static_cast<color>(3u),
                                   static_cast<color>(1u), static_cast<color>(4u)};
    for (std::uint32_t y = 0; y < m; ++y)
        desk[y][0] = numbers_pos[y % 5];
    if (n > 1)
        for (std::uint32_t y = 0; y < m; ++y)
            for (std::uint32_t x = 1; x < n; ++x)
                desk[y][x] = static_cast<color>((static_cast<std::uint32_t>(desk[y][x - 1]) + 1) % 5);
    for (std::uint32_t y = 0; y < m; ++y)
        for (std::uint32_t x = 0; x < n; ++x)
            desk[y][x] = static_cast<color>(static_cast<std::uint32_t>(desk[y][x]) + 1);
//    auto is_ok = IsOk(desk, n, m);
    PrintDesk(desk, n, m);
//        std::cout << IsOk(desk, n, m);
//        return 0;
    return 0;
}
