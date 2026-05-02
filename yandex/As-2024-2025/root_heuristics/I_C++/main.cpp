#include <iostream>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

const int32_t maxn = 1e5;
int32_t n, m;

vector<int32_t> ps[maxn + 2], invps[maxn + 2];
map<pair<int32_t, int32_t>, int64_t> cache;

void sol() {
    cin >> n >> m;
    for (int32_t i = 0; i <= n + 1; ++i) ps[i].resize(m), invps[i].resize(m);
    iota(ps[0].begin(), ps[0].end(), 0);
    iota(invps[0].begin(), invps[0].end(), 0);
    for (int32_t i = 1; i <= n; ++i) {
        for (auto &el: ps[i + 1]) cin >> el, --el;
        for (int32_t j = 0; j < m; ++j) ps[i][j] = ps[i + 1][ps[i - 1][j]];
        for (int32_t j = 0; j < m; ++j) invps[i][ps[i][j]] = j;
    }
    int32_t q;
    cin >> q;
    cache.clear();
    for (int32_t i = 0, l, r; i < q; ++i) {
        cin >> l >> r, --l;
        if (cache.contains({l, r})) cout << cache[{l, r}] << "\n";
        else {
            int64_t res = 0;
            for (int32_t j = 0; j < m; ++j) res += 1ll * (j + 1) * (ps[r][invps[l][j]] + 1);
            cout << res << "\n";
            cache.emplace(std::pair<int32_t, int32_t>{l, r}, res);
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t t;
    cin >> t;
    while (t--) sol();
    return 0;
}
