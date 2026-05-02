#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdint>

using namespace std;

vector<vector<vector<uint64_t>>> dp(11, vector<vector<uint64_t>>(64));

void init_dp() {
    for (uint32_t razr_cnt = 2; razr_cnt < 11; ++razr_cnt) {
        dp[razr_cnt][0].resize(1 << razr_cnt, 0);
        dp[razr_cnt][0][0] = 1;
        for (uint32_t len = 1; len < 64; ++len) {
            dp[razr_cnt][len].resize(1 << razr_cnt, 0);
            for (uint32_t chetns = 0; chetns < (1 << razr_cnt); ++chetns)
                for (uint32_t dig = 0; dig < razr_cnt; ++dig)
                    dp[razr_cnt][len][chetns] += dp[razr_cnt][len - 1][(chetns ^ (1 << dig))];
        }
    }
}

string transform_num_system(uint64_t num, uint32_t c) {
    if (num == 0) return "0";
    string res;
    for (; num != 0; num /= c) res += '0' + num % c;
    reverse(res.begin(), res.end());
    return res;
}

bool can_increase_free_cnt(string &ac, const string &bc, uint32_t free_cnt, uint32_t c) {
    ++free_cnt;
    if (free_cnt > ac.size()) return false;
    for (uint32_t i = 0; i < free_cnt; ++i) if (ac[ac.size() - i - 1] != '0') return false;
    for (uint32_t i = 0; i < free_cnt; ++i) ac[ac.size() - i - 1] = '0' + c - 1;
    bool is_max_ok = ac <= bc;
    for (uint32_t i = 0; i < free_cnt; ++i) ac[ac.size() - i - 1] = '0';
    return is_max_ok;
}

bool need_decrease_free_cnt(string &ac, const string &bc, uint32_t free_cnt, uint32_t c) {
    for (uint32_t i = 0; i < free_cnt; ++i) ac[ac.size() - i - 1] = '0' + c - 1;
    bool is_max_bad = ac > bc;
    for (uint32_t i = 0; i < free_cnt; ++i) ac[ac.size() - i - 1] = '0';
    return is_max_bad;
}

uint32_t count_chetn(const string &ac, uint32_t free_cnt) {
    uint32_t chetn = 0;
    bool started = false;
    for (uint32_t i = 0; i + free_cnt < ac.size(); ++i) {
        if (ac[i] != '0') started = true;
        if (started) chetn ^= 1 << (ac[i] - '0');
    }
    return chetn;
}

uint64_t solve_for_one_door(uint32_t c, uint64_t a, uint64_t b) {
    string ac = transform_num_system(a, c), bc = "00" + transform_num_system(b, c);
    ac = string(bc.size() - ac.size(), '0') + ac;
    uint32_t free_cnt = 0;
    uint64_t result = 0;
    while (ac <= bc) {
        while (can_increase_free_cnt(ac, bc, free_cnt, c))
            ++free_cnt;
        while (need_decrease_free_cnt(ac, bc, free_cnt, c))
            --free_cnt;
        result += dp[c][free_cnt][count_chetn(ac, free_cnt)];
        ++ac[ac.size() - free_cnt - 1];
        uint32_t cur_i = ac.size() - free_cnt - 1;
        while (ac[cur_i] - '0' == c) ac[cur_i] = '0', ++ac[--cur_i];
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    init_dp();
    uint32_t n, c;
    uint64_t a, b;
    cin >> n;
    for (uint32_t i = 0; i < n; ++i) {
        cin >> c >> a >> b;
        cout << solve_for_one_door(c, a, b) << "\n";
    }
    return 0;
}
