#include <iostream>
#include <vector>
#include <set>

using namespace std;

//struct Vert {
//    int32_t fup;
//    int32_t tin;
//    multiset<int32_t> son_fups;
//    set<int32_t> sons;
//};
//
//void
//dfs(vector<Vert> &g, const vector<set<int32_t>> &rg, vector<bool> &used, int32_t &timer, int32_t &res, int32_t v,
//    int32_t p = -1) {
//    used[v] = true;
//    g[v].tin = g[v].fup = timer++;
//    for (auto to: rg[v]) {
//        if (to == p) continue;
//        if (used[to]) {
//            g[v].fup = min(g[v].fup, g[to].tin);
//        } else {
//            dfs(g, rg, used, timer, res, to, v);
//            g[v].fup = min(g[v].fup, g[to].fup);
//            g[v].son_fups.insert(g[to].fup);
//            g[v].sons.insert(to);
//        }
//    }
//    for (auto to: g[v].sons) {
//        if (g[v].son_fups.size() > 1) {
//            g[v].son_fups.erase(g[v].son_fups.find(g[to].fup));
//            if (*g[v].son_fups.rbegin() >= g[v].tin) { ++res; }
//            g[v].son_fups.insert(g[to].fup);
//        }
//        if (!g[to].son_fups.empty()) {
//            if (*g[to].son_fups.rbegin() >= g[v].tin) { ++res; }
//        }
//    }
//}

void dfs(const vector<set<int32_t>> &rg, vector<int32_t> &used, int32_t v, int32_t ut, int32_t bad_1, int32_t bad_2) {
    if (v == bad_1 || v == bad_2 || used[v] == ut) return;
    used[v] = ut;
    for (auto to: rg[v])
        if (used[to] != ut)
            dfs(rg, used, to, ut, bad_1, bad_2);
}

int main() {
    int32_t n, m;
    cin >> n >> m;
    vector<set<int32_t>> rg(n);
    vector<pair<int32_t, int32_t>> edges(m);
    for (int32_t i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        rg[a - 1].insert(b - 1);
        rg[b - 1].insert(a - 1);
        edges[i] = {a - 1, b - 1};
    }
    vector<int32_t> used(n, 0);
    int32_t time = 1, res = 0;
    for (auto [v, u]: edges) {
        rg[v].erase(u);
        rg[u].erase(v);
        bool ok = true;
        if (!rg[v].empty()) {
            ok = false;
            dfs(rg, used, *rg[v].begin(), time, u, v);
        } else if (!rg[u].empty()) {
            ok = false;
            dfs(rg, used, *rg[u].begin(), time, u, v);
        }
        if (!ok) {
            ok = true;
            for (auto tt: rg[v]) {
                if (used[tt] != time) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                for (auto tt: rg[u]) {
                    if (used[tt] != time) {
                        ok = false;
                        break;
                    }
                }
            }
            if (!ok) ++res;
        }
        ++time;
//        if ()
//        if(dfs())
        rg[v].insert(u);
        rg[u].insert(v);
    }
    cout << res;
//    vector<Vert> g(n);
//    int32_t timer = 0, res = 0;
//    dfs(g, rg, used, timer, res, 0);
//    cout << res;
    return 0;
}
