//#pragma GCC optimize("Ofast")
//#pragma GCC optimize(O3)
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,tune=native")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
//#pragma GCC optimize("vpt")
//#pragma GCC optimize("rename-registers")
//#pragma GCC optimize("move-loop-invariants")
//#pragma GCC optimize("unswitch-loops")
//#pragma GCC optimize("function-sections")
//#pragma GCC optimize("data-sections")
//#pragma GCC optimize("branch-target-load-optimize")
//#pragma GCC optimize("branch-target-load-optimize2")
//#pragma GCC optimize("btr-bb-exclusive")
//#pragma GCC optimize("inline")
//#pragma GCC optimize("-fgcse")
//#pragma GCC optimize("-fgcse-lm")
//#pragma GCC optimize("-fipa-sra")
//#pragma GCC optimize("-ftree-pre")
//#pragma GCC optimize("-ftree-vrp")
//#pragma GCC optimize("-fpeephole2")
//#pragma GCC optimize("-ffast-math")
//#pragma GCC optimize("-fsched-spec")
//#pragma GCC optimize("-falign-jumps")
//#pragma GCC optimize("-falign-loops")
//#pragma GCC optimize("-falign-labels")
//#pragma GCC optimize("-fdevirtualize")
//#pragma GCC optimize("-fcaller-saves")
//#pragma GCC optimize("-fcrossjumping")
//#pragma GCC optimize("-fthread-jumps")
//#pragma GCC optimize("-freorder-blocks")
//#pragma GCC optimize("-fschedule-insns")
//#pragma GCC optimize("inline-functions")
//#pragma GCC optimize("-ftree-tail-merge")
//#pragma GCC optimize("-fschedule-insns2")
//#pragma GCC optimize("-fstrict-aliasing")
//#pragma GCC optimize("-falign-functions")
//#pragma GCC optimize("-fcse-follow-jumps")
//#pragma GCC optimize("-fsched-interblock")
//#pragma GCC optimize("-fpartial-inlining")
//#pragma GCC optimize("no-stack-protector")
//#pragma GCC optimize("-freorder-functions")
//#pragma GCC optimize("-findirect-inlining")
//#pragma GCC optimize("-fhoist-adjacent-loads")
//#pragma GCC optimize("-frerun-cse-after-loop")
//#pragma GCC optimize("inline-small-functions")
//#pragma GCC optimize("-finline-small-functions")
//#pragma GCC optimize("-ftree-switch-conversion")
//#pragma GCC optimize("-foptimize-sibling-calls")
//#pragma GCC optimize("-fexpensive-optimizations")
//#pragma GCC optimize("inline-functions-called-once")
//#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <iostream>
#include <list>
#include <vector>

using namespace std;

vector<vector<pair<int32_t, char>>> raw_g, raw_rev_g, cond_g;
vector<vector<int32_t>> max_cond_depth;
vector<bool> used;
vector<int32_t> order;
list<int32_t> dfs_now_component;
string best_res;
int32_t best_res_start;

void dfs1(int32_t v) {
    used[v] = true;
    for (auto [to, c]: raw_g[v]) if (!used[to]) dfs1(to);
    order.push_back(v);
}

void dfs2(int32_t v) {
    used[v] = true;
    dfs_now_component.push_back(v);
    for (auto [to, c]: raw_rev_g[v]) if (!used[to]) dfs2(to);
}

int32_t dfs4(int32_t v) {
    int32_t max_d = 0;
    max_cond_depth[v].resize(cond_g[v].size());
    for (int32_t i = 0; i < cond_g[v].size(); ++i) {
        max_cond_depth[v][i] = dfs4(cond_g[v][i].first) + 1;
        if (max_cond_depth[v][i] > max_d) max_d = max_cond_depth[v][i];
    }
    return max_d;
}

void dfs3(int32_t v, string &str) {
    int32_t max_depth = 0;
    for (int32_t i = 0; i < cond_g[v].size(); ++i)
        if (max_cond_depth[v][i] > max_depth)
            max_depth = max_cond_depth[v][i];
    for (int32_t _ = 0; _ < cond_g[v].size(); ++_) {
        if (max_cond_depth[v][_] < max_depth) continue;
        str += cond_g[v][_].second;
        dfs3(cond_g[v][_].first, str);
        if (str.size() >= best_res.size()) {
            
            int32_t best_start = 0;
            for (int32_t start = 0; start < str.size(); ++start) {
                bool is_less = false;
                for (int32_t i = 0; i < str.size(); ++i) {
                    if (str[(best_start + i) % str.size()] < str[(start + i) % str.size()]) break;
                    if (str[(best_start + i) % str.size()] > str[(start + i) % str.size()]) {
                        is_less = true;
                        break;
                    }
                }
                if (is_less) best_start = start;
            }
            if (str.size() > best_res.size()) best_res = str, best_res_start = best_start;
            else if (str.size() == best_res.size()) {
                bool is_less = false;
                for (int32_t i = 0; i < str.size(); ++i) {
                    if (best_res[(best_res_start + i) % str.size()] < str[(best_start + i) % str.size()]) break;
                    if (best_res[(best_res_start + i) % str.size()] > str[(best_start + i) % str.size()]) {
                        is_less = true;
                        break;
                    }
                }
                if (is_less) best_res = str, best_res_start = best_start;
            }
        }
        str.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int32_t n, m;
    cin >> n >> m;
    vector<list<pair<int32_t, char>>> l_raw_g(n), l_raw_rev_g(n);
    char temp_c;
    for (int32_t i = 0, u, v; i < m; ++i) {
        cin >> u >> v >> temp_c;
        l_raw_g[u - 1].emplace_back(v - 1, temp_c);
        l_raw_rev_g[v - 1].emplace_back(u - 1, temp_c);
    }
    raw_g.resize(n), raw_rev_g.resize(n);
    for (uint32_t i = 0; i < n; ++i) raw_g[i].assign(l_raw_g[i].begin(), l_raw_g[i].end());
    for (uint32_t i = 0; i < n; ++i) raw_rev_g[i].assign(l_raw_rev_g[i].begin(), l_raw_rev_g[i].end());
    l_raw_g.clear(), l_raw_rev_g.clear();
    used.assign(n, false);
    for (int32_t i = 0; i < n; ++i) if (!used[i]) dfs1(i);
    used.assign(n, false);
    vector<vector<uint32_t>> comps;
    comps.reserve(n);
    vector<int32_t> comp_on_v(n);
    for (int32_t i = 0; i < n; ++i) {
        int v = order[n - 1 - i];
        if (!used[v]) {
            dfs2(v);
            for (auto &u: dfs_now_component) comp_on_v[u] = comps.size();
            comps.emplace_back(dfs_now_component.begin(), dfs_now_component.end());
            dfs_now_component.clear();
        }
    }
    cond_g.resize(comps.size());
    for (int32_t comp_id = 0; comp_id < comps.size(); ++comp_id) {
        int32_t ways_cnt = 0;
        for (auto &v: comps[comp_id]) for (auto [to, c]: raw_g[v]) if (comp_on_v[to] != comp_id) ++ways_cnt;
        cond_g[comp_id].reserve(ways_cnt);
        for (auto &v: comps[comp_id])
            for (auto [to, c]: raw_g[v])
                if (comp_on_v[to] != comp_id)
                    cond_g[comp_id].emplace_back(comp_on_v[to], c);
    }
    int32_t start_comp = comp_on_v[0];
    max_cond_depth.resize(cond_g.size());
    dfs4(start_comp);
    string str;
    str.reserve(n);
    dfs3(start_comp, str);
    for (int32_t i = 0; i < best_res.size(); ++i) cout << best_res[(best_res_start + i) % best_res.size()];
    return 0;
}
