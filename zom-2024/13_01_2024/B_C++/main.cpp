#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

const uint32_t c7 = 1e7;

int main() {
    const uint32_t maxn = c7;
    vector<uint32_t> lp(maxn + 1), primes;
    primes.reserve(664580);
    for (uint32_t i = 2; i <= maxn; ++i) {
        if (!lp[i]) primes.push_back(lp[i] = i);
        for (uint32_t j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= maxn; ++j)
            lp[i * primes[j]] = primes[j];
    }
    uint32_t n;
    cin >> n;
    vector<uint32_t> nums(n);
    for (auto &num: nums) cin >> num;
    unordered_map<uint32_t, vector<uint32_t>> prime_cnts;
    unordered_map<uint32_t, uint32_t> now_num_cnts;
    unordered_map<uint32_t, uint32_t> usings_cnt;
    for (auto num: nums) {
        now_num_cnts.clear();
        while (num > 1) {
            uint32_t p_div = lp[num];
            auto it = now_num_cnts.find(p_div);
            if (it == now_num_cnts.end()) now_num_cnts.emplace(p_div, 1);
            else ++it->second;
            num /= p_div;
        }
        for (auto [p_div, cnt]: now_num_cnts) {
            auto it = prime_cnts.find(p_div);
            if (it == prime_cnts.end()) it = prime_cnts.emplace(p_div, vector<uint32_t>(30, 0)).first;
            ++it->second[cnt];
            auto it2 = usings_cnt.find(p_div);
            if (it2 == usings_cnt.end()) usings_cnt.emplace(p_div, 1);
            else ++it2->second;
        }
    }
    uint32_t res = 0;
    for (auto &[p_div, cnts]: prime_cnts) {
        uint32_t best_to_change_cnt = 1e9, cuc = usings_cnt[p_div];
        for (uint32_t i = 0; i < cnts.size(); ++i) {
            uint32_t to_change_cnt = 0;
            to_change_cnt += (n - cuc) * i;
            for (uint32_t j = 1; j < i; ++j) to_change_cnt += cnts[j] * (i - j);
            for (uint32_t j = i + 1; j < cnts.size(); ++j) to_change_cnt += cnts[j] * (j - i);
            if (to_change_cnt < best_to_change_cnt) best_to_change_cnt = to_change_cnt;
        }
        res += best_to_change_cnt;
    }
    cout << res;
    return 0;
}
