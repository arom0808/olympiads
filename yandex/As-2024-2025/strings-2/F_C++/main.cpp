#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
using ll = long long;
using ull = unsigned long long;

constexpr int maxn = 5e6 + 2;
constexpr int asz = 26;

string s;
ull hbc[asz];
mt19937_64 rng(236623);
ull hpf[maxn];

bool check_len(int len) {
    ull phv = hpf[len];
    for (int i = len; i < s.size(); i += len) if (hpf[i + len] - hpf[i] != phv) return false;
    return true;
}

void solve() {
    for (int i = 0; i < asz; ++i) hbc[i] = rng();
    cin >> s;
    hpf[0] = 0;
    for (int i = 0; i < s.size(); ++i) hpf[i + 1] = hpf[i] + hbc[s[i] - 'a'];
    vector<int> lengths;
    lengths.reserve(5000);
    for (int i = 1; i * i <= s.size(); ++i) {
        if (s.size() % i) continue;
        lengths.push_back(i);
        if (i * i != s.size()) lengths.push_back(s.size() / i);
    }
    sort(lengths.begin(), lengths.end());
    for (auto l: lengths) {
        if (!check_len(l)) continue;
        cout << s.size() / l << "\n";
        return;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
