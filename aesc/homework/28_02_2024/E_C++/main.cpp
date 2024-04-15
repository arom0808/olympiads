#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class PrefSum {
    uint32_t n, m;
    vector<vector<T>> ps;

public:
    explicit PrefSum(const vector<vector<T>> &arr)
            : n(arr.size()), m(arr.front().size()), ps(arr.size() + 1, vector<T>(arr.front().size() + 1)) {
        for (uint32_t i = 0; i < n; ++i)
            for (uint32_t j = 0; j < m; ++j)
                ps[i + 1][j + 1] = arr[i][j] + ps[i][j + 1] + ps[i + 1][j] - ps[i][j];
    }

    T sum(uint32_t i0, uint32_t j0, uint32_t len) {
        return ps[i0 + len][j0 + len] + ps[i0][j0] - ps[i0][j0 + len] - ps[i0 + len][j0];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    uint32_t n, m;
    cin >> n >> m;
    vector<vector<int32_t>> matrix(n, vector<int32_t>(m));
    for (auto &row: matrix) for (auto &el: row) cin >> el;
    PrefSum<int32_t> ps(matrix);
    uint32_t l = 0, r = min(n, m), best_len = 0, best_i = 0, best_j = 0;
    while (l != r) {
        uint32_t len = ((l + r) >> 1) + ((l + r) & 1);
        bool ok = false;
        for (uint32_t i = 0; i + len <= n && !ok; ++i)
            for (uint32_t j = 0; j + len <= m && !ok; ++j)
                if (ps.sum(i, j, len) == len * len)
                    ok = true, best_i = len > best_len ? i : best_i,
                    best_j = len > best_len ? j : best_j, best_len = max(len, best_len);
        if (ok) l = len;
        else r = len - 1;
    }
    cout << best_len << "\n" << best_i + 1 << " " << best_j + 1;
    return 0;
}
