#include <iostream>

using namespace std;

constexpr int64_t inf = 1e18;

int64_t dig_sum(int64_t num, int64_t base) {
    int64_t res = 0;
    while (num) {
        res += num % base;
        num /= base;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int64_t n, s;
    cin >> n >> s;
    for (int64_t b = 2; b * b <= n; ++b) {
        if (dig_sum(n, b) == s) {
            cout << b << "\n";
            return 0;
        }
    }
    int64_t b = inf;
    for (int64_t x = 1, cb = (n + x - s) / x; x * x <= n && x <= s; ++x, cb = (n + x - s) / x)
        if ((n + x - s) % x == 0 && cb >= 2 && x < cb && s - x < cb)
            b = std::min(b, cb);
    if (n == s) b = std::min(b, n + 1);
    cout << (b == inf ? -1 : b) << "\n";
    return 0;
}
