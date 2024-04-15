#include <iostream>

using namespace std;

int main() {
    uint32_t n, m;
    cin >> n >> m;
    uint32_t matrix[n][m];
    for (auto &row: matrix) for (auto &el: row) el = 0;
    uint32_t dir = 0, i = 0, j = 0, num = 1;
    for (; matrix[i][j] == 0; ++num) {
        matrix[i][j] = num;
        if (dir == 0) {
            if (j + 1 < m && matrix[i][j + 1] == 0) ++j;
            else dir = (dir + 1) % 4, ++i;
        } else if (dir == 1) {
            if (i + 1 < n && matrix[i + 1][j] == 0) ++i;
            else dir = (dir + 1) % 4, --j;
        } else if (dir == 2) {
            if (j > 0 && matrix[i][j - 1] == 0) --j;
            else dir = (dir + 1) % 4, --i;
        } else if (dir == 3) {
            if (i > 0 && matrix[i - 1][j] == 0) --i;
            else dir = (dir + 1) % 4, ++j;
        }
    }
    for (auto &row: matrix) {
        for (auto el: row) cout << el << " ";
        cout << "\n";
    }
    return 0;
}
