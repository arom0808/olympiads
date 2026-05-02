#include <iostream>
#include <vector>
#include <map>

using namespace std;
using ll = long long;

constexpr int maxn = 150001;

int n, m;
int s[maxn];
ll ans;
map<vector<int>, int> st_cache;
vector<int> ans_vec;

void stupid_solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) {
        vector<int> cv;
        for (int j = i + 1; j <= n; ++j) {
            cv.push_back(s[j - 1]);
            ++st_cache[cv];
        }
    }
    ans = 0;
    for (auto &[v, cnt]: st_cache) {
        if (v.size() * cnt > ans) {
            ans = v.size() * cnt;
            ans_vec = v;
        }
    }
    cout << ans << "\n";
    cout << ans_vec.size() << "\n";
    for (auto &el: ans_vec) cout << el << " ";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r", stdin);
#endif
    stupid_solve();
    return 0;
}
