#include <iostream>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>

using namespace std;

constexpr int maxn = 1e5, maxlen = 1e5 + 1;
constexpr int asz = 26;

bool ans[maxn];

struct Que {
    int l, r, id;

    bool operator<(const Que &rhs) const {
        if (l != rhs.l) return l < rhs.l;
        if (r != rhs.r) return r < rhs.r;
        return id < rhs.id;
    }
};

namespace AhoCorasic {
    struct PairRightCmp {
        bool operator()(const Que &p1, const Que &p2) const {
            if (p1.r != p2.r) return p1.r > p2.r;
            if (p1.l != p2.l) return p1.l < p2.l;
            return p1.id < p2.id;
        }
    };

    int p[maxlen], link[maxlen], superlink[maxlen];
    int go[maxlen][asz], to[maxlen][asz];
    char pc[maxlen];
    int next_q_id[maxlen];
    vector<Que> ques[maxlen];

    int used_nodes = 0;
    int root;

    void v_init(int v, int _p, char _pc) {
        p[v] = _p, pc[v] = _pc;
        link[v] = superlink[v] = -1;
        for (int i = 0; i < asz; ++i) go[v][i] = -1;
        for (int i = 0; i < asz; ++i) to[v][i] = -1;
    }

    int get_new_node(int _p, char _pc) {
        v_init(used_nodes, _p, _pc);
        return used_nodes++;
    }

    void init() {
        used_nodes = 0;
        root = get_new_node(-1, 0);
    }

    void add_que(const string &s, int l, int r, int q_id) {
        int v = root;
        for (auto c: s) {
            if (to[v][c - 'a'] == -1) to[v][c - 'a'] = get_new_node(v, c - 'a');
            v = to[v][c - 'a'];
        }
        if (l + s.size() - 1 <= r) ques[v].emplace_back(l + s.size() - 1, r, q_id);
    }

    void calc_dp() {
        deque<int> d;
        d.push_back(root);
        while (!d.empty()) {
            int v = d.front();
            d.pop_front();

            sort(ques[v].begin(), ques[v].end());

            if (v == root || p[v] == root) link[v] = root;
            else link[v] = go[link[p[v]]][pc[v]];

            if (v == root) superlink[v] = -1;
            else if (!ques[link[v]].empty()) superlink[v] = link[v];
            else superlink[v] = superlink[link[v]];

            for (char c = 0; c < asz; ++c) {
                if (to[v][c] != -1) go[v][c] = to[v][c];
                else if (v != root) go[v][c] = go[link[v]][c];
                else go[v][c] = root;
            }

            for (auto c: to[v]) if (c != -1) d.push_back(c);
        }
    }

    vector<Que> tqv;

    int get_superlink(int v) {
        if (superlink[v] != -1 && next_q_id[superlink[v]] == ques[superlink[v]].size())
            superlink[v] = superlink[superlink[v]];
        return superlink[v];
    }

    void gen_ans(const string &s) {
        int v = root;
        for (int i = 0; i < s.size(); ++i) {
            v = go[v][s[i] - 'a'];
            for (int u = v; u != -1; u = get_superlink(u)) {
                while (next_q_id[u] < ques[u].size() && ques[u][next_q_id[u]].l <= i)
                    tqv.push_back(ques[u][next_q_id[u]++]);
                sort(tqv.begin(), tqv.end(), PairRightCmp());
                while (!tqv.empty() && tqv.back().r < i)
                    tqv.pop_back();
                for (auto [l,r,id]: tqv) ans[id] = true;
                tqv.clear();
            }
        }
    }
}

void solve() {
    string ms;
    cin >> ms;
    int n;
    cin >> n;
    string ts;
    AhoCorasic::init();
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r >> ts, --l, --r;
        AhoCorasic::add_que(ts, l, r, i);
    }
    AhoCorasic::calc_dp();
    AhoCorasic::gen_ans(ms);
    for (int i = 0; i < n; ++i) cout << (ans[i] ? '+' : '-');
    cout << "\n";
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
