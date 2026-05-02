#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

constexpr int maxn = 2e5 + 10, maxcolor = maxn * 2;

int n;

vector<int> g[maxn];
int next_prior;
int fire_color[maxn];
int prior[maxn];

void calc_colors() {
    map<int, set<pair<int, int> > > vs_by_pow;
    vector<int> pows(n);
    for (int v = 0; v < n; ++v) pows[v] = g[v].size();
    for (int v = 0; v < n; ++v) vs_by_pow[pows[v]].emplace(prior[v], v);
    for (int col = 0; col + 1 < n; ++col) {
        auto [cpr, v] = *vs_by_pow[1].begin();
        fire_color[v] = col;
        pows[v] = -1;
        vs_by_pow[1].erase(make_pair(cpr, v));
        for (auto u: g[v]) {
            if (pows[u] == -1) continue;
            vs_by_pow[pows[u]].erase(make_pair(prior[u], u));
            vs_by_pow[--pows[u]].emplace(prior[u], u);
        }
    }
    fire_color[vs_by_pow[0].begin()->second] = n - 1;
}

void solve() {
    int q;
    cin >> n >> q;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) prior[i] = i;
    next_prior = n;
    string rt;
    for (int _ = 0, v, u; _ < q; ++_) {
        cin >> rt;
        if (rt == "up") {
            cin >> v, --v;
            prior[v] = next_prior++;
        } else if (rt == "when") {
            cin >> v, --v;
            calc_colors();
            cout << fire_color[v] + 1 << "\n";
        } else {
            cin >> v >> u, --v, --u;
            calc_colors();
            if (fire_color[v] < fire_color[u]) cout << v + 1 << "\n";
            else cout << u + 1 << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#elifdef TEST
    freopen("input.txt", "r", stdin);
#endif
    solve();
    return 0;
}
