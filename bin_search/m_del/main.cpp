#include <iostream>
#include <iomanip>
#include <cmath>

long double GetSqrt(const long double &a, const long double &n) {
    if (a == 0) {
        return 0;
    }
    const auto ld_2 = static_cast<long double>(2);
    long double l = 0, r = 1000, x = (l + r) / ld_2;
    while (std::abs(std::pow(x, n) - a) > 1e-15) {
        if (std::pow(x, n) > a) {
            r = x;
            x = (l + r) / ld_2;
        } else if (std::pow(x, n) < a) {
            l = x;
            x = (l + r) / ld_2;
        }
    }
    return x;
}

int main() {
    long double a;
    std::int32_t n;
    std::cin >> a >> n;
    long double x = GetSqrt(a, n);
    std::cout
            << std::setprecision(static_cast<std::int32_t>(std::to_string(static_cast<std::int64_t>(x)).length()) + 6)
            << x;
    return 0;
}