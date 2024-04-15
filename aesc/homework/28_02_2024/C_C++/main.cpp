#include <iostream>

using namespace std;

int main() {
    int32_t table[8][8];
    char c;
    for (auto &row: table) {
        for (auto &el: row) {
            cin >> c;
            if (c == 'B') el = 1;
            else if (c == 'R') el = 2;
            else el = 0;
        }
    }
    bool matrix[8][8];
    for (auto &row: matrix) for (auto &el: row) el = false;
    for (int32_t si = 0; si < 8; ++si) {
        for (int32_t sj = 0; sj < 8; ++sj) {
            if (table[si][sj] == 1) {
                matrix[si][sj] = true;
                for (int32_t i = si + 1, j = sj + 1; i < 8 && j < 8 && !table[i][j]; ++i, ++j) matrix[i][j] = true;
                for (int32_t i = si + 1, j = sj - 1; i < 8 && j >= 0 && !table[i][j]; ++i, --j) matrix[i][j] = true;
                for (int32_t i = si - 1, j = sj + 1; i >= 0 && j < 8 && !table[i][j]; --i, ++j) matrix[i][j] = true;
                for (int32_t i = si - 1, j = sj - 1; i >= 0 && j >= 0 && !table[i][j]; --i, --j) matrix[i][j] = true;
            } else if (table[si][sj] == 2) {
                matrix[si][sj] = true;
                for (int32_t i = si + 1; i < 8 && !table[i][sj]; ++i) matrix[i][sj] = true;
                for (int32_t i = si - 1; i >= 0 && !table[i][sj]; --i) matrix[i][sj] = true;
                for (int32_t j = sj + 1; j < 8 && !table[si][j]; ++j) matrix[si][j] = true;
                for (int32_t j = sj - 1; j >= 0 && !table[si][j]; --j) matrix[si][j] = true;
            }
        }
    }
    int32_t res = 0;
    for (auto &row: matrix) for (auto &el: row) res += !el;
    cout << res;
    return 0;
}
