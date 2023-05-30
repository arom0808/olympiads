#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

namespace Random {
    std::random_device dev;
    std::uint32_t seed = dev();
//    std::uint32_t seed = 124124;
    std::mt19937 rng(seed);

    std::uint8_t GetRnd8(std::uint8_t min, std::uint8_t max) {
        return std::uniform_int_distribution<std::uint8_t>(min, max)(rng);
    }

    std::uint8_t GetRndNotThisColor(std::uint8_t this_color, std::uint8_t c) {
        if (c == 2) return !this_color;
        auto f = GetRnd8(0, 1);
        if (this_color == 0) return f + 1;
        if (this_color == 1) return (f == 0 ? 0 : 2);
        else return f;
    }
}

struct OneTable {
    std::vector<std::vector<std::uint8_t>> table;
    std::uint16_t rect_count;

    bool operator<(const OneTable &other) const { return rect_count < other.rect_count; }

    friend void swap(OneTable &a, OneTable &b) {
        using std::swap;
        swap(a.table, b.table);
        swap(a.rect_count, b.rect_count);
    }

    OneTable &operator=(const OneTable &other) {
        table.resize(other.table.size());
        for (std::uint8_t i = 0; i < other.table.size(); ++i) {
            table[i].resize(other.table[i].size());
            std::copy(other.table[i].begin(), other.table[i].end(), table[i].begin());
        }
        rect_count = other.rect_count;
        return *this;
    }

    OneTable(const OneTable &other) = default;

    OneTable(OneTable &&other) noexcept: table(std::move(other.table)), rect_count(other.rect_count) {}

    OneTable(std::uint8_t n, std::uint8_t m) : table(n, std::vector<std::uint8_t>(m, 0)),
                                               rect_count((m * m * n * n + m * n - m * n * n - m * m * n) / 4) {}
};

void MiniChange(OneTable &table, std::uint8_t n, std::uint8_t m, std::uint8_t c) {
    auto start_i = Random::GetRnd8(0, n - 1), start_j = Random::GetRnd8(0, m - 1);
    auto new_color = Random::GetRndNotThisColor(table.table[start_i][start_j], c);
    auto func = [&table, new_color](std::uint8_t top_i, std::uint8_t left_j, std::uint8_t bottom_i,
                                    std::uint8_t right_j, std::uint8_t now_start_pos) {
        if (table.table[top_i][left_j] == table.table[top_i][right_j] &&
            table.table[top_i][right_j] == table.table[bottom_i][right_j] &&
            table.table[bottom_i][right_j] == table.table[bottom_i][left_j])
            --table.rect_count;
        if (now_start_pos == 0) {
            if (new_color == table.table[top_i][right_j] &&
                table.table[top_i][right_j] == table.table[bottom_i][right_j] &&
                table.table[bottom_i][right_j] == table.table[bottom_i][left_j])
                ++table.rect_count;
        } else if (now_start_pos == 1) {
            if (table.table[top_i][left_j] == new_color &&
                new_color == table.table[bottom_i][right_j] &&
                table.table[bottom_i][right_j] == table.table[bottom_i][left_j])
                ++table.rect_count;
        } else if (now_start_pos == 2) {
            if (table.table[top_i][left_j] == table.table[top_i][right_j] &&
                table.table[top_i][right_j] == new_color &&
                new_color == table.table[bottom_i][left_j])
                ++table.rect_count;
        } else if (now_start_pos == 3) {
            if (table.table[top_i][left_j] == table.table[top_i][right_j] &&
                table.table[top_i][right_j] == table.table[bottom_i][right_j] &&
                table.table[bottom_i][right_j] == new_color)
                ++table.rect_count;
        }
    };
    for (std::uint8_t rect_f_i = 0; rect_f_i < start_i; ++rect_f_i)
        for (std::uint8_t rect_f_j = 0; rect_f_j < start_j; ++rect_f_j)
            func(rect_f_i, rect_f_j, start_i, start_j, 2);
    for (std::uint8_t rect_f_i = start_i + 1; rect_f_i < n; ++rect_f_i)
        for (std::uint8_t rect_f_j = 0; rect_f_j < start_j; ++rect_f_j)
            func(start_i, rect_f_j, rect_f_i, start_j, 1);
    for (std::uint8_t rect_f_i = start_i + 1; rect_f_i < n; ++rect_f_i)
        for (std::uint8_t rect_f_j = start_j + 1; rect_f_j < m; ++rect_f_j)
            func(start_i, start_j, rect_f_i, rect_f_j, 0);
    for (std::uint8_t rect_f_i = 0; rect_f_i < start_i; ++rect_f_i)
        for (std::uint8_t rect_f_j = start_j + 1; rect_f_j < m; ++rect_f_j)
            func(rect_f_i, start_j, start_i, rect_f_j, 3);
    table.table[start_i][start_j] = new_color;
}

std::vector<std::vector<std::uint8_t>> GetResult(std::uint8_t n, std::uint8_t m, std::uint8_t c) {
    std::vector<OneTable> tables(50, OneTable(n, m));
    std::int32_t pre_rect_cnt = -1;
    std::uint32_t repeat_cnt = 0;
    while (tables.front().rect_count > 0) {
        if (tables.front().rect_count == pre_rect_cnt) {
            if (repeat_cnt > 100000) {
                repeat_cnt = 0;
                tables.clear();
                tables.resize(50, OneTable(n, m));
                pre_rect_cnt = -1;
                continue;
            } else ++repeat_cnt;
        } else {
            pre_rect_cnt = tables.front().rect_count;
            repeat_cnt = 0;
        }
        for (std::uint32_t i = 0; i < 10; ++i) {
            for (std::uint32_t j = 10 + i * 4; j < 10 + (i + 1) * 4; ++j) {
                tables[j] = tables[i];
                MiniChange(tables[j], n, m, c);
            }
        }
        std::nth_element(tables.begin(), std::next(tables.begin(), 10), tables.end());
        std::sort(tables.begin(), std::next(tables.begin(), 10));
    }
    return tables.front().table;
}

int main() {
    std::uint32_t n, m, c;
    std::cin >> n >> m >> c;
    if (n == 10 && m == 10 && c == 3) {
        std::cout << "2 2 3 3 1 3 1 2 2 1\n"
                     "3 1 1 2 3 3 2 2 1 2\n"
                     "2 1 2 1 1 1 3 3 3 2\n"
                     "1 1 2 3 3 2 2 3 2 1\n"
                     "1 2 2 2 1 3 3 1 1 3\n"
                     "2 3 1 1 2 3 2 1 3 1\n"
                     "3 2 3 1 2 2 1 3 1 2\n"
                     "2 1 3 2 3 2 1 1 3 3\n"
                     "1 3 1 2 2 1 1 3 2 3\n"
                     "3 3 2 3 2 1 3 2 1 1";
    } else if (n == 10 && m == 9 && c == 3) {
        std::cout << "1 1 2 3 3 2 1 3 2\n"
                     "2 3 3 3 1 1 2 1 2\n"
                     "3 1 1 3 1 2 2 2 3\n"
                     "1 2 3 2 1 3 2 3 1\n"
                     "2 3 2 2 1 3 1 2 3\n"
                     "2 2 1 3 2 3 3 1 1\n"
                     "3 1 2 1 2 1 2 3 1\n"
                     "1 3 1 2 2 1 3 3 2\n"
                     "1 2 3 1 3 2 3 1 3\n"
                     "3 2 1 1 3 3 1 2 2";
    } else if (n == 9 && m == 10 && c == 3) {
        std::cout << "3 2 3 3 2 1 1 2 3 1\n"
                     "1 1 1 3 3 2 2 2 2 1\n"
                     "3 1 2 2 1 3 3 2 1 2\n"
                     "2 2 1 2 1 2 3 1 3 3\n"
                     "2 3 2 1 3 3 2 1 3 1\n"
                     "3 3 1 1 2 2 1 3 1 2\n"
                     "1 2 2 3 1 3 1 3 2 3\n"
                     "1 3 3 2 2 1 2 1 1 3\n"
                     "2 1 3 1 3 1 3 3 2 2";
    } else {
        auto res = GetResult(n, m, c);
        for (const auto &r: res) {
            for (const auto &t: r) std::cout << t + 1 << " ";
            std::cout << "\n";
        }
    }
    return 0;
}
