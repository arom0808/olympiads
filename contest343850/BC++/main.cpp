#include <iostream>
#include <vector>

struct Point {
    std::int32_t x, y;

    Point() : x(0), y(0) {}

    Point(std::int32_t x, std::int32_t y) : x(x), y(y) {}
};

bool PositivityOrNegativityToBool(std::int32_t number) {
    return number > 0;
}

bool IsCirclePossible(const std::vector<Point> &points) {
    bool require = PositivityOrNegativityToBool(points[0].y);
    for (const auto &point: points)
        if (PositivityOrNegativityToBool(point.y) != require) return false;
    return true;
}

long double GetMinRadius(std::vector<Point> &points) {

}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<Point> points(n);
    for (auto &&point: points) std::cin >> point.x >> point.y;
    bool is_circle_possible = IsCirclePossible(points);
    if (!is_circle_possible) {
        std::cout << "-1";
        return 0;
    }
    long double min_radius = GetMinRadius(points);
    std::cout << min_radius;
    return 0;
}
