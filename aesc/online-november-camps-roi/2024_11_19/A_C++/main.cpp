#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
using ll = int64_t;

constexpr int maxn = 1e5, maxlogn = 18;
int n, q, edges_size;
vector<int> g[maxn];
vector<int> g_sz_pf[maxn];
map<pair<int, int>, int> edge_ids;
pair<int, int> edges[maxn * 2];
ll vert_paths_cnt[maxn];
ll edge_paths_cnt[maxn * 2];
ll vpc_pf[maxn + 1];
ll epc_pf[maxn * 2 + 1];
int bp[maxn * 2][maxlogn];

ll count_edge_path(int eid) {
    if (edge_paths_cnt[eid] != -1) return edge_paths_cnt[eid];
    int from = edges[eid].first, to = edges[eid].second;
    if (g[to].size() == 1) return edge_paths_cnt[eid] = 1;
    if (vert_paths_cnt[to] != -1)
        return edge_paths_cnt[eid] = vert_paths_cnt[to] - edge_paths_cnt[edge_ids[{to, from}]];
    ll tvpc = 1;
    for (auto u: g[to]) {
        if (u == from) continue;
        tvpc += count_edge_path(edge_ids[{to, u}]);
    }
    edge_paths_cnt[eid] = tvpc;
    vert_paths_cnt[to] = tvpc + count_edge_path(edge_ids[{to, from}]);
    return edge_paths_cnt[eid];
}

pair<int, int> make_steps(int p, int v, ll k) {
    if (k > vert_paths_cnt[v] - (p == -1 ? 0 : edge_paths_cnt[edge_ids[{v, p}]]) - 1) return {-1, -1};
    while (k) {
        int sid = lower_bound(begin(edges), begin(edges) + edges_size, make_pair(v, 0)) - begin(edges);
        int fid = lower_bound(begin(epc_pf), begin(epc_pf) + edges_size + 1, epc_pf[sid] + k) - begin(epc_pf) - 1;
        ll fdk = epc_pf[fid] - epc_pf[sid];
        if (p != -1 && make_pair(v, p) <= edges[fid]) {
            fid = lower_bound(begin(epc_pf), begin(epc_pf) + edges_size + 1,
                              epc_pf[sid] + k + edge_paths_cnt[edge_ids[{v, p}]]) - begin(epc_pf) - 1;
            fdk = epc_pf[fid] - epc_pf[sid] - edge_paths_cnt[edge_ids[{v, p}]];
        }
        k -= fdk + 1;
        p = v, v = edges[fid].second;
    }
    return {p, v};
}

void solve() {
    cin >> n >> q;
    edges_size = (n - 1) * 2;
    for (int i = 0, u, v; i + 1 < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
        edges[i * 2] = make_pair(u, v), edges[i * 2 + 1] = make_pair(v, u);
    }
    for (int i = 0; i < n; ++i) sort(g[i].begin(), g[i].end());
    sort(begin(edges), begin(edges) + edges_size);
    for (int i = 0; i < edges_size; ++i) edge_ids[edges[i]] = i;
    for (int i = 0; i < n; ++i) vert_paths_cnt[i] = -1;
    for (int i = 0; i < edges_size; ++i) edge_paths_cnt[i] = -1;
    for (int i = 0; i < edges_size; ++i) count_edge_path(i);
    epc_pf[0] = 0;
    for (int i = 0; i < edges_size; ++i) epc_pf[i + 1] = epc_pf[i] + edge_paths_cnt[i];
    for (int v = 0; v < n; ++v) {
        if (vert_paths_cnt[v] != -1) continue;
        vert_paths_cnt[v] = 1;
        for (auto u: g[v]) vert_paths_cnt[v] += edge_paths_cnt[edge_ids[{v, u}]];
    }
    vpc_pf[0] = 0;
    for (int i = 0; i < n; ++i) vpc_pf[i + 1] = vpc_pf[i] + vert_paths_cnt[i];
    // blocks_cnt = (n + block_size - 1) / block_size;
    for (int i = 0; i < n; ++i) for (int j = 0; j < maxlogn; ++j) bp[i][j] = -1;
    for (int i = 0; i < edges_size; ++i) bp[i][0] = i;
    for (int i = 0; i < n; ++i) {
        sqdp[i][0] = {-1, i};
        for (int bid = 1; bid < blocks_cnt; ++bid) {
            for (int fid = bid - 1; fid >= 0; --fid) {
                auto crr = make_steps(sqdp[i][fid].first, sqdp[i][fid].second, 1ll * (bid - fid) * block_size);
                if (crr.second == -1) continue;
                sqdp[i][bid] = crr;
                break;
            }
        }
    }
    ll k;
    for (int _ = 0; _ < q; ++_) {
        cin >> k, --k;
        int v = upper_bound(begin(vpc_pf), begin(vpc_pf) + n + 1, k) - begin(vpc_pf) - 1;
        k -= vpc_pf[v];
        int sv = v;
        for (int bid = k / block_size; bid >= 0; --bid) {
            if (k / block_size - bid > 3) throw std::runtime_error("");
            auto crr = make_steps(sqdp[v][bid].first, sqdp[v][bid].second,
                                  1ll * (k / block_size - bid) * block_size + k % block_size);
            if (crr.second == -1) continue;
            v = crr.second;
            break;
        }
        cout << sv + 1 << " " << v + 1 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
