#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int32_t n, m;
    cin >> n >> m;
    vector<vector<int32_t>> table(n, vector<int32_t>(m));
    for (auto &row: table) for (auto &val: row) cin >> val;
    int64_t res = 0;
    for (int32_t i = 0; i + 1 < n; ++i) {
        for (int32_t j = 0; j + 1 < m; ++j) {
            for (int32_t k = i + 1; k < n; ++k) {
                for (int32_t h = j + 1; h < m; ++h) {
                    int32_t dt = h - j - table[k][j];
                    if (table[i][j] != table[k][j] + table[i][h] + dt) continue;
                    if (table[i][h] + dt != k - i) continue;
                    ++res;
                }
            }
        }
    }
    cout << res;
    return 0;
}
