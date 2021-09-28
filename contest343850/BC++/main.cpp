#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

const long double EPS = 1e-6;

template<typename T>
bool is_touch(const std::pair<long double, long double> &point, const T &rad) {
    if (point.second == 0) {
        return true;
    } else if (point.second > 0) {
        if (point.second - rad <= rad && point.second + rad >= rad) {
            return true;
        }
    } else {
        if (point.second - rad <= (-rad) && point.second + rad >= (-rad)) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool is_touch(const std::vector<std::pair<long double, long double>> &points, const T &rad) {
    for (const std::pair<long double, long double> &point: points) {
        if (!is_touch<T>(point, rad))
            return false;
    }
    return true;
}

long double
ternary_search(const std::vector<std::pair<long double, long double>> &points, const long double &from,
               const long double &to) {
    if (to - from <= EPS)
        return (from + to) / 2;
    long double a = (from * 2 + to) / 3;
    long double b = (from + to * 2) / 3;
    if (is_touch(points, a))
        return ternary_search(points, from, b);
    else
        return ternary_search(points, a, to);
}

bool p_cmp_y(const std::pair<long double, long double> &a, const std::pair<long double, long double> &b) {
    return a.second < b.second;
}

int main() {
    std::vector<std::pair<long double, long double>> points;
    std::int64_t temp_input;
    std::cin >> temp_input;
    points.resize(temp_input);
    for (auto &point: points) {
        std::cin >> point.first >> point.second;
    }
    if (points.size() == 1) {
        std::cout << (points[0].second / 2);
        return 0;
    }
    bool atop = false, adown = false;
    for (auto &point: points) {
        if (point.second > 0)
            atop = true;
        else if (point.second < 0)
            adown = true;
    }
    if (atop && adown) {
        std::cout << -1;
        return 0;
    }
    long double max = atop ? std::max_element(points.begin(), points.end(), p_cmp_y)->second : std::min_element(
            points.begin(), points.end(), p_cmp_y)->second;
    bool re = false;
    std::uint64_t radius = 0;
    for (std::uint64_t i = 0; (atop ? i <= max : i >= max); ++i) {
        if (is_touch(points, i)) {
            re = true;
            radius = i;
            break;
        }
    }
    if (!re) {
        std::cout << -1;
        return 0;
    }
    std::cout << ternary_search(points, radius - 1, radius);
    return 0;
}
