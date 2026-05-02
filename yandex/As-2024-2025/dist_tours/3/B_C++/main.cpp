#include <algorithm>
#include <iostream>
#include <array>

using namespace std;

constexpr int maxn = 300, maxbc = maxn / 2 + 1;

struct MyBitSet {
    static constexpr int bits_nums_cnt = 5;
    array<uint64_t, bits_nums_cnt> bits;

    void shift_left() {
        for (int i = 0; i < bits_nums_cnt; ++i) {
            bits[i] <<= 1;
            if (i + 1 < bits_nums_cnt) bits[i] |= bits[i + 1] >> 63;
        }
    }

    void shift_right() {
        for (int i = bits_nums_cnt - 1; i >= 0; --i) {
            bits[i] >>= 1;
            if (i > 0) bits[i] |= (bits[i - 1] & 1) << 63;
        }
    }

    void add_bit(bool bit) {
        shift_left();
        bits[bits_nums_cnt - 1] |= bit;
    }

    bool operator<(const MyBitSet &rhs) const {
        for (int i = 0; i < bits_nums_cnt; ++i) if (bits[i] != rhs.bits[i]) return bits[i] < rhs.bits[i];
        return false;
    }

    bool operator>(const MyBitSet &rhs) const {
        return rhs < *this;
    }
};

struct MyS {
    int size;
    MyBitSet mask;

    MyS() = default;

    explicit MyS(int _size) : size(_size) {
    }

    bool operator<(const MyS &rhs) const {
        if (size != rhs.size) return size < rhs.size;
        return mask > rhs.mask;
    }
};

MyS _dp[2][maxn][maxbc];
int table[maxn][maxn];
int n, m;

int char_to_table(char c) {
    if (c == '.') return 0;
    if (c == '*') return 1;
    if (c == '(') return 2;
    if (c == ')') return 3;
    if (c == 'M') return 4;
}

void solve() {
    auto now_dp = _dp[0], next_dp = _dp[1];
    for (int j = 0; j < maxn; ++j)
        for (int k = 0; k < maxbc; ++k)
            now_dp[j][k].size = -1;
    cin >> n >> m;
    char c;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> c, table[i][j] = char_to_table(c);
    MyS best_res;
    best_res.size = 0;
    for (int i = n - 1; i > 0; --i) {
        for (int j = 0; j < m; ++j) for (int k = 0; k < maxbc; ++k) next_dp[j][k].size = -1;
        for (int j = 0; j < m; ++j) {
            if (table[i][j] == 1) continue;
            if (table[i][j] == 4) now_dp[j][0].size = 0;
            for (int ni = i - 1, nj = j - 1; nj <= j + 1; ++nj)
                if (table[ni][nj] == 1 && next_dp[nj][0] < now_dp[j][0])
                    next_dp[nj][0] = now_dp[j][0];
            for (int k = 0; k < maxbc; ++k) {
                if (now_dp[j][k].size == -1) continue;
                for (int ni = i - 1, nj = j - 1; nj <= j + 1; ++nj) {
                    if (nj < 0 || nj >= m) continue;
                    if (table[ni][nj] == 0 && next_dp[nj][k] < now_dp[j][k]) next_dp[nj][k] = now_dp[j][k];
                    else if (table[ni][nj] == 2 && k + 1 < maxbc) {
                        ++now_dp[j][k].size, now_dp[j][k].mask.add_bit(false);
                        if (next_dp[nj][k + 1] < now_dp[j][k]) next_dp[nj][k + 1] = now_dp[j][k];
                        --now_dp[j][k].size, now_dp[j][k].mask.shift_right();
                    } else if (table[ni][nj] == 3 && k > 0) {
                        ++now_dp[j][k].size, now_dp[j][k].mask.add_bit(true);
                        if (next_dp[nj][k - 1] < now_dp[j][k]) next_dp[nj][k - 1] = now_dp[j][k];
                        --now_dp[j][k].size, now_dp[j][k].mask.shift_right();
                    }
                }
            }
        }
        for (int j = 0; j < m; ++j)
            if (best_res < next_dp[j][0])
                best_res = next_dp[j][0];
        swap(now_dp, next_dp);
    }
    cout << best_res.size << "\n";
    string res(best_res.size, '0');
    for (int i = 0; i < best_res.size; ++i) {
        res[i] = (best_res.mask.bits[MyBitSet::bits_nums_cnt - 1] & 1) ? ')' : '(';
        best_res.mask.shift_right();
    }
    reverse(res.begin(), res.end());
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    solve();
#endif
    return 0;
}
