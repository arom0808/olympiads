#include <iostream>

using namespace std;

pair<int32_t, int32_t> sol(int32_t n, int32_t m, const int32_t *matrix, int32_t num) {
    for (int32_t i = 0, j = m - 1; i < n; ++i) {
        while (matrix[i * m + j] > num && j > 0) --j;
        if (matrix[i * m + j] == num) return {i, j};
    }
    return {-1, -1};
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, m, q;
    cin >> n >> m;
    int32_t matrix[n][m];
    for (auto &row: matrix) for (auto &el: row) cin >> el;
    cin >> q;
    for (int32_t _ = 0, num; _ < q; ++_) {
        cin >> num;
        auto res = sol(n, m, reinterpret_cast<const int32_t *>(matrix), num);
        cout << res.first + 1 << " " << res.second + 1 << "\n";
    }
    return 0;
}
