#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    long double a, b, c, d, x1, x2, x3, p, q, dis, exp = 1e-5;
    std::cin >> a >> b >> c >> d;

    p = (3 * a * c - b * b) / (3 * a * a);
    q = (2 * b * b * b - 9 * a * b * c + 27 * a * a * d) / (27 * a * a * a);
    dis = q * q + 4 * p * p * p;

    if (dis > 0) {
        x1 = std::pow((-q + std::sqrt(dis)) / 2, 1.0 / 3) + std::pow((-q - std::sqrt(dis)) / 2, 1.0 / 3) - b / (3 * a);
        x2 = -p / (3 * a) +
             (std::pow(-(q / 2) + std::sqrt(dis) / 2, 0.5) + std::pow(-(q / 2) - std::sqrt(dis) / 2, 0.5)) *
             (std::sqrt(3.0) / 2);
        x3 = -p / (3 * a) -
             (std::pow(-(q / 2) + std::sqrt(dis) / 2, 0.5) + std::pow(-(q / 2) - std::sqrt(dis) / 2, 0.5)) *
             (std::sqrt(3.0) / 2);
    } else {
        x1 = 2 * std::pow(-q / 2, 1.0 / 3) - b / (3 * a);
        x2 = -p / (3 * a) - std::pow(-q / 2, 1.0 / 3);
        x3 = x2;
    }
    long double res;
    if (std::abs(a * x1 * x1 * x1 + b * x1 * x1 + c * x1 + d) <= exp) res = x1;
    else if (std::abs(a * x2 * x2 * x2 + b * x2 * x2 + c * x2 + d) <= exp) res = x2;
    else res = x3;
    std::cout << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << res;
    return 0;
}