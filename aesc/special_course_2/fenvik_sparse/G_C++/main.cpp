#include <iostream>
#include <vector>

using namespace std;

int main() {
    string raw;
    cin >> raw;
    vector<bool> brs(raw.size());
    for (uint32_t i = 0; i < raw.size(); ++i) brs[i] = raw[i] == '(';
    uint32_t n = brs.size();
    vector<uint32_t> dp(n, 0);
    for (uint32_t i = 1; i < n; ++i) {
        if (brs[i]) continue;
        if (brs[i - 1])
            dp[i] = (i > 1 ? dp[i - 2] : 0) + 2;
        else if (dp[i - 1] && i > dp[i - 1] && brs[i - dp[i - 1] - 1])
            dp[i] = dp[i - 1] + 2 + (i > dp[i - 1] + 1 ? dp[i - dp[i - 1] - 2] : 0);
    }
    uint32_t max_len = 0, max_cnt = 1;
    for (auto len: dp) {
        if (len > max_len) {
            max_len = len;
            max_cnt = 1;
        } else if (len == max_len) ++max_cnt;
    }
    cout << max_len << " " << (max_len == 0 ? 1 : max_cnt);
    return 0;
}



//pair<uint32_t, uint32_t> sol1(const vector<bool> &brs) {
//    list<pair<uint32_t, uint32_t>> right_seqs;
//    for (uint32_t i = 0; i + 1 < brs.size();) {
//        if (!brs[i] || brs[i + 1]) {
//            ++i;
//            continue;
//        }
//        uint32_t l = i, r = i + 1;
//        while (true) {
//            if (l > 1 && r + 1 < brs.size() && brs[l - 1] && !brs[r + 1]) {
//                --l;
//                ++r;
//            } else if (l > 1 && !right_seqs.empty() && right_seqs.back().second == l - 1) {
//                l = right_seqs.back().first;
//                right_seqs.pop_back();
//            } else break;
//        }
//        right_seqs.emplace_back(l, r);
//        i = r + 1;
//    }
//    uint32_t max_len = 0, max_cnt = 1;
//    for (auto [l, r]: right_seqs) {
//        if (r - l + 1 > max_len) {
//            max_len = r - l + 1;
//            max_cnt = 1;
//        } else if (r - l + 1 == max_len) ++max_cnt;
//    }
//    return {max_len, max_cnt};
//}
//
//pair<uint32_t, uint32_t> sol2(const vector<bool> &brs) {
//    return {max_len, max_len == 0 ? 1 : max_cnt};
//}
//
//bool is_psp(const vector<bool> &brs, uint32_t l, uint32_t r) {
//    int32_t cnt = 0;
//    for (uint32_t i = l; i <= r; ++i) {
//        if (brs[i]) ++cnt; else --cnt;
//        if (cnt < 0) return false;
//    }
//    return cnt == 0;
//}
//
//pair<uint32_t, uint32_t> sol3(const vector<bool> &brs) {
//    uint32_t max_len = 0;
//    for (uint32_t i = 0; i + 1 < brs.size(); ++i)
//        for (uint32_t j = i + 1; j < brs.size(); ++j)
//            if (is_psp(brs, i, j) && j - i + 1 > max_len) max_len = j - i + 1;
//    uint32_t max_cnt = 0;
//    for (uint32_t i = 0; i + max_len <= brs.size(); ++i)
//        if (i + max_len > 0 && is_psp(brs, i, i + max_len - 1)) ++max_cnt;
//    return {max_len, max_len == 0 ? 1 : max_cnt};
//}
//
//namespace Test {
//    random_device dev;
//    mt19937 rng(dev());
//
//    int32_t randint(int32_t a, int32_t b) {
//        return uniform_int_distribution<int32_t>(a, b)(rng);
//    }
//
//    void Test() {
//        while (true) {
//            vector<bool> brs(randint(0, 10));
//            for (_Bit_reference b: brs) {
//                b = randint(0, 1);
//                cout << (b ? '(' : ')');
//            }
//            cout << "\n";
//            auto r1 = sol2(brs), r2 = sol3(brs);
//            if (r1 != r2) {
//                cout << "r1: " << r1.first << " " << r1.second << "\n";
//                cout << "r2: " << r2.first << " " << r2.second;
//                break;
//            }
//        }
//    }
//}
