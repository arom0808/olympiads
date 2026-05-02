#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
using ll = long long;

constexpr int maxn = 2e5, maxlogn = 18, inf = 1e9 + 1;
int n;
vector<pair<int, int> > g[maxn];
bool used[maxn];
int cbl[maxn][maxlogn];
ll dcbl[maxn][maxlogn];
int par[maxn], cur_par[maxn], sz[maxn], cent_level[maxn];

int dfs_sz(int v, int p = -1) {
    if (used[v]) return 0;
    sz[v] = 1;
    for (auto [u,w]: g[v]) if (u != p) sz[v] += dfs_sz(u, v);
    return sz[v];
}

void dfs_process_centroid(int v, int clev, int cid, ll cdist, int p = -1) {
    if (used[v]) return;
    cbl[v][clev] = cid;
    dcbl[v][clev] = cdist;
    cur_par[v] = cid;
    for (auto [u,w]: g[v]) if (u != p) dfs_process_centroid(u, clev, cid, cdist + w, v);
}

void find_add_centroid(int v) {
    dfs_sz(v);
    int csz = sz[v];
    for (int found = 1, cp = -1; found;) {
        found = false;
        for (auto [u,w]: g[v]) {
            if (used[u] || u == cp || sz[u] <= csz / 2) continue;
            cp = v, v = u, found = 1;
            break;
        }
    }
    cent_level[v] = (cur_par[v] == -1) ? 0 : cent_level[cur_par[v]] + 1;
    par[v] = cur_par[v];
    dfs_process_centroid(v, cent_level[v], v, 0);
    used[v] = true;
}

struct Party {
    int v, t;

    bool operator<(const Party &rhs) const {
        if (t != rhs.t) return t < rhs.t;
        return v < rhs.v;
    }
};

map<int, int> csts[maxn];
Party parties[maxn];
int m;

int get_max_cnt_in_centroid(int v, int t) {
    auto it = csts[v].upper_bound(t);
    if (it == csts[v].begin()) return 0;
    return prev(it)->second;
}

int get_max_parties_cnt(int v, int t) {
    int ans = 0;
    for (int level = 0; level < maxlogn; ++level) {
        if (cbl[v][level] == -1) break;
        if (t < dcbl[v][level]) continue;
        ans = std::max(ans, get_max_cnt_in_centroid(cbl[v][level], t - dcbl[v][level]));
    }
    return ans;
}

void add_party_to_centroid(int v, int t, int cnt) {
    auto it = csts[v].emplace(t, cnt).first;
    if (it->second < cnt) it->second = cnt;
    if (it != csts[v].begin() && prev(it)->second >= it->second)
        csts[v].erase(it);
    else
        while (next(it) != csts[v].end() && next(it)->second <= it->second)
            csts[v].erase(next(it));
}

void add_party(int v, int t, int cnt) {
    for (int level = 0; level < maxlogn; ++level) {
        if (cbl[v][level] == -1) break;
        if (dcbl[v][level] + t >= inf) continue;
        add_party_to_centroid(cbl[v][level], dcbl[v][level] + t, cnt);
    }
}

void solve() {
    cin >> n;
    for (int i = 0, u, v, w; i + 1 < n; ++i) {
        cin >> u >> v >> w, --u, --v;
        g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    }
    for (int v = 0; v < n; ++v) cur_par[v] = -1;
    for (int v = 0; v < n; ++v) for (int lev = 0; lev < maxlogn; ++lev) cbl[v][lev] = -1;
    for (int v = 0; v < n; ++v) while (!used[v]) find_add_centroid(v);
    cin >> m;
    for (int i = 0; i < m; ++i) cin >> parties[i].v >> parties[i].t, --parties[i].v;
    sort(parties, parties + m);
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        auto [v,t] = parties[i];
        int cmcnt = get_max_parties_cnt(v, t);
        ans = std::max(ans, cmcnt + 1);
        add_party(v, t, cmcnt + 1);
    }
    cout << ans << "\n";
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
