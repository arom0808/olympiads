#include <iostream>
#include <vector>
#include <fstream>

using Row = std::vector<std::pair<std::uint32_t, bool>>;
using Field = std::vector<Row>;

inline std::uint32_t GetFromTop(const Field &field, const std::uint32_t &x, const std::uint32_t &y) {
    if (y == 0) return 0;
    return field[y - 1][x].first;
}

inline std::uint32_t GetFromLeft(const Field &field, const std::uint32_t &x, const std::uint32_t &y) {
    if (x == 0) return 0;
    return field[y][x - 1].first;
}

void UpdateCell(Field &field, const std::uint32_t &x, const std::uint32_t &y) {
    std::uint32_t from_top = GetFromTop(field, x, y);
    std::uint32_t from_left = GetFromLeft(field, x, y);
    if (from_top > from_left) {
        field[y][x].first += from_top;
        field[y][x].second = true;
    } else {
        field[y][x].first += from_left;
        field[y][x].second = false;
    }
}

int main() {
    std::uint32_t m, n;
    std::ifstream bug_in("bug2.in");
    bug_in >> n >> m;
    Field field(n, Row(m, {0, false}));
    for (auto &&row: field) for (auto &&value: row) bug_in >> value.first;
    const auto raw_field = field;
    for (std::uint32_t i = 0; i < std::min(m, n); ++i) {
        UpdateCell(field, i, i);
        for (std::uint32_t x = i + 1, y = i; x < m; ++x) UpdateCell(field, x, y);
        for (std::uint32_t x = i, y = i + 1; y < n; ++y) UpdateCell(field, x, y);
    }
    std::vector<bool> path;
    std::uint32_t now_x = m - 1, now_y = n - 1;
    std::uint64_t sum = raw_field[0][0].first;
    while (now_x != 0 || now_y != 0) {
        sum += raw_field[now_y][now_x].first;
        path.push_back(field[now_y][now_x].second);
        if (field[now_y][now_x].second) --now_y;
        else --now_x;
    }
    std::cout << "sum: " << sum << std::endl;
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        if (*it) std::cout << "D";
        else std::cout << "R";
    }
    return 0;
}
