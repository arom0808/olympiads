#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using ll = int64_t;

template<typename T>
inline T iceil(T a, T b) {
    return (a + b - 1) / b;
}

constexpr int maxn = 2e5;
constexpr ll inf = 2e18;
int n, m;

struct Pizzeria {
    int s, p;
};

struct Client {
    int id, c;
    vector<int> banned_pizzerias;
};

Pizzeria pizzerias[maxn];
Client clients[maxn];
ll ans[maxn];

struct Line {
    ll k, b;

    Line(ll k = 0, ll b = 0): k(k), b(b) {
    }

    ll operator()(ll x) const {
        return k * x + b;
    }
};

ll intersect(Line a, Line b) {
    if (a.k == b.k) return a.b > b.b ? -inf : inf;
    return iceil(b.b - a.b, a.k - b.k);
}

namespace ST {
    struct Node {
        vector<pair<ll, Line> > cht;
        int luid;

        ll get_min(ll x) {
            while (luid + 1 < cht.size() && cht[luid + 1].first <= x) ++luid;
            return cht[luid].second(x);
        }
    };

    Node nodes[maxn * 4];
    int size;

    void upd_from_child(int v, int l, int r) {
        if (r - l <= 1) return;
        auto &ccht = nodes[v].cht;
        const auto &cht1 = nodes[v * 2].cht, &cht2 = nodes[v * 2 + 1].cht;
        for (int i1 = 0, i2 = 0; i1 < cht1.size() || i2 < cht2.size();) {
            Line cl;
            if (i2 == cht2.size() || (i1 != cht1.size() && cht1[i1].second.k > cht2[i2].second.k))
                cl = cht1[i1++].second;
            else cl = cht2[i2++].second;
            while (!ccht.empty()) {
                ll ix = intersect(ccht.back().second, cl);
                if (ix <= ccht.back().first) ccht.pop_back();
                else {
                    ccht.emplace_back(ix, cl);
                    break;
                }
            }
            if (ccht.empty()) ccht.emplace_back(-inf, cl);
        }
    }

    void _build(int v, int l, int r) {
        nodes[v].luid = 0;
        if (r - l == 1) {
            nodes[v].cht.emplace_back(
                -inf, Line(-2 * pizzerias[l].s, 1ll * pizzerias[l].s * pizzerias[l].s + pizzerias[l].p));
            return;
        }
        int mid = (l + r) / 2;
        _build(v * 2, l, mid);
        _build(v * 2 + 1, mid, r);
        upd_from_child(v, l, r);
    }

    ll _get_min(int v, int l, int r, int a, int b, ll x) {
        if (l >= r || l >= b || a >= r) return inf;
        if (a <= l && r <= b) return nodes[v].get_min(x);
        int mid = (l + r) / 2;
        return std::min(_get_min(v * 2, l, mid, a, b, x), _get_min(v * 2 + 1, mid, r, a, b, x));
    }

    void build() {
        size = n;
        _build(1, 0, size);
    }

    ll get_min(int a, int b, ll x) {
        return _get_min(1, 0, size, a, b, x);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> pizzerias[i].s >> pizzerias[i].p;
    for (int i = 0, tk; i < m; ++i) {
        clients[i].id = i;
        cin >> clients[i].c >> tk;
        clients[i].banned_pizzerias.resize(tk);
        for (auto &el: clients[i].banned_pizzerias) cin >> el, --el;
        sort(clients[i].banned_pizzerias.begin(), clients[i].banned_pizzerias.end());
    }
    ST::build();
    sort(begin(clients), next(begin(clients), m), [](const Client &a, const Client &b) {
        return a.c < b.c;
    });
    for (int i = 0; i < m; ++i) {
        ll cans = inf;
        int pre_banned = -1;
        for (auto cban: clients[i].banned_pizzerias) {
            if (pre_banned + 1 != cban) cans = std::min(cans, ST::get_min(pre_banned + 1, cban, clients[i].c));
            pre_banned = cban;
        }
        if (pre_banned + 1 != n) cans = std::min(cans, ST::get_min(pre_banned + 1, n, clients[i].c));
        ans[clients[i].id] = cans + 1ll * clients[i].c * clients[i].c;
    }
    for (int i = 0; i < m; ++i) cout << ans[i] << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    // freopen("input.txt", "r",stdin);
    solve();
    return 0;
}
