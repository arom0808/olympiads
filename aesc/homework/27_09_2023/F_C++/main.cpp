#include <iostream>
#include <tuple>
#include <iomanip>
#include <cmath>
//#include <random>

std::int32_t gcd(std::int32_t a, std::int32_t b) {
    while (b > 0) std::tie(a, b) = std::make_tuple(b, a % b);
    return a;
}

enum class Status {
    not_found,
    found,
    any
};

bool is_eq(long double a, long double b) {
    return std::abs(a - b) < 1e-5;
}

void print_result(std::pair<Status, long double> x, std::pair<Status, long double> y) {
    if (is_eq(x.second, 0)) x.second = 0;
    if (is_eq(y.second, 0)) y.second = 0;
    if (x.first == Status::any) {
        if (y.first == Status::any) std::cout << "2XY";
        else std::cout << "1X " << y.second;
    } else if (x.first == Status::found) {
        if (y.first == Status::any) std::cout << "1Y " << x.second;
        else std::cout << "2 " << x.second << " " << y.second;
    } else {
        std::cout << "1";
    }
}

//namespace Dev {
//    std::random_device dev;
//    std::mt19937 rng(dev());
//    std::bernoulli_distribution bg(0.5);
//    std::uniform_int_distribution ind(-100, 100);
//
//    void Gen(std::int32_t &a, std::int32_t &b, std::int32_t &c, std::int32_t &d, std::int32_t &e, std::int32_t &f) {
//        a = (bg(rng) ? ind(rng) : 0);
//        b = (bg(rng) ? ind(rng) : 0);
//        c = (bg(rng) ? ind(rng) : 0);
//        d = (bg(rng) ? ind(rng) : 0);
//        e = (bg(rng) ? ind(rng) : 0);
//        f = (bg(rng) ? ind(rng) : 0);
//    }
//
//    void PrintR(std::int32_t a, std::int32_t b, std::int32_t c, std::int32_t d, std::int32_t e, std::int32_t f) {
//        std::cout << a << "x + (" << b << ")y = " << e << "\n";
//        std::cout << c << "x + (" << d << ")y = " << f << "\n\n";
//    }
//}

int main() {
    std::int32_t a, b, c, d, e, f;
    std::cin >> a >> b >> c >> d >> e >> f;
//    Dev::Gen(a, b, c, d, e, f);
//    a = 48;
//    b = 66;
//    c = 0;
//    d = 92;
//    e = 0;
//    f = -55;
//    Dev::PrintR(a, b, c, d, e, f);
    std::cout << std::fixed << std::setprecision(2);
    std::int32_t d1 = gcd(gcd(std::abs(a), std::abs(b)), std::abs(e)) * (e < 0 ? (-1) : 1),
            d2 = gcd(gcd(std::abs(c), std::abs(d)), std::abs(f)) * (f < 0 ? (-1) : 1);
    if (d1 != 0) std::tie(a, b, e) = std::make_tuple(a / d1, b / d1, e / d1);
    if (d2 != 0) std::tie(c, d, f) = std::make_tuple(c / d2, d / d2, f / d2);
    if (a != 0 && b != 0) std::tie(a, b, c, d, e, f) = std::make_tuple(c, d, a, b, f, e);
    std::pair<Status, long double> x(Status::not_found, 0), y(Status::not_found, 0);
    if (a == 0) {
        if (b == 0) {
            if (e == 0) x = y = {Status::any, 0};
            else {
                std::cout << "0";
                return 0;
            }
        } else {
            x = {Status::any, 0};
            y = {Status::found, static_cast<long double>(e) / static_cast<long double>(b)};
        }
    } else {
        if (b == 0) {
            x = {Status::found, static_cast<long double>(e) / static_cast<long double>(a)};
            y = {Status::any, 0};
        }
    }
    if (c == 0) {
        if (d == 0) {
            if (f == 0) print_result(x, y);
            else std::cout << "0";
            return 0;
        } else {
            if (x.first != Status::found) x = {Status::any, 0};
            auto n_y = static_cast<long double>(f) / static_cast<long double>(d);
            if (y.first == Status::found && !is_eq(y.second, n_y)) {
                std::cout << "0";
                return 0;
            } else y = {Status::found, n_y};
        }
    } else {
        if (d == 0) {
            auto n_x = static_cast<long double>(f) / static_cast<long double>(c);
            if (x.first == Status::found && !is_eq(x.second, n_x)) {
                std::cout << "0";
                return 0;
            } else x = {Status::found, n_x};
            if (y.first != Status::found) y = {Status::any, 0};
        } else {
            if ((x.first == Status::any && y.first == Status::any) || (a == c && b == d && e == f)) {
                std::cout << "1";
                return 0;
            } else {
                if (x.first == Status::found)
                    y = {Status::found, (static_cast<long double>(f) - static_cast<long double>(c) * x.second) /
                                        static_cast<long double>(d)};
                else
                    x = {Status::found, (static_cast<long double>(f) - static_cast<long double>(d) * y.second) /
                                        static_cast<long double>(c)};
            }
        }
    }
    print_result(x, y);
    return 0;
}
