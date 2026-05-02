#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>
#include <array>

using namespace std;

constexpr int maxn = 1e5, maxlen = 4e5 + 1, asz = 26;

int qs_pos_by_c[asz];

namespace Bor {
    int to[maxlen][asz];
    int par[maxlen], pc[maxlen], to_par_term_cnt[maxlen], ch_cnt[maxlen], scnt[maxlen];
    int fans[maxlen];
    bool term[maxlen];

    void v_init(int v, int _par, int _pc) {
        for (int i = 0; i < asz; ++i) to[v][i] = -1;
        par[v] = _par;
        pc[v] = _pc;
        to_par_term_cnt[v] = ch_cnt[v] = scnt[v] = 0;
        term[v] = false;
    }

    int v_by_sid[maxn];
    int nodes_used = 0;
    int root;

    int get_new_node(int _par, int _pc) {
        v_init(nodes_used, _par, _pc);
        return nodes_used++;
    }

    void init() {
        nodes_used = 0;
        root = get_new_node(-1, -1);
    }

    void add_str(const string &s, int sid) {
        int v = root;
        for (char rc: s) {
            ++scnt[v];
            int c = rc - 'a';
            if (to[v][c] == -1) to[v][c] = get_new_node(v, c), ++ch_cnt[v];
            v = to[v][c];
        }
        ++scnt[v];
        term[v] = true;
        v_by_sid[sid] = v;
    }

    bool dfs_compress(int v) {
        if (par[v] != -1 && ch_cnt[v] == 1) {
            int cid = 0;
            for (; cid < asz; ++cid) if (to[v][cid] != -1) break;
            auto u = to[v][cid];
            to[par[v]][pc[v]] = u;
            par[u] = par[v];
            pc[u] = pc[v];
            to_par_term_cnt[u] = to_par_term_cnt[v] + term[v];
            return true;
        }
        for (int i = 0; i < asz; ++i) {
            if (to[v][i] == -1) continue;
            while (dfs_compress(to[v][i])) {
            }
        }
        for (int i = 0; i < asz; ++i) if (to[v][i] != -1) fans[v] += scnt[to[v][i]] + to_par_term_cnt[to[v][i]];
        return false;
    }

    void compress() {
        dfs_compress(0);
    }

    // int max_depth(int v) {
    //     int res = 0;
    //     for (int i = 0; i < asz; ++i) {
    //         if (to[v][i] != -1) res = std::max(res, max_depth(to[v][i]));
    //     }
    //     return res + 1;
    // }

    int cnt_less(int sid, const string &alpha_s) {
        int v = v_by_sid[sid];
        int res = to_par_term_cnt[v];
        int _pc = pc[v];
        v = par[v];
        while (v != -1) {
            if (term[v]) ++res;
            if (qs_pos_by_c[_pc] < 13) {
                for (int i = 0; i < asz; ++i) {
                    int ca = alpha_s[i] - 'a';
                    if (ca == _pc) break;
                    if (to[v][ca] != -1) res += scnt[to[v][ca]] + to_par_term_cnt[to[v][ca]];
                }
            } else {
                res += fans[v];
                for (int i = asz - 1; i >= 0; --i) {
                    int ca = alpha_s[i] - 'a';
                    if (to[v][ca] != -1) res -= scnt[to[v][ca]] + to_par_term_cnt[to[v][ca]];
                    if (ca == _pc) break;
                }
            }
            res += to_par_term_cnt[v];
            _pc = pc[v];
            v = par[v];
        }
        return res;
    }
}

int n;

void solve() {
    cin >> n;
    string temp_str;
    Bor::init();
    for (int i = 0; i < n; ++i) {
        cin >> temp_str;
        Bor::add_str(temp_str, i);
    }
    Bor::compress();
    // if (Bor::max_depth(0) >= 900) throw std::runtime_error("hee");
    // if (n >= 100000) throw std::runtime_error("gee");
    int q;
    cin >> q;
    for (int _ = 0, k; _ < q; ++_) {
        cin >> k >> temp_str;
        for (int i = 0; i < asz; ++i) qs_pos_by_c[temp_str[i] - 'a'] = i;
        cout << Bor::cnt_less(k - 1, temp_str) + 1 << "\n";
    }
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
