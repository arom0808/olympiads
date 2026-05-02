#include <iostream>

using namespace std;
using ll = long long;

constexpr int maxn = 2e5;

struct ST {
public:
    int tree[maxn * 2];
    int sz;

    void init(int val, int _sz) {
        sz = _sz;
        for (int i = 0; i < sz * 2; ++i) tree[i] = val;
    }

    void set_min(int l, int r, int val) {
        l += sz, r += sz;
        while (l < r) {
            if (l & 1) tree[l] = std::min(tree[l], val), ++l;
            if (r & 1) --r, tree[r] = std::min(tree[r], val);
            l >>= 1, r >>= 1;
        }
    }

    int get_min(int pos) const {
        pos += sz;
        int ans = tree[pos];
        while (pos) {
            ans = std::min(ans, tree[pos]);
            pos >>= 1;
        }
        return ans;
    }
};

ST cols_st, rows_st;
int n, q;

void solve() {
    cin >> n >> q;
    ll ans = 1ll * (n - 2) * (n - 2);
    cols_st.init(n - 1, n), rows_st.init(n - 1, n);
    for (int i = 0, t, x; i < q; ++i) {
        cin >> t >> x, --x;
        if (t == 1) {
            int near_white = cols_st.get_min(x);
            ans -= near_white - 1;
            rows_st.set_min(1, near_white, x);
        } else {
            int near_white = rows_st.get_min(x);
            ans -= near_white - 1;
            cols_st.set_min(1, near_white, x);
        }
    }
    cout << ans << "\n";
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
