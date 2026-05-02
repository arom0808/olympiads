#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

constexpr int maxn = 1e5, maxrsz = 1e6, inf = 1e9;

vector<pair<int, int> > raw_g[maxn];
vector<int> v_colors[maxn];
map<pair<int, int>, int> v_cache;
vector<pair<int, int> > g[maxrsz];
int dist[maxrsz];
int n, m;

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int p, q, c;
        cin >> p >> q >> c, --p, --q;
        raw_g[p].emplace_back(q, c);
        raw_g[q].emplace_back(p, c);
        v_colors[p].push_back(c), v_colors[q].push_back(c);
    }
    for (int i = 0; i < n; ++i) {
        sort(v_colors[i].begin(), v_colors[i].end());
        v_colors[i].erase(unique(v_colors[i].begin(), v_colors[i].end()), v_colors[i].end());
    }
    for (int v = 0; v < n; ++v) {
        int vmid = v_cache.emplace(make_pair(v, -1), v_cache.size()).first->second;
        for (auto c: v_colors[v]) {
            int uid = v_cache.emplace(make_pair(v, c), v_cache.size()).first->second;
            g[vmid].emplace_back(uid, 1);
            g[uid].emplace_back(vmid, 1);
        }
        for (auto [u, c]: raw_g[v]) {
            int vid = v_cache.emplace(make_pair(v, c), v_cache.size()).first->second;
            int uid = v_cache.emplace(make_pair(u, c), v_cache.size()).first->second;
            g[vid].emplace_back(uid, 0);
        }
    }
    int start_v = v_cache[{0, -1}], finish_v = v_cache[{n - 1, -1}];
    for (int i = 0; i < v_cache.size(); ++i) dist[i] = inf;
    dist[start_v] = 0;
    deque<int> d;
    d.push_back(start_v);
    while (!d.empty()) {
        int v = d.front();
        d.pop_front();
        for (auto [u,w]: g[v]) {
            if (dist[u] <= dist[v] + w) continue;
            dist[u] = dist[v] + w;
            if (!w) d.push_front(u);
            else d.push_back(u);
        }
    }
    if (dist[finish_v] == inf) cout << "-1\n";
    else cout << dist[finish_v] / 2 << "\n";
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
