#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

constexpr int maxn = 1e5;

int n;
int vals[maxn];
vector<int> g[maxn];
ll ans = 0;

void dfs2(int v, int gv, int dist, int p = -1){
    ans = std::max(ans, 1ll*std::min(vals[v], vals[gv]) * dist);
    for(auto u: g[v]) if (u!=p) dfs2(u, gv, dist+1, v);
}

void dfs1(int v, int p = -1) {
    dfs2(v,v,0);
    for(auto u:g[v]) if(u!=p) dfs1(u,v);
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> vals[i];
    for (int i = 0, u, v; i + 1 < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    dfs1(0);
    cout<<ans<<"\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt","r",stdin);
#endif
    solve();
    return 0;
}
