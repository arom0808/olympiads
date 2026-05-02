#include <iostream>

using namespace std;

constexpr int maxn = 1e6, maxlen = 1e6 + 1, asz = 26;

int ans[maxn], cnt_ans[maxn], starts_ans[maxn + 1];
int n;

namespace AhoCoras {
    int ps[maxlen], link[maxlen], superlink[maxlen], len[maxlen];
    int to[maxlen][asz], go[maxlen][asz];
    int sid[maxlen];
    char pc[maxlen];

    void init_v(int v, int _p = -1, char _pc = 0, int _len = 0) {
        ps[v] = _p, pc[v] = _pc, len[v] = _len;
        link[v] = superlink[v] = -1;
        for (int i = 0; i < asz; ++i) to[v][i] = -1;
        for (int i = 0; i < asz; ++i) go[v][i] = -1;
        sid[v] = -1;
    }

    int root = 0;
    int nodes_used = 0;

    int get_new_node(int _p = -1, char _pc = 0, int _len = 0) {
        init_v(nodes_used, _p, _pc, _len);
        return nodes_used++;
    }

    void init() {
        nodes_used = 0;
        root = get_new_node();
    }

    int add_str(const string &s, int _sid) {
        auto v = root;
        for (auto c: s) {
            if (to[v][c - 'a'] == -1) to[v][c - 'a'] = get_new_node(v, c - 'a', len[v] + 1);
            v = to[v][c - 'a'];
        }
        if (sid[v] == -1) sid[v] = _sid;
        return sid[v];
    }

    int d[maxlen];
    int d_start, d_end;

    void calc_dp() {
        d[d_start] = root;
        d_start = 0, d_end = 1;
        while (d_start != d_end) {
            auto v = d[d_start++];

            if (v == root || ps[v] == root) link[v] = root;
            else link[v] = go[link[ps[v]]][pc[v]];

            if (v == root) superlink[v] = -1;
            else if (sid[link[v]] != -1) superlink[v] = link[v];
            else superlink[v] = superlink[link[v]];

            for (char c = 0; c < asz; ++c) {
                if (to[v][c] != -1) go[v][c] = to[v][c];
                else if (v != root) go[v][c] = go[link[v]][c];
                else go[v][c] = root;
            }

            for (auto c: to[v]) if (c != -1) d[d_end++] = c;
        }
    }

    void gen_ans(const string &s) {
        int v = root;
        for (auto c: s) {
            v = go[v][c - 'a'];
            for (auto u = v; u != -1; u = superlink[u]) if (sid[u] != -1) ++cnt_ans[sid[u]];
        }
        starts_ans[0] = 0;
        for (int i = 0; i < n; ++i) starts_ans[i + 1] = starts_ans[i] + cnt_ans[i];
        v = root;
        for (int i = 0; i < s.size(); ++i) {
            v = go[v][s[i] - 'a'];
            for (auto u = v; u != -1; u = superlink[u]) if (sid[u] != -1) ans[starts_ans[sid[u]]++] = i - len[u] + 1;
        }
        starts_ans[0] = 0;
        for (int i = 0; i < n; ++i) starts_ans[i + 1] = starts_ans[i] + cnt_ans[i];
    }
}

int r_id[maxn];

void solve() {
    string s, ts;
    cin >> s;
    cin >> n;
    AhoCoras::init();
    for (int i = 0; i < n; ++i) {
        cin >> ts;
        r_id[i] = AhoCoras::add_str(ts, i);
    }
    ts.clear(), ts.shrink_to_fit();
    AhoCoras::calc_dp();
    AhoCoras::gen_ans(s);
    for (int i = 0; i < n; ++i) {
        cout << starts_ans[r_id[i] + 1] - starts_ans[r_id[i]] << " ";
        for (int j = starts_ans[r_id[i]]; j < starts_ans[r_id[i] + 1]; ++j) cout << ans[j] + 1 << " ";
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    freopen("inputik.txt", "r", stdin);
    freopen("outputik.txt", "w", stdout);
#endif
    solve();
    return 0;
}
