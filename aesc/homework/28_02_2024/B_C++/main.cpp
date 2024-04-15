#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    uint32_t n, m;
    cin >> n >> m;
    uint32_t matrix[n][m];
    for (auto &row: matrix) for (auto &el: row) cin >> el;
    uint32_t min_ids[n], max_ids[m];
    for (uint32_t i = 0; i < n; ++i) min_ids[i] = 0;
    for (uint32_t i = 0; i < m; ++i) max_ids[i] = 0;
    for (uint32_t i = 0; i < n; ++i) {
        for (uint32_t j = 0; j < m; ++j) {
            if (matrix[i][j] < matrix[i][min_ids[i]]) min_ids[i] = j;
            if (matrix[i][j] > matrix[max_ids[j]][j]) max_ids[j] = i;
        }
    }
    bool exists = false;
    for (uint32_t i = 0; i < n; ++i)
        if (max_ids[min_ids[i]] == i)
            cout << i + 1 << " " << min_ids[i] + 1 << "\n", exists = true;
    if (!exists) cout << 0;
    return 0;
}
