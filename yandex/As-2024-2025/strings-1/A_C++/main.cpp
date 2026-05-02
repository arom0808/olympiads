#include <iostream>

using namespace std;

constexpr int maxn = 1e7;
int z[maxn];
string s;
int n;

void solve() {
    cin >> s;
    n = s.size();
    s += s;
    int l = 0, r = 1;
    for (int i = 1; i <= n; ++i) {
        z[i] = std::max(0, std::min(z[i - l], r - i));
        while (i + z[i] < n * 2 && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    for (int i = 1; i <= n; ++i) {
        if (z[i] >= n) {
            cout << n / i << "\n";
            return;
        }
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
