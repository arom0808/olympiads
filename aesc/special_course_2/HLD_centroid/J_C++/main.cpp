#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdint>

using namespace std;

const int64_t maxn = 2e5, maxlogn = 30;

class ST {
public:
    map<int64_t, int64_t> data;

    void add_val(int64_t day, int64_t val) {
        auto it = data.lower_bound(day);
        if (it->first == day && it->second >= val) return;
        if (it != data.begin() && prev(it)->second >= val) return;
        auto it2 = it;
        while (it2 != data.end() && it2->second <= val) ++it2;
        data.erase(it, it2);
        data.emplace(day, val);
    }

    int64_t max_on_pref(int64_t day) {
        auto it = data.upper_bound(day);
        if (it == data.begin()) return 0;
        return prev(it)->second;
    }
};

int64_t sz[maxn], centroid_class[maxn], centroid_par[maxn];
int64_t dist[maxn][maxlogn];
vector<pair<int64_t, int64_t>> g[maxn];
vector<int64_t> centroids[maxlogn];
ST sts[maxn];
bool used[maxn];

int64_t dfs_size(int64_t u, int64_t p = -1) {
    sz[u] = 1;
    for (auto [v, l]: g[u]) if (v != p && !used[v]) sz[u] += dfs_size(v, u);
    return sz[u];
}

int64_t find_centroid(int64_t u, int64_t cn, int64_t p = -1) {
    int64_t v = -1;
    for (auto [_v, l]: g[u]) {
        if (_v != p && !used[_v] && sz[_v] > cn / 2) {
            v = _v;
            break;
        }
    }
    if (v == -1) return u;
    return find_centroid(v, cn, u);
}

void dfs_dist(int64_t u, int64_t c_class, int64_t p = -1, int64_t nd = 0) {
    dist[u][c_class] = nd;
    for (auto [v, l]: g[u]) if (v != p && !used[v]) dfs_dist(v, c_class, u, nd + l);
}

void find_and_process_centroid(int64_t u, int64_t c_class, int64_t c_par) {
    if (used[u]) return;
    dfs_size(u);
    int64_t c_id = find_centroid(u, sz[u]);
    dfs_dist(c_id, c_class);
    centroid_class[c_id] = c_class;
    centroid_par[c_id] = c_par;
    centroids[c_class].push_back(c_id);
    used[c_id] = true;
}

void process_act(int64_t day, int64_t u) {
    int64_t br = 0;
    for (int64_t c_id = u, c_class = centroid_class[u]; c_id != -1; c_id = centroid_par[c_id], --c_class)
        if (day >= dist[u][c_class])
            br = std::max(br, sts[c_id].max_on_pref(day - dist[u][c_class]));
    for (int64_t c_id = u, c_class = centroid_class[u]; c_id != -1; c_id = centroid_par[c_id], --c_class)
        sts[c_id].add_val(day + dist[u][c_class], br + 1);
}

int main() {
    freopen("events.in", "r", stdin);
    freopen("events.out", "w", stdout);
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int64_t n, m;
    cin >> n;
    for (int64_t i = 1, a, b, l; i < n; ++i) {
        cin >> a >> b >> l, --a, --b;
        g[a].emplace_back(b, l), g[b].emplace_back(a, l);
    }
    find_and_process_centroid(0, 0, -1);
    for (int64_t c_class = 0; c_class < maxlogn && !centroids[c_class].empty(); ++c_class)
        for (auto c_id: centroids[c_class])
            for (auto [v, l]: g[c_id])
                find_and_process_centroid(v, c_class + 1, c_id);
    cin >> m;
    vector<pair<int64_t, int64_t>> acts(m);
    for (auto &[d, c]: acts) cin >> c >> d, --c;
    sort(acts.begin(), acts.end());
    for (auto [d, c]: acts) process_act(d, c);
    int64_t br = 0;
    for (int64_t i = 0; i < n; ++i)
        if (!sts[i].data.empty() && sts[i].data.rbegin()->second > br)
            br = sts[i].data.rbegin()->second;
    cout << br << "\n";
    return 0;
}
