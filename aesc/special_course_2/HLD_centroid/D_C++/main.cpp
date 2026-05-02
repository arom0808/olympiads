#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

const int32_t maxn = 3e5 + 2;
const int32_t maxlogn = 21;

bool colors[maxn], used[maxn];
vector<int32_t> g[maxn], centres[maxlogn];
int32_t sz[maxn], cnt_in[maxn], cnt_out[maxn];

int32_t size_dfs(int32_t u, int32_t p = -1) {
    sz[u] = 1;
    for (auto v: g[u]) if (v != p && !used[v]) sz[u] += size_dfs(v, u);
    return sz[u];
}

int32_t centroid_dfs(int32_t u, int32_t cn, int32_t p = -1) {
    int32_t v = -1;
    for (auto _v: g[u]) {
        if (_v != p && !used[_v] && sz[_v] > cn / 2) {
            v = _v;
            break;
        }
    }
    if (v == -1) return u;
    return centroid_dfs(v, cn, u);
}

int32_t add_centroid(int32_t u, int32_t c_class) {
    if (used[u]) return u;
    size_dfs(u);
    int32_t c_id = centroid_dfs(u, sz[u]);
    centres[c_class].push_back(c_id);
    used[c_id] = true;
    return c_id;
}

void dfs_in(int32_t u, int32_t p = -1, int32_t c_cnt = 0, int32_t need_open = 0) {
    if (colors[u]) ++c_cnt, need_open = max(need_open - 1, 0);
    else --c_cnt, ++need_open;
    if (c_cnt >= 0 && need_open == 0) ++cnt_in[c_cnt];
    for (int32_t v: g[u]) if (v != p && !used[v]) dfs_in(v, u, c_cnt, need_open);
}

void dfs_out(int32_t u, int32_t p, int32_t c_cnt, int32_t min_cnt_on_way) {
    if (colors[u]) ++c_cnt;
    else --c_cnt;
    if (min_cnt_on_way > c_cnt) min_cnt_on_way = c_cnt;
    if (c_cnt <= 0 && min_cnt_on_way >= c_cnt) ++cnt_out[-c_cnt];
    for (int32_t v: g[u]) if (v != p && !used[v]) dfs_out(v, u, c_cnt, min_cnt_on_way);
}

uint64_t process_c_id_child(int32_t c_id, int32_t u_c_cnt, int32_t i, bool next) {
    uint64_t res = 0;
    if (!used[g[c_id][next ? i + 1 : i - 1]]) dfs_in(g[c_id][next ? i + 1 : i - 1], c_id, u_c_cnt, max(-u_c_cnt, 0));
    int32_t cn_out = sz[g[c_id][i]];
    for (int32_t j = 0; j <= cn_out; ++j) cnt_out[j] = 0;
    if (!used[g[c_id][i]]) dfs_out(g[c_id][i], c_id, 0, 0);
    for (int32_t j = 0; j <= cn_out; ++j)
        res += 1ll * cnt_in[j] * cnt_out[j];
    return res;
}

uint64_t process_centroid(int32_t u, int32_t c_class) {
    if (used[u]) return 0;
    uint64_t res = 0;
    int32_t c_id = add_centroid(u, c_class), cn_in = sz[u];
    for (int32_t i = 0; i <= cn_in; ++i) cnt_in[i] = cnt_out[i] = 0;
    int32_t u_c_cnt = colors[c_id] ? 1 : -1;
    if (u_c_cnt >= 0) {
        ++cnt_in[u_c_cnt];
        for (auto v: g[c_id]) if (!used[v]) dfs_out(v, c_id, 0, 0);
        res += 1ll * cnt_in[u_c_cnt] * cnt_out[u_c_cnt];
    } else {
        for (auto v: g[c_id]) if (!used[v]) dfs_in(v, c_id, u_c_cnt, max(-u_c_cnt, 0));
        res += cnt_in[0];
    }
    for (int32_t i = 0; i <= cn_in; ++i) cnt_in[i] = 0;
    for (int32_t i = 1; i < g[c_id].size(); ++i)
        res += process_c_id_child(c_id, u_c_cnt, i, false);
    for (int32_t i = 0; i <= cn_in; ++i) cnt_in[i] = 0;
    for (int32_t i = g[c_id].size() - 2; i >= 0; --i)
        res += process_c_id_child(c_id, u_c_cnt, i, true);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n;
    cin >> n;
    char c;
    for (int32_t i = 0; i < n; ++i) cin >> c, colors[i] = c == '(';
    for (int32_t i = 1, a, b; i < n; ++i) {
        cin >> a >> b;
        g[a - 1].push_back(b - 1), g[b - 1].push_back(a - 1);
    }
    uint64_t res = 0;
    res += process_centroid(0, 0);
    for (int32_t c_class = 0; c_class < maxlogn && !centres[c_class].empty(); ++c_class)
        for (auto c_id: centres[c_class])
            for (auto u: g[c_id])
                res += process_centroid(u, c_class + 1);
    cout << res << "\n";
    return 0;
}
