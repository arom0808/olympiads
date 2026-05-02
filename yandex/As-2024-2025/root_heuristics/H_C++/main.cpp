#include <iostream>
#include <vector>

using namespace std;

constexpr int32_t maxn = 1e5, max_big_cnt = 450, sqrtm = 500;

int32_t wc[max_big_cnt][maxn];
int32_t wtwid[maxn];
int32_t cs[maxn];
vector<int32_t> g[maxn], wg[maxn];

int32_t n, m, q, bad_cnt = 0;

int main() {
     ios::sync_with_stdio(false), cin.tie(nullptr);
     cin >> n >> m;
     for (int32_t i = 0; i < n; ++i) cin >> cs[i], --cs[i];
     for (int32_t i = 0, a, b; i < m; ++i) {
         cin >> a >> b, --a, --b;
         g[a].push_back(b), g[b].push_back(a);
         if (cs[a] != cs[b]) ++bad_cnt;
     }
     for (int32_t i = 0; i < maxn; ++i) wtwid[i] = -1;
     for (int32_t i = 0, wcnt = 0; i < n; ++i) if (g[i].size() >= sqrtm) wtwid[i] = wcnt++;
     for (int32_t v = 0; v < n; ++v) {
         if (wtwid[v] == -1) continue;
         for (auto u: g[v]) {
             ++wc[wtwid[v]][cs[u]];
             if (wtwid[u] != -1) wg[v].push_back(u);
         }
     }
     cin >> q;
     for (int32_t i = 0, c, v; i < q; ++i) {
         cin >> v >> c, --v, --c;
         if (wtwid[v] == -1) {
             for (const auto u: g[v]) {
                 if (cs[v] != cs[u]) --bad_cnt;
                 if (c != cs[u]) ++bad_cnt;
                 if (wtwid[u] != -1) --wc[wtwid[u]][cs[v]], ++wc[wtwid[u]][c];
             }
         } else {
             bad_cnt += wc[wtwid[v]][cs[v]] - wc[wtwid[v]][c];
             for (const auto u: wg[v]) --wc[wtwid[u]][cs[v]], ++wc[wtwid[u]][c];
         }
         cs[v] = c;
         cout << bad_cnt << "\n";
     }
     return 0;
}
