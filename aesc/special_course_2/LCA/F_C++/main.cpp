#include <iostream>
#include <vector>
#include <numeric>
#include <limits>

using namespace std;

const uint64_t inf = numeric_limits<uint64_t>::max();

vector<uint64_t> dsu_ds, dsu_ancs;

uint64_t dsu_vert(uint64_t v) { return v == dsu_ds[v] ? v : dsu_ds[v] = dsu_vert(dsu_ds[v]); }

uint64_t dsu_anc(uint64_t v) { return dsu_ancs[dsu_vert(v)]; }

void dsu_unite(uint64_t a, uint64_t b, uint64_t anc) {
    a = dsu_vert(a), b = dsu_vert(b);
    if ((a + b) & 1) swap(a, b);
    dsu_ds[a] = b, dsu_ancs[b] = anc;
}

void dsu_assign(uint64_t size) {
    dsu_ds.resize(size);
    iota(dsu_ds.begin(), dsu_ds.end(), 0ull);
    dsu_ancs = dsu_ds;
}

vector<uint64_t> parents, childs_cnt, req_sizes;
vector<vector<uint32_t>> nodes, reqs;
vector<bool> used;
uint64_t ans = 0;

void dfs(uint64_t v, uint64_t p) {
    for (auto u: nodes[v]) {
        if (u == p) continue;
        dfs(u, v);
        dsu_unite(v, u, v);
    }
    for (auto u: reqs[v]) if (used[u]) ans += dsu_anc(u);
    used[v] = true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint64_t n, m;
    cin >> n >> m;
    parents.assign(n, inf), childs_cnt.assign(n, 0);
    for (uint64_t i = 1, p; i < n; ++i) {
        cin >> p;
        parents[i] = p;
        ++childs_cnt[p];
    }
    nodes.resize(n);
    for (uint64_t i = 0; i < n; ++i) nodes[i].reserve(childs_cnt[i]);
    for (uint64_t i = 1; i < n; ++i) nodes[parents[i]].push_back(i);
    req_sizes.assign(n, 0);
    uint64_t ra1, ra2, a1, a2;
    uint64_t x, y, z;
    cin >> ra1 >> ra2 >> x >> y >> z;
    a1 = ra1, a2 = ra2;
    for (uint64_t i = 1; i <= m; ++i) {
        if (i > 1) {
            a1 = (x * a1 + y * a2 + z) % n;
            a2 = (x * a2 + y * a1 + z) % n;
        }
        ++req_sizes[a1];
        ++req_sizes[a2];
    }
    reqs.resize(n);
    for (uint64_t i = 0; i < n; ++i) reqs[i].reserve(req_sizes[i]);
    a1 = ra1, a2 = ra2;
    for (uint64_t i = 1; i <= m; ++i) {
        if (i > 1) {
            a1 = (x * a1 + y * a2 + z) % n;
            a2 = (x * a2 + y * a1 + z) % n;
        }
        reqs[a1].push_back(a2);
        reqs[a2].push_back(a1);
    }
    used.assign(n, false);
    dsu_assign(n);
    dfs(0, inf);
    cout << ans;
    return 0;
}