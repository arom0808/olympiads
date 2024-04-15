#include <iostream>
#include <vector>
#include <iomanip>

using ll = long long;
using ull = unsigned long long;
using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::swap;
using std::fixed;
using std::setprecision;

//ull gcd(ull a, ull b) {
//    ull t;
//    while (b > 0) {
//        t = a % b;
//        a = b;
//        b = t;
//    }
//    return a;
//}
//
//struct Fract {
//    ull a, b;
//
//    void simplify() {
//        ull g = gcd(a, b);
//        a /= g;
//        b /= g;
//    }
//
//    bool operator<(const Fract &other) const { return a * other.b < b * other.a; }
//
//    bool operator>(const Fract &other) const { return a * other.b > b * other.a; }
//
//    bool operator==(const Fract &other) const { return a * other.b == b * other.a; }
//
//    Fract(ull a, ull b) : a(a), b(b) { simplify(); }
//};

int main() {
    ull n, m, k;
    cin >> n >> m >> k;
    vector<pair<ull, ull>> tps(k);
    for (auto &tp: tps) {
        cin >> tp.first >> tp.second;
        --tp.first;
        --tp.second;
    }
    vector<vector<ull>> table(n, vector<ull>(m, 1)), dp1(n, vector<ull>(m, 1)), dp2(n, vector<ull>(m, 1));
    for (auto &row: table) for (auto &val: row) cin >> val;
    dp1.front().front() = table.front().front();
    for (ull i = 0; i < n; ++i) {
        for (ull j = 0; j < m; ++j) {
            auto &r = dp1[i][j];
            if (i > 0 && dp1[i - 1][j] + table[i][j] > r) r = dp1[i - 1][j] + table[i][j];
            if (j > 0 && dp1[i][j - 1] + table[i][j] > r) r = dp1[i][j - 1] + table[i][j];
        }
    }
    dp2.back().back() = table.back().back();
    for (ll i = n - 1; i >= 0; --i) {
        for (ll j = m - 1; j >= 0; --j) {
            auto &r = dp2[i][j];
            if (i + 1 < n && dp2[i + 1][j] + table[i][j] > r) r = dp2[i + 1][j] + table[i][j];
            if (j + 1 > m && dp2[i][j + 1] + table[i][j] > r) r = dp2[i][j + 1] + table[i][j];
        }
    }
    long double res = static_cast<long double>(dp1[n - 1][m - 1]) / (n + m - 1);
    for (auto &tp1: tps) {
        for (auto &tp2: tps) {
            long double th = static_cast<long double>(dp1[tp1.first][tp1.second] + dp2[tp2.first][tp2.second]) /
                             (tp1.first + tp1.second + n - tp2.first + m - tp2.second);
            if (th > res) res = th;
        }
    }
    cout << fixed << setprecision(10) << res;
    return 0;
}
