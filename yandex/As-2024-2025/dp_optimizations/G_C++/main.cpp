#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

constexpr int maxn = 2e5, maxp = 1e6 + 1;
constexpr ll inf = 1e18;

struct Line {
    ll k, b;

    ll operator()(ll x) const {
        return k * x + b;
    }
};

namespace LiChao {
    Line tree[maxp * 4];

    void _init(int v, int l, int r) {
        tree[v] = {0, inf};
        if (r - l == 1) return;
        _init(v * 2, l, (l + r) / 2);
        _init(v * 2 + 1, (l + r) / 2, r);
    }

    void init() {
        _init(1, 0, maxp);
    }

    void _insert(int v, int l, int r, Line line) {
        auto mid = (l + r) / 2;
        if (line(mid) < tree[v](mid)) swap(tree[v], line);
        if (r - l <= 1) return;
        if (line(l) < tree[v](l)) _insert(v * 2, l, mid, line);
        else if (line(r - 1) < tree[v](r - 1)) _insert(v * 2 + 1, mid, r, line);
    }

    void insert(Line line) {
        _insert(1, 0, maxp, line);
    }

    ll _min_val(int v, int l, int r, int x) {
        if (r - l == 1) return tree[v](x);
        int mid = (l + r) / 2;
        ll nv;
        if (x < mid) nv = _min_val(v * 2, l, mid, x);
        else nv = _min_val(v * 2 + 1, mid, r, x);
        return std::min(tree[v](x), nv);
    }

    ll min_val(int x) {
        return _min_val(1, 0, maxp, x);
    }
}

pair<int, int> rects[maxn];
int n;
ll dp[maxn];

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> rects[i].first >> rects[i].second;
    sort(rects, rects + n, [](const pair<int, int> &a, const pair<int, int> &b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });
    vector<pair<int, int> > temp_rects;
    temp_rects.push_back(rects[n - 1]);
    for (int i = n - 2, pre = n - 1; i >= 0; --i) {
        if (rects[i].second > rects[pre].second) {
            temp_rects.push_back(rects[i]);
            pre = i;
        }
    }
    reverse(temp_rects.begin(), temp_rects.end());
    n = temp_rects.size();
    copy(temp_rects.begin(), temp_rects.end(), rects);
    LiChao::init();
    for (int i = 0; i < n; ++i) {
        LiChao::insert(Line(rects[i].second, i ? dp[i - 1] : 0ll));
        dp[i] = LiChao::min_val(rects[i].first);
    }
    cout << dp[n - 1] << "\n";
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
