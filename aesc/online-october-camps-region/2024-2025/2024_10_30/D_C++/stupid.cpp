#include <algorithm>
#include <iostream>
#include <array>
#include <set>
#include <vector>

using namespace std;

constexpr int inf = 1e8;
constexpr int maxn = 1e5, maxk = 50;
int n, k, m;

namespace Stupid {
    vector<int> arr;
    array<int, maxk> cnts;
    void build(const vector<int> &_arr) { arr = _arr; }
    void change(int pos, int val) { arr[pos] = val; }

    bool check_for_len(int len) {
        cnts.fill(0);
        int dif_cnts = 0;
        for (int i = 0; i < len; ++i) if (cnts[arr[i]]++ == 0) ++dif_cnts;
        if (dif_cnts == k) return true;
        for (int i = 1; i + len <= n; ++i) {
            if (--cnts[arr[i - 1]] == 0) --dif_cnts;
            if (cnts[arr[i + len - 1]]++ == 0) ++dif_cnts;
            if (dif_cnts == k) return true;
        }
        return false;
    }

    int mfsl() {
        int l = 0, r = n + 1;
        while (r - l != 1) {
            int mid = (l + r) / 2;
            if (check_for_len(mid)) r = mid;
            else l = mid;
        }
        if (r == n + 1) return inf;
        return r;
    }
}


void solve() {
    cin >> n >> k >> m;
    vector<int> arr(n);
    for (auto &el: arr) cin >> el, --el;
    Stupid::build(arr);
    for (int i = 0, t, p, u; i < m; ++i) {
        cin >> t;
        if (t == 1) {
            cin >> p >> u, --p, --u;
            Stupid::change(p, u);
        } else {
            int ans = Stupid::mfsl();
            cout << (ans == inf ? -1 : ans) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    solve();
    return 0;
}
