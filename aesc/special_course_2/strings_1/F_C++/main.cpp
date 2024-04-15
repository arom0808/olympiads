#include <iostream>
#include <random>
#include <vector>

using namespace std;

const uint64_t k = 31, mod = 1e9 + 7;
vector<uint64_t> p;

uint64_t hash_substr(uint32_t l, uint32_t r, const vector<uint64_t> &h) {
    return (mod + h[r + 1] - h[l]) % mod * p[h.size() - l - 1] % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    p.assign(1e5 + 1, 1);
    for (uint32_t i = 1; i < p.size(); ++i) p[i] = p[i - 1] * k % mod;

    string s;
    cin >> s;
    vector<uint64_t> h(s.size() + 1, 0);
    for (uint32_t i = 0; i < s.size(); ++i) h[i + 1] = (h[i] + p[i] * (s[i] - 'a' + 1)) % mod;
    uint32_t q;
    cin >> q;
    for (uint32_t i = 0, a, b, c, d; i < q; ++i) {
        cin >> a >> b >> c >> d;
        --a, --b, --c, --d;
        uint32_t l = 0, r = min(b - a, d - c) + 1;
        while (l != r) {
            uint32_t m = (l + r) / 2 + (l + r) % 2;
            if (hash_substr(a, a + m - 1, h) == hash_substr(c, c + m - 1, h)) l = m;
            else r = m - 1;
        }
        if (l <= min(b - a, d - c)) cout << (s[a + l] < s[c + l] ? "<\n" : ">\n");
        else cout << (b - a == d - c ? "=\n" : (b - a > d - c ? ">\n" : "<\n"));
    }
    return 0;
}
