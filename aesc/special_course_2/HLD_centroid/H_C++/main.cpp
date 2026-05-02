#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

const int32_t maxn = 1e5, maxlogn = 30;

int32_t sz[maxn], centroid_class[maxn], centroid_par[maxn];
vector<int32_t> g[maxn], centroid[maxlogn];
bool used[maxn];

int32_t dfs_size(int32_t u, int32_t p = -1) {
    sz[u] = 1;
    for (int32_t v: g[u]) if (!used[v] && v != p) sz[u] += dfs_size(v, u);
    return sz[u];
}

int32_t find_centroid(int32_t u, int32_t cn, int32_t p = -1) {
    int32_t v = -1;
    for (int32_t _v: g[u]) {
        if (!used[_v] && _v != p && sz[_v] > cn / 2) {
            v = _v;
            break;
        }
    }
    if (v == -1) return u;
    return find_centroid(v, cn, u);
}

void find_and_process_centroid(int32_t u, int32_t c_class, int32_t cp) {
    if (used[u]) return;
    dfs_size(u);
    int32_t c_id = find_centroid(u, sz[u]);
    centroid_class[c_id] = c_class;
    centroid[c_class].push_back(c_id);
    centroid_par[c_id] = cp;
    used[c_id] = true;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n;
    cin >> n;
    for (int32_t i = 1, a, b; i < n; ++i) {
        cin >> a >> b, --a, --b;
        g[a].push_back(b), g[b].push_back(a);
    }
    find_and_process_centroid(0, 0, -1);
    for (int32_t c_class = 0; c_class < maxlogn && !centroid[c_class].empty(); ++c_class)
        for (auto c_id: centroid[c_class])
            for (auto u: g[c_id])
                find_and_process_centroid(u, c_class + 1, c_id);
    if (!centroid[26].empty()) {
        cout << "Impossible!\n";
        return 0;
    }
    for (int32_t i = 0; i < n; ++i) {
        cout << static_cast<char>('A' + centroid_class[i]) << " ";
    }
    cout << "\n";
    return 0;
}
