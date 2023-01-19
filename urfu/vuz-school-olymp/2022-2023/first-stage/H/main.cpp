#include <iostream>
#include <vector>
#include <algorithm>

struct ColumnSegment {
    std::uint32_t x;
    std::uint32_t y1, y2;
    std::uint32_t length;

    ColumnSegment(std::uint32_t x, std::uint32_t y1, std::uint32_t y2, std::uint32_t length)
            : x(x), y1(y1), y2(y2), length(length) {}
};

std::uint32_t M, N;

bool IsSOk(const std::vector<std::vector<bool>> &table, const std::uint32_t x, const std::uint32_t min_y,
           const std::uint32_t mid_y, const std::uint32_t max_y) {
    if (M < x + max_y - mid_y - 1) return false;
    if (M < x + mid_y + 1 - min_y) return false;
    for (std::uint32_t length = max_y - mid_y - 1, cur_y = max_y - 1; length > 1; --length, --cur_y) {
        for (std::uint32_t i = x; i < x + length; ++i) if (!table[cur_y][i]) return false;
    }
    for (std::uint32_t length = mid_y + 1 - min_y, cur_y = mid_y; length > 1; --length, --cur_y) {
        for (std::uint32_t i = x; i < x + length; ++i) if (!table[cur_y][i]) return false;
    }
    return true;
}

int main() {
    std::cin >> N >> M;
    std::vector<std::vector<bool>> table(N, std::vector<bool>(M));
    char buf;
    for (auto &i: table) {
        for (auto &&j: i) {
            std::cin >> buf;
            j = buf == '#';
        }
    }
    std::vector<ColumnSegment> column_segments;
    column_segments.reserve(M * N);
    for (std::uint32_t j = 0; j < M; ++j) {
        std::uint32_t start_y;
        bool is_line_started = false;
        for (std::uint32_t i = 0; i < N; ++i) {
            if (table[i][j]) {
                if (!is_line_started) {
                    start_y = i;
                    is_line_started = true;
                }
            } else {
                if (is_line_started) {
                    is_line_started = false;
                    column_segments.emplace_back(j, start_y, i, i - start_y);
                }
            }
        }
        if (is_line_started) {
            is_line_started = false;
            column_segments.emplace_back(j, start_y, N, N - start_y);
        }
    }
    auto cmp_column_segments = [](const ColumnSegment &a, const ColumnSegment &b) { return a.length >= b.length; };
    std::sort(column_segments.begin(), column_segments.end(), cmp_column_segments);
    std::uint32_t max_result = 0;
    for (const auto &column_segment: column_segments) {
        for (std::uint32_t min_y = column_segment.y1; min_y < column_segment.y2; ++min_y) {
            for (std::uint32_t max_y = min_y + 1; max_y <= column_segment.y2; ++max_y) {
                if (max_y - min_y < 4) continue;
                for (std::uint32_t mid_y = min_y + 1; mid_y < max_y - 2; ++mid_y) {
                    if (IsSOk(table, column_segment.x, min_y, mid_y, max_y)) {
                        std::uint32_t cur_result = (max_y - mid_y) * (max_y - mid_y - 1) / 2 +
                                                   (mid_y + 1 - min_y) * (mid_y + 2 - min_y) / 2;
                        if (cur_result > max_result) max_result = cur_result;
                    }
                }
            }
        }
    }
    std::cout << max_result;
    return 0;
}
