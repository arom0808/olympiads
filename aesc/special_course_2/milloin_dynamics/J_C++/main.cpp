#include <iostream>
#include <vector>

using namespace std;

const int64_t mod = 1e9 + 7;

int64_t get_on_num(const string &st, bool is_add) {
    vector<vector<int64_t>> dp(st.size(), vector<int64_t>(10, 0));
    for (int64_t i = 0; i < st[0] - '0'; ++i) dp[0][i] = 1;
    bool is_raw_ok = true;
    for (int64_t i = 0; i + 1 < st.size(); ++i) {
        for (int64_t ldf = 0; ldf < 10; ++ldf)
            for (int64_t lds = ldf; lds < 10; ++lds)
                dp[i + 1][lds] = (dp[i + 1][lds] + dp[i][ldf]) % mod;
        if (st[i] > st[i + 1]) is_raw_ok = false;
        if (is_raw_ok)
            for (int64_t lds = st[i] - '0'; lds < st[i + 1] - '0'; ++lds)
                dp[i + 1][lds] = (dp[i + 1][lds] + 1) % mod;
    }
    int64_t res = 0;
    for (auto num: dp.back()) res = (res + num) % mod;
    if (is_raw_ok && is_add) res = (res + 1) % mod;
    return res;
}

int main() {
    string sl, sr;
    cin >> sl >> sr;
    int64_t res = (get_on_num(sr, true) - get_on_num(sl, false)) % mod;
    if (res < 0) res += mod;
    cout << res;
    return 0;
}
