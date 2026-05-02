#include <iostream>
#include <deque>

using namespace std;

constexpr int maxn = 3e4, maxlen = 3e4 + 1, asz = 2;

namespace AhoCorasic {
    int p[maxlen];
    char pc[maxlen];
    int to[maxlen][asz], go[maxlen][asz];
    int link[maxlen];
    bool term[maxlen];
    int color[maxlen];

    void v_init(int v, int _p, char _pc) {
        p[v] = _p, pc[v] = _pc;
        for (int i = 0; i < asz; ++i) to[v][i] = -1;
        for (int i = 0; i < asz; ++i) go[v][i] = -1;
        link[v] = -1;
        term[v] = false;
        color[v] = 0;
    }

    int used_nodes = 0;
    int root = 0;

    int get_new_node(int _p, char _pc) {
        v_init(used_nodes, _p, _pc);
        return used_nodes++;
    }

    void init() {
        used_nodes = 0;
        root = get_new_node(-1, 0);
    }

    void add_str(const string &s) {
        int v = root;
        for (auto c: s) {
            if (to[v][c - '0'] == -1) to[v][c - '0'] = get_new_node(v, c - '0');
            v = to[v][c - '0'];
        }
        term[v] = true;
    }

    void calc_dp() {
        deque<int> d;
        d.push_back(root);
        while (!d.empty()) {
            int v = d.front();
            d.pop_front();

            if (v == root || p[v] == root) link[v] = root;
            else link[v] = go[link[p[v]]][pc[v]];

            for (char c = 0; c < asz; ++c) {
                if (to[v][c] != -1) go[v][c] = to[v][c];
                else if (v == root) go[v][c] = root;
                else go[v][c] = go[link[v]][c];
            }
            term[v] |= term[link[v]];

            for (auto u: to[v]) if (u != -1) d.push_back(u);
        }
    }

    bool dfs(int v) {
        if (term[v]) return false;
        if (color[v] == 1) return true;
        color[v] = 1;
        for (char c = 0; c < asz; ++c) if (color[go[v][c]] != 2 && dfs(go[v][c])) return true;
        color[v] = 2;
        return false;
    }

    bool get_ans() {
        return dfs(root);
    }
}

void solve() {
    int n;
    cin >> n;
    string ts;
    AhoCorasic::init();
    for (int i = 0; i < n; ++i) {
        cin >> ts;
        AhoCorasic::add_str(ts);
    }
    AhoCorasic::calc_dp();
    cout << (AhoCorasic::get_ans() ? "TAK" : "NIE") << "\n";
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
