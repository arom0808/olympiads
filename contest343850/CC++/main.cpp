#include <iostream>
#include <vector>
#include <cmath>

const long double eps = 1e-6;

struct Point {
    long double x, y, z;

    Point() : x(0), y(0), z(0) {}

    Point(long double _x, long double _y, long double _z) : x(_x), y(_y), z(_z) {}
};

long double dist(const Point &a, const Point &b) {
    return sqrtl(powl(a.x - b.x, 2) + powl(a.y - b.y, 2) + powl(a.z - b.z, 2));
}

long double max_dist(const Point &p, const std::vector<Point> &ps) {
    long double max = 0, td;
    for (auto pp: ps) {
        td = dist(p, pp);
        if (td > max)
            max = td;
    }
    return max;
}

std::pair<long double, long double> min_max_x(const std::vector<Point> &ps) {
    std::pair<long double, long double> _min_max_x(1e4, 1e-4);
    for (auto pp: ps) {
        if (pp.x < _min_max_x.first)
            _min_max_x.first = pp.x;
        if (pp.x > _min_max_x.second)
            _min_max_x.second = pp.x;
    }
    return _min_max_x;
}

std::pair<long double, long double> min_max_y(const std::vector<Point> &ps) {
    std::pair<long double, long double> _min_max_y(1e4, 1e-4);
    for (auto pp: ps) {
        if (pp.y < _min_max_y.first)
            _min_max_y.first = pp.y;
        if (pp.y > _min_max_y.second)
            _min_max_y.second = pp.y;
    }
    return _min_max_y;
}

std::pair<long double, long double> min_max_z(const std::vector<Point> &ps) {
    std::pair<long double, long double> _min_max_z(1e4, 1e-4);
    for (auto pp: ps) {
        if (pp.z < _min_max_z.first)
            _min_max_z.first = pp.z;
        if (pp.z > _min_max_z.second)
            _min_max_z.second = pp.z;
    }
    return _min_max_z;
}

long double searchX(long double left, long double right, const std::vector<Point> &ps) {
    long double a, b;
    while (right - left > eps) {
        a = (left * 2 + right) / 3;
        b = (left + right * 2) / 3;
        if (max_dist({a, 0, 0}, ps) < max_dist({b, 0, 0}, ps))
            right = b;
        else
            left = a;
    }
    return (left + right) / 2;
}

long double searchY(const long double &x, long double left, long double right, const std::vector<Point> &ps) {
    long double a, b;
    while (right - left > eps) {
        a = (left * 2 + right) / 3;
        b = (left + right * 2) / 3;
        if (max_dist({x, a, 0}, ps) < max_dist({x, b, 0}, ps))
            right = b;
        else
            left = a;
    }
    return (left + right) / 2;
}

long double
searchZ(const long double &x, const long double &y, long double left, long double right, const std::vector<Point> &ps) {
    long double a, b;
    while (right - left > eps) {
        a = (left * 2 + right) / 3;
        b = (left + right * 2) / 3;
        if (max_dist({x, y, a}, ps) < max_dist({x, y, b}, ps))
            right = b;
        else
            left = a;
    }
    return (left + right) / 2;
}

int main() {
    std::vector<Point> points;
    std::uint16_t temp_input = 0;
    std::cin >> temp_input;
    points.resize(temp_input);
    for (auto &point: points) {
        std::cin >> point.x >> point.y >> point.z;
    }
    auto _min_max_x = min_max_x(points);
    auto _min_max_y = min_max_y(points);
    auto _min_max_z = min_max_z(points);
    auto x = searchX(_min_max_x.first, _min_max_x.second, points);
    auto y = searchY(x, _min_max_y.first, _min_max_y.second, points);
    auto z = searchZ(x, y, _min_max_z.first, _min_max_z.second, points);
    std::cout << std::to_string(x) << ' ' << std::to_string(y) << ' ' << std::to_string(z);
    return 0;
}
