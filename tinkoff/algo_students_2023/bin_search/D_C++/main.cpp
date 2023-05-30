#include <iostream>
#include <functional>
#include <cmath>
#include <iomanip>

long double GetSolution(long double l, long double r, const std::function<char(const long double &num)> &check_f) {
    if (l > r) std::swap(l, r);
    while (true) {
        auto mid = (l + r) / 2;
        char check_res = check_f(mid);
        if (check_res == '=') return mid;
        if (check_res == '>') l = mid;
        else r = mid;
    }
}

int main() {
    long double C, exp = 1e-7;
    std::cin >> C;
    auto check_f = [&C, &exp](const long double &num) {
        long double n_v = num * num + std::sqrt(num + 1);
        if (std::abs(n_v - C) <= exp) return '=';
        if (C > n_v) return '>';
        return '<';
    };
    std::cout << std::setprecision(std::numeric_limits<double>::digits10 + 1) << GetSolution(0, C, check_f)
              << std::endl;
    return 0;
}
