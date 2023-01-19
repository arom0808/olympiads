#include <iostream>
#include <vector>

struct ExtremePoints {
    std::int32_t top_y, bottom_y, left_x, right_x;

    explicit ExtremePoints(std::int32_t top_y = -1, std::int32_t bottom_y = -1, std::int32_t left_x = -1,
                           std::int32_t right_x = -1) : top_y(top_y), bottom_y(bottom_y), left_x(left_x),
                                                        right_x(right_x) {}
};

ExtremePoints
GetExtremePoints(const std::vector<std::vector<bool>> &display,
                 ExtremePoints outer_extreme_points = ExtremePoints(), bool req_value = true) {
    if (outer_extreme_points.top_y < 0 || outer_extreme_points.bottom_y < 0 || outer_extreme_points.left_x < 0 ||
        outer_extreme_points.right_x < 0) {
        outer_extreme_points.top_y = 0;
        outer_extreme_points.bottom_y = display.size() - 1;
        outer_extreme_points.left_x = 0;
        outer_extreme_points.right_x = display.size() - 1;
    }
    std::int32_t top_y = -1, bottom_y = -1, left_x = -1, right_x = -1;
    for (std::uint32_t y = outer_extreme_points.top_y; y <= outer_extreme_points.bottom_y; ++y) {
        for (std::uint32_t x = outer_extreme_points.left_x; x <= outer_extreme_points.right_x; ++x) {
            if (display[y][x] == req_value) {
                if (top_y == -1) top_y = y;
                if (left_x == -1 || x < left_x) left_x = x;
                if (bottom_y == -1 || y > bottom_y) bottom_y = y;
                if (right_x == -1 || x > right_x) right_x = x;
            }
        }
    }
    return ExtremePoints(top_y, bottom_y, left_x, right_x);
}

std::int32_t FindFirstInLine(const std::vector<std::vector<bool>> &display,
                             std::uint32_t line_id, bool req_value, std::uint32_t first_x = 0,
                             std::int32_t last_x = -1) {
    if (last_x == -1) last_x = display.size() - 1;
    for (std::uint32_t x = first_x; x <= last_x; ++x) if (display[line_id][x] == req_value) return x;
    return -1;
}

std::int32_t FindLastInLine(const std::vector<std::vector<bool>> &display,
                            std::uint32_t line_id, bool req_value, std::uint32_t first_x = 0,
                            std::int32_t last_x = -1) {
    if (last_x == -1) last_x = display.size() - 1;
    std::uint32_t x = last_x;
    while (true) {
        if (display[line_id][x] == req_value) return x;
        if (x == 0) break;
        --x;
    }
    return -1;
}

std::int32_t FindFirstInColumn(const std::vector<std::vector<bool>> &display,
                               std::uint32_t column_id, bool req_value, std::uint32_t first_y = 0,
                               std::int32_t last_y = -1) {
    if (last_y == -1) last_y = display.size() - 1;
    for (std::uint32_t y = first_y; y <= last_y; ++y) if (display[y][column_id] == req_value) return y;
    return -1;
}

std::int32_t FindLastInColumn(const std::vector<std::vector<bool>> &display,
                              std::uint32_t column_id, bool req_value, std::uint32_t first_y = 0,
                              std::int32_t last_y = -1) {
    if (last_y == -1) last_y = display.size() - 1;
    std::uint32_t y = last_y;
    while (true) {
        if (display[y][column_id] == req_value) return y;
        if (y == 0) break;
        --y;
    }
    return -1;
}

bool IsFullBlock(const std::vector<std::vector<bool>> &display, const ExtremePoints &extreme_points, bool req_value) {
    for (std::uint32_t y = extreme_points.top_y; y <= extreme_points.bottom_y; ++y)
        for (std::uint32_t x = extreme_points.left_x; x <= extreme_points.right_x; ++x)
            if (display[y][x] != req_value) return false;
    return true;
}

bool IsI(const std::vector<std::vector<bool>> &display, const ExtremePoints &extreme_points) {
    return IsFullBlock(display, extreme_points, true);
}

bool IsO(const std::vector<std::vector<bool>> &display, const ExtremePoints &extreme_points) {
    ExtremePoints inner_points = GetExtremePoints(display, extreme_points, false);
    if (inner_points.left_x <= extreme_points.left_x || inner_points.left_x >= extreme_points.right_x) return false;
    if (inner_points.right_x <= extreme_points.left_x || inner_points.right_x >= extreme_points.right_x) return false;
    if (inner_points.top_y <= extreme_points.top_y || inner_points.top_y >= extreme_points.bottom_y) return false;
    if (inner_points.bottom_y <= extreme_points.top_y || inner_points.bottom_y >= extreme_points.bottom_y) return false;
    if (!IsFullBlock(display, inner_points, false)) return false;
    if (!IsFullBlock(display, ExtremePoints{extreme_points.top_y, inner_points.top_y - 1,
                                            extreme_points.left_x, extreme_points.right_x}, true))
        return false;
    if (!IsFullBlock(display, ExtremePoints{inner_points.top_y, extreme_points.bottom_y,
                                            extreme_points.left_x, inner_points.left_x - 1}, true))
        return false;
    if (!IsFullBlock(display, ExtremePoints{inner_points.bottom_y + 1, extreme_points.bottom_y,
                                            inner_points.left_x, extreme_points.right_x}, true))
        return false;
    if (!IsFullBlock(display, ExtremePoints{inner_points.top_y, inner_points.bottom_y,
                                            inner_points.right_x + 1, extreme_points.right_x}, true))
        return false;
    return true;
}

bool IsC(const std::vector<std::vector<bool>> &display, const ExtremePoints &extreme_points) {
    ExtremePoints inner_points = GetExtremePoints(display, extreme_points, false);
    if (inner_points.left_x <= extreme_points.left_x || inner_points.left_x > extreme_points.right_x) return false;
    if (inner_points.right_x != extreme_points.right_x) return false;
    if (inner_points.top_y <= extreme_points.top_y || inner_points.top_y >= extreme_points.bottom_y) return false;
    if (inner_points.bottom_y <= extreme_points.top_y || inner_points.bottom_y >= extreme_points.bottom_y) return false;
    if (!IsFullBlock(display, inner_points, false)) return false;
    if (!IsFullBlock(display, ExtremePoints{extreme_points.top_y, inner_points.top_y - 1,
                                            extreme_points.left_x, extreme_points.right_x}, true))
        return false;
    if (!IsFullBlock(display, ExtremePoints{inner_points.top_y, extreme_points.bottom_y,
                                            extreme_points.left_x, inner_points.left_x - 1}, true))
        return false;
    if (!IsFullBlock(display, ExtremePoints{inner_points.bottom_y + 1, extreme_points.bottom_y,
                                            inner_points.left_x, extreme_points.right_x}, true))
        return false;
    return true;
}

bool IsL(const std::vector<std::vector<bool>> &display, const ExtremePoints &extreme_points) {
    ExtremePoints inner_points = GetExtremePoints(display, extreme_points, false);
    if (inner_points.left_x <= extreme_points.left_x || inner_points.left_x > extreme_points.right_x) return false;
    if (inner_points.right_x != extreme_points.right_x) return false;
    if (inner_points.top_y != extreme_points.top_y) return false;
    if (inner_points.bottom_y < extreme_points.top_y || inner_points.bottom_y >= extreme_points.bottom_y) return false;
    if (!IsFullBlock(display, inner_points, false)) return false;
    if (!IsFullBlock(display, ExtremePoints{inner_points.top_y, extreme_points.bottom_y,
                                            extreme_points.left_x, inner_points.left_x - 1}, true))
        return false;
    if (!IsFullBlock(display, ExtremePoints{inner_points.bottom_y + 1, extreme_points.bottom_y,
                                            inner_points.left_x, extreme_points.right_x}, true))
        return false;
    return true;
}

bool IsH(const std::vector<std::vector<bool>> &display, const ExtremePoints &extreme_points) {
    std::int32_t first_x = FindFirstInLine(display, extreme_points.top_y, false, extreme_points.left_x,
                                           extreme_points.right_x);
    std::int32_t last_x = FindLastInLine(display, extreme_points.top_y, false, extreme_points.left_x,
                                         extreme_points.right_x);
    if (first_x <= extreme_points.left_x || last_x <= extreme_points.left_x || last_x == extreme_points.right_x)
        return false;
    std::int32_t first_y = FindFirstInColumn(display, first_x, true, extreme_points.top_y, extreme_points.bottom_y);
    std::int32_t last_y = FindLastInColumn(display, first_x, true, extreme_points.top_y, extreme_points.bottom_y);
    if (first_y <= extreme_points.top_y || last_y <= extreme_points.top_y || last_y == extreme_points.bottom_y)
        return false;
    --first_y;
    ++last_y;
    if (!IsFullBlock(display,
                     ExtremePoints(extreme_points.top_y, extreme_points.bottom_y, extreme_points.left_x, first_x - 1),
                     true))
        return false;
    if (!IsFullBlock(display, ExtremePoints(first_y + 1, last_y - 1, first_x, last_x), true))
        return false;
    if (!IsFullBlock(display,
                     ExtremePoints(extreme_points.top_y, extreme_points.bottom_y, last_x + 1, extreme_points.right_x),
                     true))
        return false;
    if (!IsFullBlock(display, ExtremePoints(extreme_points.top_y, first_y, first_x, last_x), false))
        return false;
    if (!IsFullBlock(display, ExtremePoints(last_y, extreme_points.bottom_y, first_x, last_x), false))
        return false;
    return true;
}

bool IsP(const std::vector<std::vector<bool>> &display, const ExtremePoints &extreme_points) {
    std::int32_t first_x = FindFirstInLine(display, extreme_points.bottom_y, false, extreme_points.left_x,
                                           extreme_points.right_x);
    if (first_x <= extreme_points.left_x || first_x == extreme_points.right_x) return false;
    std::int32_t last_y = FindLastInColumn(display, first_x, true, extreme_points.top_y, extreme_points.bottom_y);
    if (last_y <= extreme_points.top_y + 1) return false;
    ++last_y;
    std::int32_t middle_y = FindLastInColumn(display, first_x, false, extreme_points.top_y, last_y - 1);
    if (middle_y <= extreme_points.top_y) return false;
    std::int32_t first_y = FindFirstInColumn(display, first_x, false, extreme_points.top_y, middle_y);
    if (first_y <= extreme_points.top_y) return false;
    std::int32_t last_x = FindLastInLine(display, first_y, false, first_x, extreme_points.right_x);
    if (last_x >= extreme_points.right_x) return false;
    if (!IsFullBlock(display,
                     ExtremePoints(extreme_points.top_y, extreme_points.bottom_y, extreme_points.left_x, first_x - 1),
                     true))
        return false;
    if (!IsFullBlock(display, ExtremePoints(extreme_points.top_y, first_y - 1, first_x, extreme_points.right_x),
                     true))
        return false;
    if (!IsFullBlock(display, ExtremePoints(first_y, last_y - 1, last_x + 1, extreme_points.right_x), true))
        return false;
    if (!IsFullBlock(display, ExtremePoints(middle_y + 1, last_y - 1, first_x, last_x), true)) return false;
    if (!IsFullBlock(display, ExtremePoints(first_y, middle_y, first_x, last_x), false)) return false;
    if (!IsFullBlock(display, ExtremePoints(last_y, extreme_points.bottom_y, first_x, extreme_points.right_x),
                     false))
        return false;
    return true;
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::vector<bool>> display(n, std::vector<bool>(n));
    char tmp;
    for (auto &&row: display) {
        for (auto &&pixel: row) {
            std::cin >> tmp;
            if (tmp == '#') pixel = true;
            else pixel = false;
        }
    }
    ExtremePoints extreme_points = GetExtremePoints(display);
    if (extreme_points.top_y < 0 || extreme_points.bottom_y < 0 || extreme_points.left_x < 0 ||
        extreme_points.right_x < 0)
        std::cout << "X";
    if (IsI(display, extreme_points))
        std::cout << "I";
    else if (IsO(display, extreme_points))
        std::cout << "O";
    else if (IsC(display, extreme_points))
        std::cout << "C";
    else if (IsL(display, extreme_points))
        std::cout << "L";
    else if (IsH(display, extreme_points))
        std::cout << "H";
    else if (IsP(display, extreme_points))
        std::cout << "P";
    else std::cout << "X";
    return 0;
}
