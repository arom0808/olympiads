#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
constexpr int maxn = 150001;
constexpr int64_t inf = 1e16;

namespace ST {
    struct Node {
        int64_t sum = 0;
    };

    Node tree[maxn * 4];
    int size;

    void _init(int v, int l, int r) {
        if (r - l == 1) {
            tree[v].sum = 0;
            return;
        }
        tree[v].sum = tree[v * 2].sum + tree[v * 2 + 1].sum;
    }

    void _add(int v, int l, int r, int pos, int64_t val) {
        if (l >= pos + 1 || pos >= r) return;
        if (l == pos && r == pos + 1) {
            tree[v].sum += val;
            return;
        }
        _add(v * 2, l, (l + r) / 2, pos, val), _add(v * 2 + 1, (l + r) / 2, r, pos, val);
        tree[v].sum = tree[v * 2].sum + tree[v * 2 + 1].sum;
    }

    int64_t _sum(int v, int l, int r, int a, int b) {
        if (l >= b || a >= r) return 0;
        if (a <= l && r <= b) return tree[v].sum;
        return _sum(v * 2, l, (l + r) / 2, a, b) + _sum(v * 2 + 1, (l + r) / 2, r, a, b);
    }

    void init(int _size) {
        size = _size;
        _init(1, 0, size);
    }

    void add(int pos, int64_t val) {
        _add(1, 0, size, pos, val);
    }

    int64_t sum(int a, int b) {
        return _sum(1, 0, size, a, b);
    }
}

int n, m;
int64_t arr[maxn];
int64_t g_ans[maxn];

struct Que {
    int id, l, r;
    int64_t ans = 1;

    bool operator<(const Que &rhs) const {
        if (ans != rhs.ans) return ans < rhs.ans;
        return id < rhs.id;
    }
};

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    arr[n++] = inf;
    vector<pair<int64_t, int> > to_add_arr(n);
    for (int i = 0; i < n; ++i) to_add_arr[i] = {arr[i], i};
    sort(to_add_arr.begin(), to_add_arr.end());
    ST::init(n);
    set<Que> ques;
    for (int i = 0; i < m; ++i) {
        Que que;
        cin >> que.l >> que.r, --que.l;
        que.id = i;
        ques.insert(que);
    }
    for (auto to_add_it = to_add_arr.begin(); to_add_it != to_add_arr.end();) {
        int64_t to_add_val = to_add_it->first;
        while (!ques.empty() && to_add_val > ques.begin()->ans) {
            auto que = *ques.begin();
            ques.erase(ques.begin());
            int64_t cur_sum = ST::sum(que.l, que.r) - (que.ans - 1);
            que.ans += cur_sum;
            g_ans[que.id] = que.ans;
            if (cur_sum != 0) ques.insert(que);
        }
        do {
            ST::add(to_add_it->second, to_add_val);
            ++to_add_it;
        } while (to_add_it != to_add_arr.end() && to_add_it->first == prev(to_add_it)->first);
    }
    for (int i = 0; i < m; ++i) cout << g_ans[i] << "\n";
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
