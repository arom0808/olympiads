#include <algorithm>
#include <iostream>

using namespace std;

constexpr int32_t maxk = 1e7 + 5;
constexpr int32_t maxn = 1e5 + 5;

namespace ST {
    struct Node {
        int64_t sum = 0, change = 0;
        int32_t l, r;

        void init() {
            l = r = -1;
        }
    };

    Node tree[maxk];
    int32_t size;
    int used_cnt = 1;

    void add_children(int v, int l, int r) {
        if (r - l <= 1) return;
        if (tree[v].l != -1) return;
        tree[v].l = used_cnt++;
        tree[v].r = used_cnt++;
        tree[tree[v].l].init();
        tree[tree[v].r].init();
        tree[tree[v].l].sum = tree[v].change * ((l + r) / 2 - l), tree[tree[v].l].change = tree[v].change;
        tree[tree[v].r].sum = tree[v].change * (r - (l + r) / 2), tree[tree[v].r].change = tree[v].change;
        tree[v].change = 0;
    }

    void transfer_changes(int32_t v, int32_t l, int32_t r) {
        if (!tree[v].change) return;
        if (r - l > 1) {
            tree[tree[v].l].change += tree[v].change, tree[tree[v].l].sum += tree[v].change;
            tree[tree[v].r].change += tree[v].change, tree[tree[v].r].sum += tree[v].change;
        }
        tree[v].change = 0;
    }

    int64_t _sum(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || l >= b || a >= r) return 0;
        if (a <= l && r <= b) return tree[v].sum;
        add_children(v, l, r);
        transfer_changes(v, l, r);
        return _sum(tree[v].l, l, (l + r) / 2, a, b) + _sum(tree[v].r, (l + r) / 2, r, a, b);
    }

    void _add(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b, int64_t val) {
        if (l >= r || l >= b || a >= r) return;
        if (a <= l && r <= b) {
            tree[v].sum += val * (r - l), tree[v].change += val;
            return;
        }
        add_children(v, l, r);
        transfer_changes(v, l, r);
        _add(tree[v].l, l, (l + r) / 2, a, b, val);
        _add(tree[v].r, (l + r) / 2, r, a, b, val);
        tree[v].sum = tree[tree[v].l].sum + tree[tree[v].r].sum;
    }

    int64_t sum(int32_t a, int32_t b) {
        return _sum(0, 0, size, a, b);
    }

    void add(int32_t a, int32_t b, int64_t val) {
        _add(0, 0, size, a, b, val);
    }

    void init(int32_t sz) {
        size = sz;
        tree[0].init();
    }
}

struct Rec {
    int32_t l, r, t, v;

    bool operator<(const Rec &rhs) const {
        return t < rhs.t;
    }

    friend istream &operator>>(istream &is, Rec &rec) {
        is >> rec.l >> rec.r >> rec.t >> rec.v;
        return is;
    }
};

struct Req {
    int32_t id, l, r, t;

    bool operator<(const Req &rhs) const {
        return t < rhs.t;
    }

    friend istream &operator>>(istream &is, Req &req) {
        is >> req.l >> req.r >> req.t;
        return is;
    }
};

Rec recs[maxn];
Req reqs[maxn];
int64_t ans[maxn];
int k, n, m;

void solve() {
    cin >> k >> n;
    ++k;
    ST::init(k);
    for (int i = 0; i < n; ++i) cin >> recs[i];
    sort(recs, recs + n);
    cin >> m;
    for (int i = 0; i < m; ++i) cin >> reqs[i], reqs[i].id = i;
    sort(reqs, reqs + m);
    for (int i = 0, next_rec = 0; i < m; ++i) {
        while (next_rec < n && recs[next_rec].t <= reqs[i].t) {
            auto [l,r,t,v] = recs[next_rec];
            ST::add(l, r + 1, v);
            ++next_rec;
        }
        auto [id,l,r,t] = reqs[i];
        ans[id] = ST::sum(l, r + 1);
    }
    for (int i = 0; i < m; ++i) cout << ans[i] << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    solve();
#endif
    return 0;
}


//
// struct PV {
//     int x, y;
//
//     static int64_t square_dist(PV a, PV b) {
//         return 1ll * (a.x - b.x) * (a.x - b.x) + 1ll * (a.y - b.y) * (a.y - b.y);
//     }
// };
//
// struct Circle {
//     PV center;
//     int r, id;
//
//     static bool cross(Circle a, Circle b) {
//         return PV::square_dist(a.center, b.center) <= 1ll * (a.r + b.r) * (a.r + b.r);
//     }
//
//     bool operator<(const Circle &b) const {
//         if (r != b.r) return r > b.r;
//         return id < b.id;
//     }
// };
//
// struct FlatCircle {
//     int x, r, id;
// };
//
// constexpr int maxn = 3e5;
// int n;
// Circle raw_circles[maxn];
// const int inf = 2e9 + 1;
// int ans[maxn];
// bool all_y_0 = true;
//
// namespace ST {
//     struct Node {
//         pair<int, int> max_val = {-inf, 0}, min_val = {inf, 0};
//     };
//
//     Node tree[maxn * 4];
//     int size;
//
//     void _build(int v, int l, int r, const vector<FlatCircle> &circles) {
//         if (r - l == 1) {
//             tree[v] = {{circles[l].r + circles[l].x, l}, {circles[l].x - circles[l].r, l}};
//             return;
//         }
//         int mid = (l + r) / 2;
//         _build(v * 2, l, mid, circles);
//         _build(v * 2 + 1, mid, r, circles);
//         tree[v].min_val = std::min(tree[v * 2].min_val, tree[v * 2 + 1].min_val);
//         tree[v].max_val = std::max(tree[v * 2].max_val, tree[v * 2 + 1].max_val);
//     }
//
//     pair<int, int> _get_max(int v, int l, int r, int a, int b) {
//         if (l >= b || a >= r) return {-inf, l};
//         if (a <= l && r <= b) return tree[v].max_val;
//         int mid = (l + r) / 2;
//         return std::max(_get_max(v * 2, l, mid, a, b), _get_max(v * 2 + 1, mid, r, a, b));
//     }
//
//     pair<int, int> _get_min(int v, int l, int r, int a, int b) {
//         if (l >= b || a >= r) return {inf, l};
//         if (a <= l && r <= b) return tree[v].min_val;
//         int mid = (l + r) / 2;
//         return std::min(_get_min(v * 2, l, mid, a, b), _get_min(v * 2 + 1, mid, r, a, b));
//     }
//
//     void _erase(int v, int l, int r, int pos) {
//         if (l >= pos + 1 || pos >= r) return;
//         if (l == pos && r == pos + 1) tree[v] = {{-inf, l}, {inf, l}};
//         else {
//             _erase(v * 2, l, (l + r) / 2, pos), _erase(v * 2 + 1, (l + r) / 2, r, pos);
//             tree[v].min_val = std::min(tree[v * 2].min_val, tree[v * 2 + 1].min_val);
//             tree[v].max_val = std::max(tree[v * 2].max_val, tree[v * 2 + 1].max_val);
//         }
//     }
//
//     void build(const vector<FlatCircle> &circles) {
//         size = circles.size();
//         _build(1, 0, size, circles);
//     }
//
//     pair<int, int> get_max(int a, int b) {
//         return _get_max(1, 0, size, a, b);
//     }
//
//     pair<int, int> get_min(int a, int b) {
//         return _get_min(1, 0, size, a, b);
//     }
//
//     void erase(int pos) {
//         _erase(1, 0, size, pos);
//     }
// }
//
// vector<FlatCircle> flat_ccs;
//
// struct flat_cmp {
//     bool operator()(int a, int b) const {
//         if (flat_ccs[a].r != flat_ccs[b].r) return flat_ccs[a].r > flat_ccs[b].r;
//         return flat_ccs[a].id < flat_ccs[b].id;
//     }
// };
//
// void all_y_0_solve() {
//     flat_ccs.resize(n);
//     for (int i = 0; i < n; ++i) flat_ccs[i] = {raw_circles[i].center.x, raw_circles[i].r, raw_circles[i].id};
//     sort(flat_ccs.begin(), flat_ccs.end(), [](const FlatCircle &a, const FlatCircle &b) {
//         if (a.x != b.x) return a.x < b.x;
//         return a.id < b.id;
//     });
//     ST::build(flat_ccs);
//     set<int, flat_cmp> circles_set;
//     for (int i = 0; i < n; ++i) circles_set.insert(i);
//     while (!circles_set.empty()) {
//         auto mc_pos = *circles_set.begin();
//         circles_set.erase(circles_set.begin());
//         ST::erase(mc_pos);
//         ans[flat_ccs[mc_pos].id] = flat_ccs[mc_pos].id;
//         while (ST::get_max(0, mc_pos).first >= flat_ccs[mc_pos].x - flat_ccs[mc_pos].r) {
//             auto [s_val, s_pos] = ST::get_max(0, mc_pos);
//             ST::erase(s_pos);
//             circles_set.erase(s_pos);
//             ans[flat_ccs[s_pos].id] = flat_ccs[mc_pos].id;
//         }
//         while (ST::get_min(mc_pos + 1, n).first <= flat_ccs[mc_pos].x + flat_ccs[mc_pos].r) {
//             auto [s_val,s_pos] = ST::get_min(mc_pos + 1, n);
//             ST::erase(s_pos);
//             circles_set.erase(s_pos);
//             ans[flat_ccs[s_pos].id] = flat_ccs[mc_pos].id;
//         }
//     }
// }
//
// void small_n_solve() {
//     set circles(begin(raw_circles), next(begin(raw_circles), n));
//     while (!circles.empty()) {
//         auto f_it = circles.begin();
//         ans[f_it->id] = f_it->id;
//         for (auto s_it = f_it; next(s_it) != circles.end();) {
//             if (Circle::cross(*f_it, *next(s_it))) {
//                 ans[next(s_it)->id] = f_it->id;
//                 circles.erase(next(s_it));
//             } else ++s_it;
//         }
//         circles.erase(f_it);
//     }
// }

// void solve() {
//     cin >> n;
//     for (int i = 0; i < n; ++i) {
//         Circle c;
//         cin >> c.center.x >> c.center.y >> c.r;
//         if (c.center.y) all_y_0 = false;
//         c.id = i;
//         raw_circles[i] = c;
//     }
//     if (all_y_0) all_y_0_solve();
//     else small_n_solve();
//     for (int i = 0; i < n; ++i) cout << ans[i] + 1 << " ";
//     cout << "\n";
// }
