#include <iostream>

using namespace std;

int64_t table[6][9];
int64_t lines_sums[6][26];
int64_t cols_sums[9][26];

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string s;
    for (int64_t i = 0; i < 6; ++i) {
        cin >> s;
        for (int64_t j = 0; j < 9; ++j) {
            table[i][j] = s[j] - 'A';
            ++lines_sums[i][s[j] - 'A'];
            ++cols_sums[j][s[j] - 'A'];
        }
    }
    int64_t min_res = -1;
    for (int64_t a = 0; a < 26; ++a) {
        for (int64_t b = 0; b < 26; ++b) {
            for (int64_t c = 0; c < 26; ++c) {
                if (a == b || b == c) continue;
                int64_t nr1 =
                        54 - cols_sums[0][a] - cols_sums[1][a] - cols_sums[2][a] - cols_sums[3][b] - cols_sums[4][b] -
                        cols_sums[5][b] - cols_sums[6][c] - cols_sums[7][c] - cols_sums[8][c];
                int64_t nr2 = 54 - lines_sums[0][a] - lines_sums[1][a] - lines_sums[2][b] - lines_sums[3][b] -
                              lines_sums[4][c] - lines_sums[5][c];
                if (min_res == -1 || nr1 < min_res) min_res = nr1;
                if (min_res == -1 || nr2 < min_res) min_res = nr2;
            }
        }
    }
    cout << min_res;
    return 0;
}
