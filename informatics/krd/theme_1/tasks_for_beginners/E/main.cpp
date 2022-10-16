#include <iostream>
#include <string>

struct Point {
    std::uint32_t x = 0, y = 0;
};

int main() {
    std::string first_point_str, second_point_str;
    std::cin >> first_point_str >> second_point_str;
    Point first_point, second_point;
    first_point.x = first_point_str[1] - '1';
    first_point.y = first_point_str[0] - 'a';
    second_point.x = second_point_str[1] - '1';
    second_point.y = second_point_str[0] - 'a';
    if (second_point.y <= first_point.y) {
        std::cout << "NO";
        return 0;
    }
    std::uint32_t x_diff = std::max(first_point.x, second_point.x) - std::min(first_point.x, second_point.x);
    std::uint32_t y_diff = std::max(first_point.y, second_point.y) - std::min(first_point.y, second_point.y);
    if ((x_diff + y_diff) % 2 == 1) {
        std::cout << "NO";
        return 0;
    }
    if (x_diff > y_diff) {
        std::cout << "NO";
        return 0;
    }
    if (y_diff % 2 == 1 && x_diff % 2 == 0) {
        std::cout << "NO";
        return 0;
    }
    if (y_diff % 2 == 0 && x_diff % 2 == 1) {
        std::cout << "NO";
        return 0;
    }
    std::cout << "YES";
    return 0;
}