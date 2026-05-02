#include <iostream>

using namespace std;

constexpr int maxn = 1e9 + 1;

char cnts[maxn], nech_ee_cnts[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cnts[1] = 1;
    nech_ee_cnts[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (i & 1) cnts[i] = (nech_ee_cnts[i / 2] + 1) & 1;
        else cnts[i] = 1;
        nech_ee_cnts[i] = (nech_ee_cnts[i - 1] + cnts[i]) & 1;
    }
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        int ans = 0;
        if (n < maxn) ans = cnts[n];
        else {
            if (n & 1) ans = (nech_ee_cnts[n / 2] + 1) & 1;
            else ans = 1;
        }
        cout << (ans ? "Alice\n" : "Bob\n");
    }
}
