#include <algorithm>
#include <iostream>
#include <array>
#include <set>
#include <vector>

using namespace std;

constexpr int inf = 1e8;
constexpr int maxn = 1e5, maxk = 50;
int n, k, m;

namespace ST {
    struct Node {
        array<int, maxk> left_poss, right_poss, sorted_left_vals;
        int ans;

        void init(int pos, int val) {
            left_poss.fill(inf), right_poss.fill(-1), sorted_left_vals.fill(inf);
            left_poss[val] = right_poss[val] = pos;
            sorted_left_vals[0] = val;
            ans = (k == 1) ? 1 : inf;
        }
    };

    Node tree[maxn * 4];
    int size;
    array<bool, maxk> temp_arr;

    void upd_from_child(int v, int l, int r) {
        if (r - l == 1) return;
        tree[v].sorted_left_vals.fill(inf);
        int sorted_poss_cnt = 0;
        for (int i = 0; i < k; ++i) {
            if (tree[v * 2].sorted_left_vals[i] != inf)
                tree[v].sorted_left_vals[sorted_poss_cnt++] = tree[v * 2].sorted_left_vals[i];
            tree[v].left_poss[i] = std::min(tree[v * 2].left_poss[i], tree[v * 2 + 1].left_poss[i]);
            tree[v].right_poss[i] = std::max(tree[v * 2].right_poss[i], tree[v * 2 + 1].right_poss[i]);
        }
        for (int i = 0; i < k && tree[v * 2 + 1].sorted_left_vals[i] != inf; ++i)
            if (tree[v * 2].left_poss[tree[v * 2 + 1].sorted_left_vals[i]] == inf)
                tree[v].sorted_left_vals[sorted_poss_cnt++] = tree[v * 2 + 1].sorted_left_vals[i];
        tree[v].ans = std::min(tree[v * 2].ans, tree[v * 2 + 1].ans);
        int cnt_in_set = 0;
        temp_arr.fill(false);
        for (auto el: tree[v * 2 + 1].sorted_left_vals) {
            if (el == inf) break;
            ++cnt_in_set;
            temp_arr[el] = true;
        }
        int segl = (l + r) / 2;
        for (int i = 0; i < k; ++i) {
            if (temp_arr[i]) continue;
            if (tree[v * 2].right_poss[i] == -1) return;
            ++cnt_in_set, temp_arr[i] = true, segl = std::min(segl, tree[v * 2].right_poss[i]);
        }
        for (int i = k - 1; i >= 0; --i) {
            if (tree[v * 2 + 1].sorted_left_vals[i] == inf) continue;
            auto cval = tree[v * 2 + 1].sorted_left_vals[i];
            int segr = tree[v * 2 + 1].left_poss[cval];
            tree[v].ans = std::min(tree[v].ans, segr - segl + 1);
            if (tree[v * 2].right_poss[cval] == -1) return;
            segl = std::min(segl, tree[v * 2].right_poss[cval]);
        }
    }

    void _build(int v, int l, int r, const vector<int> &arr) {
        if (r - l == 1) {
            tree[v].init(l, arr[l]);
            return;
        }
        int mid = (l + r) / 2;
        _build(v * 2, l, mid, arr);
        _build(v * 2 + 1, mid, r, arr);
        upd_from_child(v, l, r);
    }

    void _change(int v, int l, int r, int pos, int val) {
        if (l >= pos + 1 || pos >= r) return;
        if (l == pos && r == pos + 1) {
            tree[v].init(l, val);
            return;
        }
        int mid = (l + r) / 2;
        _change(v * 2, l, mid, pos, val);
        _change(v * 2 + 1, mid, r, pos, val);
        upd_from_child(v, l, r);
    }

    void build(const vector<int> &arr) {
        size = arr.size();
        _build(1, 0, size, arr);
    }

    void change(int pos, int val) {
        _change(1, 0, size, pos, val);
    }

    int mfsl() {
        return tree[1].ans;
    }
}

void solve() {
    cin >> n >> k >> m;
    vector<int> arr(n);
    for (auto &el: arr) cin >> el, --el;
    ST::build(arr);
    for (int i = 0, t, p, u; i < m; ++i) {
        cin >> t;
        if (t == 1) {
            cin >> p >> u, --p, --u;
            ST::change(p, u);

        } else {
            int ans = ST::mfsl();
            cout << (ans == inf ? -1 : ans) << "\n";
        }
    }
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
