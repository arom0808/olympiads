#include <iostream>
#include <vector>

using namespace std;

uint64_t gcd(uint64_t a, uint64_t b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

uint64_t sol(uint64_t n, uint64_t m, uint64_t k, const string &sa, const string &sb, const string &sc) {
    if (m + k == 0) return 1;
    uint64_t a = stoull(sb + sc), b = stoull("0" + sb);
    if (a == 0) return 1;
    uint64_t x, y;
    if (k == 0 || stoull(sc) == 0) {
        x = stoull(sb);
        y = 1;
        for (uint64_t i = 0; i < m; ++i) y *= 10;
    } else {
        x = a - b;
        y = 0;
        for (uint64_t i = 0; i < k; ++i) y = y * 10 + 9;
        for (uint64_t i = 0; i < m; ++i) y *= 10;
    }
    uint64_t g = gcd(x, y);
    x /= g, y /= g;

    uint64_t res = 1;
    vector<char> prime(y + 1, true);
    prime[0] = prime[1] = false;
    for (uint64_t i = 2; i <= y; ++i) {
        if (prime[i]) {
            if (y % i == 0) res *= i;
            if (i * i <= y) for (uint64_t j = i * i; j <= y; j += i) prime[j] = false;
        }
    }
    return res;
}

int main() {
    uint64_t n, m, k;
    cin >> n >> m >> k;
    string a, b, c;
    getline(cin, a), getline(cin, a), getline(cin, b), getline(cin, c);
    cout << sol(n, m, k, a, b, c);
    return 0;
}
