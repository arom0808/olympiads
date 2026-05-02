#pragma GCC optimize("Ofast,O3")

#include <iostream>

using namespace std;

const int32_t maxn = 1e5, block_size = 300;
int32_t n, m;
int32_t dir[maxn], proxy[maxn], proxy_cnt[maxn], used[maxn], gbi[maxn + 1];
int32_t timer = 1;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    for (int32_t i = 0; i < n; ++i) gbi[i] = i / block_size;
    gbi[n] = gbi[n - 1] + 1;
    for (int32_t i = 0; i < n; ++i) cin >> dir[i], dir[i] = std::min(dir[i] + i, n);
    for (int32_t i = n - 1; i >= 0; --i) {
        proxy[i] = dir[i], proxy_cnt[i] = 1;
        if (gbi[i] == gbi[proxy[i]]) proxy_cnt[i] += proxy_cnt[proxy[i]], proxy[i] = proxy[proxy[i]];
    }
    for (int32_t _ = 0, t, a, b; _ < m; ++_) {
        cin >> t;
        if (t == 0) {
            cin >> a >> b, --a;
            proxy[a] = dir[a] = std::min(a + b, n), proxy_cnt[a] = 1;
            if (gbi[a] == gbi[proxy[a]]) proxy_cnt[a] += proxy_cnt[proxy[a]], proxy[a] = proxy[proxy[a]];
            used[a] = ++timer;
            for (int32_t pos = a - 1; pos >= 0 && gbi[pos] == gbi[a]; --pos) {
                if (used[dir[pos]] != timer) continue;
                used[pos] = timer;
                proxy[pos] = dir[pos], proxy_cnt[pos] = 1;
                if (gbi[pos] == gbi[proxy[pos]])
                    proxy_cnt[pos] += proxy_cnt[proxy[pos]], proxy[pos] = proxy[proxy[pos]];
            }
        } else {
            cin >> a, --a;
            int32_t ans_cnt = 0;
            while (proxy[a] < n) ans_cnt += proxy_cnt[a], a = proxy[a];
            while (dir[a] < n) a = dir[a], ++ans_cnt;
            cout << a + 1 << " " << ans_cnt + 1 << "\n";
        }
    }
    return 0;
}
