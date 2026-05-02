#include <algorithm>
#include <iostream>
#include <vector>


using ll = int64_t;
using namespace std;

constexpr int maxn = 1e5;

pair<int, int> fld(int x) {
    int last_d = x % 10, first_d = last_d;
    while (x) {
        first_d = x % 10;
        x /= 10;
    }
    return make_pair(first_d, last_d);
}

namespace Stupid {
    void solve() {
        int g, r, b;
        cin >> g >> r >> b;
        vector<int> gs(g), rs(r), bs(b);
        for (auto &el: gs) cin >> el;
        for (auto &el: rs) cin >> el;
        for (auto &el: bs) cin >> el;
        ll ans = 0;
        for (auto el1: gs) {
            for (auto el2: rs) {
                for (auto el3: bs) {
                    if (el1 == el2 || el2 == el3 || el1 == el3) continue;
                    auto ff1 = fld(el1), ff2 = fld(el2), ff3 = fld(el3);
                    auto s1 = ff1.first, f1 = ff1.second;
                    auto s2 = ff2.first, f2 = ff2.second;
                    auto s3 = ff3.first, f3 = ff3.second;
                    if (f1 == s2 && f2 == s3) ++ans;
                }
            }
        }
        cout << ans;
    }
}

int main() {
    freopen("input.txt", "r",stdin);
    ios::sync_with_stdio(false), cin.tie(nullptr);
    Stupid::solve();
    return 0;
}
