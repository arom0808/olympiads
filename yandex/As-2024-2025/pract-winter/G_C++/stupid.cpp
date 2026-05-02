#include <iostream>

using namespace std;
using ll = long long;

constexpr int maxn = 2e5;

struct ST {
public:
    int vals[maxn];
    int sz;

    void init(int val, int _sz) {
        sz = _sz;
        for (int i = 0; i < sz; ++i) vals[i] = val;
    }

    void set_min(int l, int r, int val) {
        for (int i = l; i < r; ++i) vals[i] = std::min(vals[i], val);
    }

    int get_min(int pos) const {
        return vals[pos];
    }
};

ST cols_st, rows_st;
int n, q;

void solve() {
    cin >> n >> q;
    int start_val;
    cin >> start_val;
    cols_st.init(start_val, n);
    for (int i = 0; i < q; ++i) {
        int t, a, b, c;
        cin >> t;
        if (t == 1) {
            cin >> a >> b >> c;
            cols_st.set_min(a, b, c);
        } else cin >> a, cout << cols_st.get_min(a) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    solve();
    return 0;
}
