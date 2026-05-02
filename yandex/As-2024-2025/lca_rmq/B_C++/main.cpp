#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 1e5;

namespace ST {
    int tree[maxn * 2 + 4];
    int size;

    void init(int _size) {
        size = _size + 1;
    }

    void _add_point(int r, int x) {
        for (++r; r <= size; r += r & (-r)) tree[r] += x;
    }

    // [0, r)
    int _pref_sum(int r) {
        int res = 0;
        for (; r; r -= r & (-r)) res += tree[r];
        return res;
    }

    void add(int l, int r, int x) {
        _add_point(l, x);
        _add_point(r, -x);
    }

    int get_val(int pos) {
        return _pref_sum(pos + 1);
    }
}

vector<int> euler;
int n, ar, br;
vector<int> ga[maxn], gb[maxn];
int tin[maxn], tout[maxn];
int64_t ans = 0;

void dfs_euler(int v) {
    tin[v] = tout[v] = euler.size();
    euler.push_back(v);
    for (auto u: gb[v]) dfs_euler(u), tout[v] = euler.size(), euler.push_back(v);
}

void dfs_ans(int v) {
    ans += ST::get_val(tin[v]);
    ST::add(tin[v], tout[v] + 1, 1);
    for (auto u: ga[v]) dfs_ans(u);
    ST::add(tin[v], tout[v] + 1, -1);
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0, cur_p; i < n; ++i) {
        cin >> cur_p, --cur_p;
        if (cur_p == -1) ar = i;
        else ga[cur_p].push_back(i);
    }
    for (int i = 0, cur_p; i < n; ++i) {
        cin >> cur_p, --cur_p;
        if (cur_p == -1) br = i;
        else gb[cur_p].push_back(i);
    }
    dfs_euler(br);
    ST::init(euler.size());
    dfs_ans(ar);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
