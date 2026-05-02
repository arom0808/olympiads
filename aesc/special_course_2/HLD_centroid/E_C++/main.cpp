#include <iostream>
#include <vector>
#include <cstdint>
#include <map>

using namespace std;

template<typename T>
class ST {
public:
    map<int32_t, T> data;

    void set(int32_t pos, T val) {
        data.erase(data.begin(), data.upper_bound(pos));
        data.emplace(pos, val);
    }

    T max_on_suf(int32_t start) {
        auto it = data.lower_bound(start);
        if (it != data.end()) return it->second;
        return {-2, -2};
    }
};

const int32_t maxn = 1e5, maxlogn = 20;

vector<pair<int32_t, int32_t>> g[maxn];
int32_t center[maxn][maxlogn], dist[maxn][maxlogn];
int32_t sz[maxn], cp[maxn], centroid_class[maxn];
bool used[maxn];
ST<pair<int32_t, int32_t>> sts[maxn];
vector<int32_t> centroids[maxlogn];

int32_t dfs_size(int32_t u, int32_t p = -1) {
    sz[u] = 1;
    for (auto [v, w]: g[u]) if (!used[v] && v != p) sz[u] += dfs_size(v, u);
    return sz[u];
}

int32_t find_centroid(int32_t u, int32_t cn, int32_t p = -1) {
    int32_t v = -1;
    for (auto [_v, w]: g[u]) {
        if (!used[_v] && _v != p && sz[_v] > cn / 2) {
            v = _v;
            break;
        }
    }
    if (v == -1) return u;
    return find_centroid(v, cn, u);
}

void dist_center_dfs(int32_t u, int32_t nd, int32_t c_class, int32_t c_id, int32_t p = -1) {
    dist[u][c_class] = nd;
    center[u][c_class] = c_id;
    for (auto [v, w]: g[u]) if (!used[v] && v != p) dist_center_dfs(v, nd + w, c_class, c_id, u);
}

void find_and_process_centroid(int32_t u, int32_t c_class, int32_t pc) {
    if (used[u]) return;
    dfs_size(u);
    int32_t c_id = find_centroid(u, sz[u]);
    dist_center_dfs(c_id, 0, c_class, c_id);
    centroids[c_class].push_back(c_id);
    cp[c_id] = pc;
    used[c_id] = true;
    centroid_class[c_id] = c_class;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n;
    cin >> n;
    for (int32_t i = 1, a, b, w; i < n; ++i) {
        cin >> a >> b >> w, --a, --b;
        g[a].emplace_back(b, w), g[b].emplace_back(a, w);
    }
    find_and_process_centroid(0, 0, -1);
    for (int32_t c_class = 0; c_class < maxlogn && !centroids[c_class].empty(); ++c_class)
        for (auto c_id: centroids[c_class])
            for (auto [v, w]: g[c_id])
                find_and_process_centroid(v, c_class + 1, c_id);
    int32_t q;
    cin >> q;
    for (int32_t i = 0, a, v, d, c; i < q; ++i) {
        cin >> a;
        if (a == 1) {
            cin >> v >> d >> c, --v;
            for (int32_t u = v, c_class = centroid_class[v]; u != -1; u = cp[u], --c_class)
                if (d >= dist[v][c_class])
                    sts[u].set(d - dist[v][c_class], {i, c});
        } else {
            cin >> v, --v;
            pair<int32_t, int32_t> best_res(-1, 0);
            for (int32_t u = v, c_class = centroid_class[v]; u != -1; u = cp[u], --c_class)
                best_res = std::max(best_res, sts[u].max_on_suf(dist[v][c_class]));
            cout << best_res.second << "\n";
        }
    }
    return 0;
}
