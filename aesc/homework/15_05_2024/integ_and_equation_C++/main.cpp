#include <iostream>
#include <list>
#include <functional>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

//inline void sort_three_pairs(long double &d, long double &e, long double &f, long double &g, long double &h, long double &k) {
//    if (d > e) swap(d, e), swap(g, h);
//    if (e > f) swap(e, f), swap(h, k);
//    if (d > e) swap(d, e), swap(g, h);
//}

auto get_root_by_chords(long double a, long double b, long double eps,
                        const function<long double(long double)> &f) -> long double {
    long double fa = f(a), fb = f(b), fox;
    if (signbit(fa) == signbit(fb)) { throw runtime_error("a and b must have different signs"); }
    long double old_x, new_x = a - fa * (b - a) / (fb - fa);
    int n = 0;
    do {
        swap(new_x, old_x);
        fox = f(old_x);
        if (fa > fb && !signbit(fox)) { a = old_x, fa = fox; }
        else if (fa > fb && signbit(fox)) { b = old_x, fb = fox; }
        else if (fa < fb && !signbit(fox)) { b = old_x, fb = fox; }
        else if (fa < fb && signbit(fox)) { a = old_x, fa = fox; }
        new_x = a - fa * (b - a) / (fb - fa);
        ++n;
    } while (abs(new_x - old_x) > eps);
//    cout << n << "\n";
    return new_x;
}

inline auto get_kth_linear(long double a, long double b, uint32_t n, uint32_t i) -> long double {
    return (b - a) / n * i + a;
}

inline auto
parabola_area(long double d, long double e, long double f, long double g, long double h, long double k) -> long double {
    long double a = (f * (g - h) + e * (k - g) + d * (h - k)) / (f * f * (e - d) + e * e * (d - f) + d * d * (f - e));
    long double b = (h - g - a * (e * e - d * d)) / (e - d);
    long double c = g - a * d * d - b * d;
    return a * f * f * f / 3 + b * f * f / 2 + c * f - a * d * d * d / 3 - b * d * d / 2 - c * d;
}

auto integral_for_n(long double a, long double b, uint32_t n, const vector<long double> &vals) -> long double {
    long double res = 0;
    for (uint32_t i = 0; i + 2 <= n; i += 2)
        res += parabola_area(get_kth_linear(a, b, n, i), get_kth_linear(a, b, n, i + 1), get_kth_linear(a, b, n, i + 2),
                             vals[i], vals[i + 1], vals[i + 2]);
    return res;
}

vector<long double> old_vals(81920), new_vals(81920);

auto
Integral(long double a, long double b, long double eps, const function<long double(long double)> &f) -> long double {
    uint32_t n = 1;
    old_vals.clear();
    new_vals.resize(n + 1);
    long double old_res, new_res;
    for (uint32_t i = 0; i <= n; ++i) new_vals[i] = f(get_kth_linear(a, b, n, i));
    new_res = integral_for_n(a, b, n, new_vals);
    do {
        swap(new_vals, old_vals), swap(old_res, new_res);
        new_vals.resize(n * 2 + 1);
        for (uint32_t i = 0; i < n; ++i)
            new_vals[i * 2] = old_vals[i], new_vals[i * 2 + 1] = f(get_kth_linear(a, b, n * 2, i * 2 + 1));
        new_vals[n * 2] = old_vals[n];
        n *= 2;
        new_res = integral_for_n(a, b, n, new_vals);
    } while (abs(new_res - old_res) > eps);
    return new_res;
}


int main() {
////    long double eps_integ = 1e-5, eps_root = 1e-6;
    vector<pair<long double, long double>> rr({{1e-3, 1e-4},
                                               {1e-4, 1e-5},
                                               {1e-5, 1e-6},
                                               {1e-6, 1e-7},
                                               {1e-7, 1e-8},
                                               {1e-8, 1e-9},
                                               {1e-9, 1e-10}});
    cout << fixed << setprecision(30);
    for (auto [a, b]: rr) {
        auto f = [eps_integ = b](long double x) {
            auto f = [x](long double y) { return exp(-cos(y) * x * x / 2) * sqrt(sin(y)); };
            return -1 + x * x * Integral(0, M_PI_2, eps_integ, f);
        };
        auto x = get_root_by_chords(-5, 0, a, f);
        auto y = f(x);
        cout << a << " " << b << " " << x << " " << y << "\n";
        cout.flush();
    }
//    auto f = [](long double x) { return x * x * x - 1; };
//    cout << get_root_by_chords(0, 2, 1e-6, f) << "\n";
//    cout << Integral(0, 1, 1e-7, f) << "\n";
//    cout << Integral(0, 1, 1e-8, f) << "\n";
//    cout << Integral(0, 1, 1e-12, f) << "\n";
    return 0;
}
