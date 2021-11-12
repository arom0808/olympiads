#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <iomanip>

const long double EPS = 1e-16;

bool is_check(const std::vector<std::pair<long double, long double>> &points, const long double &rad) {

}

long double
ternary_search(const std::vector<std::pair<long double, long double>> &points, const long double &from,
               const long double &to) {
    if (to - from <= EPS/* || clock() < 1.9 * CLOCKS_PER_SEC*/)
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
    std::cout << std::setprecision(20) << ternary_search(points, radius - 1, radius);
    return 0;
}
