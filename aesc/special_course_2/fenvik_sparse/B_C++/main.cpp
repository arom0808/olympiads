#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class SparseTable {
    vector<vector<uint32_t>> st;

    void init_rows() {
        for (uint32_t k = 1; k < st.size(); ++k)
            for (uint32_t i = 0; i + (1 << (k - 1)) < st[k].size(); ++i)
                st[k][i] = std::min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }

public:
    [[nodiscard]] uint32_t min(uint32_t l, uint32_t r) const {
        uint32_t k = __lg(r - l);
        return std::min(st[k][l], st[k][r - (1 << k)]);
    }

    explicit SparseTable(uint32_t n, uint32_t init_val, const function<uint32_t(uint32_t)> &val_by_prev) :
            st(__lg(n) + 1, vector<uint32_t>(n)) {
        st[0][0] = init_val;
        for (uint32_t i = 1; i < n; ++i) st[0][i] = val_by_prev(st[0][i - 1]);
        init_rows();
    }

    explicit SparseTable(const vector<uint32_t> &nums) : st(__lg(nums.size()) + 1, vector<uint32_t>(nums.size())) {
        st[0] = nums;
        init_rows();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint32_t n, m, init_val, u, v;
    cin >> n >> m >> init_val >> u >> v;
    SparseTable st(n, init_val, [](uint32_t val) { return (val * 23 + 21563) % 16714589; });
    uint32_t ans = st.min(min(u, v) - 1, max(u, v));
    for (uint32_t i = 1; i < m; ++i) {
        u = ((u * 17 + 751 + ans + 2 * i) % n) + 1;
        v = ((v * 13 + 593 + ans + 5 * i) % n) + 1;
        ans = st.min(min(u, v) - 1, max(u, v));
    }
    cout << u << " " << v << " " << ans;
    return 0;
}
