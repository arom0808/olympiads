#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

constexpr int maxn = 2e5 + 10, maxcolor = maxn * 2;

int n;

namespace ColorST {
    int tree[maxcolor * 2];

    void init() {
        for (int i = maxcolor; i < maxcolor + n; ++i) tree[i] = 1;
        for (int i = maxcolor - 1; i; --i) tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }

    void add(int color, int val) {
        color += maxcolor;
        tree[color] += val;
        for (color >>= 1; color; color >>= 1) tree[color] = tree[color << 1] + tree[color << 1 | 1];
    }

    int sum(int l, int r) {
        l += maxcolor, r += maxcolor;
        int ans = 0;
        while (l != r) {
            if (l & 1) ans += tree[l++];
            if (r & 1) ans += tree[--r];
            l >>= 1, r >>= 1;
        }
        return ans;
    }
}

struct Seg {
    int start, color;

    Seg(int start, int color): start(start), color(color) {
    }

    bool operator<(const Seg &rhs) const {
        return start < rhs.start;
    }
};

vector<int> g[maxn];
int v_by_prior[maxcolor + 10];
int main_v_by_color[maxcolor + 10];
int next_prior;
int par[maxn], sz[maxn], head[maxn], tin[maxn], tout[maxn], hs[maxn];
int start_color[maxn];
int timer = 0;
set<Seg> segs;

void change_color_seg(int a, int b, int new_color) {
    auto fit = prev(segs.upper_bound(Seg(a, -1)));
    auto sit = segs.lower_bound(Seg(b, -1));
    auto fseg = *fit, sseg = *prev(sit);
    for (auto it = fit; it != sit; ++it)
        ColorST::add(it->color, it->start - next(it)->start);
    segs.erase(fit, sit);
    if (sit->start > b) {
        auto it = segs.emplace(b, sseg.color).first;
        ColorST::add(it->color, next(it)->start - it->start);
    }
    auto it = segs.emplace(a, new_color).first;
    ColorST::add(it->color, next(it)->start - it->start);
    if (fseg.start < a) {
        it = segs.insert(fseg).first;
        ColorST::add(it->color, next(it)->start - it->start);
    }
}

void dfs1(int v, int h = 0, int p = -1) {
    par[v] = p;
    hs[v] = h;
    if (p != -1) g[v].erase(find(g[v].begin(), g[v].end(), p));
    sz[v] = 1;
    for (auto u: g[v]) {
        dfs1(u, h + 1, v);
        sz[v] += sz[u];
    }
    for (auto &u: g[v]) if (sz[u] > sz[g[v][0]]) swap(u, g[v][0]);
}

void dfs2(int v) {
    tin[v] = timer++;
    for (auto u: g[v]) {
        head[u] = (u == g[v][0] ? head[v] : u);
        dfs2(u);
    }
    tout[v] = timer;
}

void calc_start_colors() {
    map<int, set<int> > vs_by_pow;
    vector<int> pows(n);
    for (int v = 0; v < n; ++v) pows[v] = g[v].size();
    for (int v = 0; v < n; ++v) vs_by_pow[pows[v]].insert(v);
    for (int col = 0; col + 1 < n; ++col) {
        auto v = *vs_by_pow[1].begin();
        start_color[v] = col;
        pows[v] = -1;
        vs_by_pow[1].erase(v);
        for (auto u: g[v]) {
            if (pows[u] == -1) continue;
            vs_by_pow[pows[u]].erase(u);
            vs_by_pow[--pows[u]].insert(u);
        }
    }
    start_color[*vs_by_pow[0].begin()] = n - 1;
}

bool anc(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

void set_up(int &a, int b, int color) {
    while (!anc(head[a], b)) {
        change_color_seg(tin[head[a]], tin[a] + 1, color);
        a = par[head[a]];
    }
}

void set_new_prior(int v) {
    if (v_by_prior[next_prior - 1] == v) return;
    int u = v_by_prior[next_prior - 1];
    int color = next_prior++;
    v_by_prior[color] = v;
    main_v_by_color[color] = u;
    set_up(v, u, color);
    set_up(u, v, color);
    if (!anc(u, v)) swap(u, v);
    change_color_seg(tin[u], tin[v] + 1, color);
}

void lca_up(int &a, int b) {
    while (!anc(head[a], b)) a = par[head[a]];
}

int lca(int a, int b) {
    lca_up(a, b);
    lca_up(b, a);
    if (!anc(a, b)) swap(a, b);
    return a;
}

int dist(int a, int b) {
    int c = lca(a, b);
    return hs[a] + hs[b] - 2 * hs[c];
}

int get_pos(int v) {
    int color = prev(segs.upper_bound(Seg(tin[v], -1)))->color;
    return ColorST::sum(0, color) + dist(v, main_v_by_color[color]);
}

void solve() {
    int q;
    cin >> n >> q;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    // for (int i = 0; i < n; ++i) prior[i] = i;
    for (int i = 0; i < n; ++i) v_by_prior[i] = i;
    calc_start_colors();
    next_prior = n;
    head[0] = hs[0] = 0;
    dfs1(0);
    dfs2(0);
    for (int v = 0; v < n; ++v) segs.emplace(tin[v], start_color[v]);
    for (int v = 0; v < n; ++v) main_v_by_color[start_color[v]] = v;
    segs.emplace(n, -1);
    ColorST::init();
    string rt;
    for (int _ = 0, v, u; _ < q; ++_) {
        cin >> rt;
        if (rt == "up") {
            cin >> v, --v;
            set_new_prior(v);
        } else if (rt == "when") {
            cin >> v, --v;
            cout << get_pos(v) + 1 << "\n";
        } else {
            cin >> v >> u, --v, --u;
            if (get_pos(v) < get_pos(u)) cout << v + 1 << "\n";
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
