#include <iostream>
#include <numeric>

using namespace std;

constexpr int maxn = 4e3;

int n;
int perm[maxn];
bool ans[maxn];

int ask() {
    cout << "? ";
    for (int i = 0; i < n; ++i) cout << perm[i] + 1 << " ";
    cout << "\n";
    cout.flush();
    int res;
    cin >> res;
    return res;
}

void solve() {
    cin >> n;
    iota(perm, perm + n, 0);
    int start_cnt = ask();
    int cval = -1;
    for (int i = 0; i + 1 < n; ++i) {
        swap(perm[i], perm[i + 1]);
        int cnt = ask();
        swap(perm[i], perm[i + 1]);
        if (cnt < start_cnt) {
            if (cval == -1) for (int j = 0; j <= i; ++j) ans[j] = true;
            cval = 0;
        } else if (cnt > start_cnt) {
            if (cval == -1) for (int j = 0; j <= i; ++j) ans[j] = false;
            cval = 1;
        }
        if (cval != -1) ans[i + 1] = cval;
    }
    cout << "! ";
    for (int i = 0; i < n; ++i) cout << (ans[i] ? 1 : 0);
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
