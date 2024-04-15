#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    int32_t n, m;
    cin >> n >> m;
    vector<vector<pair<int32_t, int32_t>>> g(n);
    for (int32_t i = 0, a, b, w; i < m; ++i) {
        cin >> a >> b >> w;
        g[a - 1].emplace_back(b - 1, w);
        g[b - 1].emplace_back(a - 1, w);
    }
    int32_t min_way = -1;
    vector<unordered_map<int32_t, int32_t>> dp1(n), dp2(n);
    for (int32_t i = 0; i < n; ++i) dp1[i].emplace(1 << i, 0);
    if (n == 1) min_way = 0;
    for (int32_t pl = 1; pl < n; ++pl) {
        for (int32_t i = 0; i < n; ++i) {
            for (auto [mask, nw]: dp1[i]) {
                for (auto [neig, neig_w]: g[i]) {
                    if ((mask & (1 << neig)) != 0) continue;
                    auto it = dp2[neig].find(mask | (1 << neig));
                    if (it == dp2[neig].end())
                        it = dp2[neig].emplace(mask | (1 << neig), nw + neig_w).first;
                    else if (nw + neig_w < it->second) it->second = nw + neig_w;
                    if (pl + 1 == n && (min_way == -1 || it->second < min_way)) min_way = it->second;
                }
            }
        }
        dp1.swap(dp2);
        for (auto &dd: dp2) dd.clear();
    }
    cout << min_way;
    return 0;
}
