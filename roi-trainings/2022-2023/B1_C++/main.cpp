#include <iostream>
#include <vector>

using namespace std;

const uint64_t c18 = 1e18;

vector<uint64_t> fibs;

uint64_t get_dp(uint64_t n, uint64_t max_div) {
    uint64_t res = 0;
    for (auto fib: fibs) {
        if (fib > max_div) break;
        if (n % fib == 0) res += get_dp(n / fib, fib);
        if (n == fib) ++res;
    }
    return res;
}

int main() {
    fibs.reserve(100);
    fibs.push_back(2), fibs.push_back(3);
    while (fibs.back() <= c18) fibs.push_back(fibs[fibs.size() - 1] + fibs[fibs.size() - 2]);
    uint32_t t;
    cin >> t;
    for (uint32_t i = 0; i < t; ++i) {
        uint64_t n;
        cin >> n;
        cout << get_dp(n, n) << "\n";
    }
    return 0;
}
