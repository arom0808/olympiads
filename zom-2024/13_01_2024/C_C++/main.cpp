//#pragma GCC optimize("Ofast")
//#pragma GCC optimize(O3)
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,tune=native")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
//#pragma GCC optimize("vpt")
//#pragma GCC optimize("rename-registers")
//#pragma GCC optimize("move-loop-invariants")
//#pragma GCC optimize("unswitch-loops")
//#pragma GCC optimize("function-sections")
//#pragma GCC optimize("data-sections")
//#pragma GCC optimize("branch-target-load-optimize")
//#pragma GCC optimize("branch-target-load-optimize2")
//#pragma GCC optimize("btr-bb-exclusive")
//#pragma GCC optimize("inline")
//#pragma GCC optimize("-fgcse")
//#pragma GCC optimize("-fgcse-lm")
//#pragma GCC optimize("-fipa-sra")
//#pragma GCC optimize("-ftree-pre")
//#pragma GCC optimize("-ftree-vrp")
//#pragma GCC optimize("-fpeephole2")
//#pragma GCC optimize("-ffast-math")
//#pragma GCC optimize("-fsched-spec")
//#pragma GCC optimize("-falign-jumps")
//#pragma GCC optimize("-falign-loops")
//#pragma GCC optimize("-falign-labels")
//#pragma GCC optimize("-fdevirtualize")
//#pragma GCC optimize("-fcaller-saves")
//#pragma GCC optimize("-fcrossjumping")
//#pragma GCC optimize("-fthread-jumps")
//#pragma GCC optimize("-freorder-blocks")
//#pragma GCC optimize("-fschedule-insns")
//#pragma GCC optimize("inline-functions")
//#pragma GCC optimize("-ftree-tail-merge")
//#pragma GCC optimize("-fschedule-insns2")
//#pragma GCC optimize("-fstrict-aliasing")
//#pragma GCC optimize("-falign-functions")
//#pragma GCC optimize("-fcse-follow-jumps")
//#pragma GCC optimize("-fsched-interblock")
//#pragma GCC optimize("-fpartial-inlining")
//#pragma GCC optimize("no-stack-protector")
//#pragma GCC optimize("-freorder-functions")
//#pragma GCC optimize("-findirect-inlining")
//#pragma GCC optimize("-fhoist-adjacent-loads")
//#pragma GCC optimize("-frerun-cse-after-loop")
//#pragma GCC optimize("inline-small-functions")
//#pragma GCC optimize("-finline-small-functions")
//#pragma GCC optimize("-ftree-switch-conversion")
//#pragma GCC optimize("-foptimize-sibling-calls")
//#pragma GCC optimize("-fexpensive-optimizations")
//#pragma GCC optimize("inline-functions-called-once")
//#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <iostream>
#include <random>
#include <string>
#include <algorithm>

using namespace std;

void rec_sol(string &str, int64_t ni, int64_t n, int64_t pal_check_cnt, int64_t &res, const string &bad_str) {
    int64_t k = bad_str.size();
    if (ni >= n) {
        bool is_bad = false, is_pal = true;
        for (int64_t i = 0; i <= n - k; ++i) {
            bool eq = true;
            for (int64_t j = 0; j < k; ++j) {
                if (str[i + j] != bad_str[j]) {
                    eq = false;
                    break;
                }
            }
            if (eq) {
                is_bad = true;
                break;
            }
        }
        if (pal_check_cnt != n) {
            for (int64_t i = pal_check_cnt / 2; i <= n - k; ++i) {
                bool eq = true;
                for (int64_t j = 0; j < k; ++j) {
                    if (str[i + j] != bad_str[k - j - 1]) {
                        eq = false;
                        break;
                    }
                }
                if (eq) {
                    is_bad = true;
                    break;
                }
            }
        }
        if (is_bad) return;
        for (int64_t i = 0; i < pal_check_cnt / 2; ++i) {
            if (str[pal_check_cnt - i - 1] != str[i]) {
                is_pal = false;
                break;
            }
        }
        if (is_pal) {
            ++res;
            cout << "rec: " << str << "\n";
        }
        return;
    }
    str[ni] = 'A';
    rec_sol(str, ni + 1, n, pal_check_cnt, res, bad_str);
    str[ni] = 'B';
    rec_sol(str, ni + 1, n, pal_check_cnt, res, bad_str);
}

int64_t bin_sol(int64_t n, int64_t pal_check_cnt, const string &bad_str) {
    int64_t res = 0, k = bad_str.size(), bad_mask = 0, rev_bad_mask = 0, last_k_1 = (1ll << k) - 1;
    for (auto c: bad_str) {
        bad_mask <<= 1;
        if (c == 'B') bad_mask |= 1;
    }
    for (int64_t i = bad_str.size() - 1; i >= 0; --i) {
        rev_bad_mask <<= 1;
        if (bad_str[i] == 'B') rev_bad_mask |= 1;
    }
    for (int64_t mask = 0; mask < (1ll << n); ++mask) {
        bool is_bad = false, is_pal = true;
        for (int64_t i = 0; i <= n - k; ++i) {
            if (((mask >> (n - k - i)) & last_k_1) == bad_mask) {
                is_bad = true;
                break;
            }
        }
        if (pal_check_cnt != n) {
            for (int64_t i = pal_check_cnt / 2; i <= n - k; ++i) {
                if (((mask >> (n - k - i)) & last_k_1) == rev_bad_mask) {
                    is_bad = true;
                    break;
                }
            }
        }
        if (is_bad) continue;
        for (int64_t i = 0; i < pal_check_cnt / 2; ++i) {
            if (((mask >> (n - pal_check_cnt + i)) & 1) != ((mask >> (n - i - 1)) & 1)) {
                is_pal = false;
                break;
            }
        }
        if (is_pal) {
            ++res;
//            string ss(n, 'A');
//            for (int64_t i = 0; i < n; ++i) ss[i] = ((mask >> (n - i - 1)) & 1) ? 'B' : 'A';
//            reverse(ss.begin(), ss.end());
//            cout << "bin: " << ss << "\n";
        }
    }
    return res;
}

int64_t for_30_sol(int64_t n, int64_t k, const string &bad_str) {
    int64_t res = 0;
    string str(n, 'A');
    rec_sol(str, 0, n, n, res, bad_str);
    return res;
}

int64_t for_60_sol(int64_t n, int64_t k, const string &bad_str) {
    int64_t left_check = n / 2 - k + n % 2, right_check = n / 2 + k - 1;
    if (left_check < 0) left_check = 0;
    if (right_check >= n) right_check = n - 1;
    int64_t res = 0, new_n = n - left_check;
    string temp_str(new_n, 'A');
//    rec_sol(temp_str, 0, new_n, right_check - left_check + 1, res, bad_str);
    res = bin_sol(new_n, right_check - left_check + 1, bad_str);
    return res;
}

int64_t for_100_sol(int64_t n, int64_t k, const string &bad_str) {
    if (k * 2 >= n) {
        return for_60_sol(n, k, bad_str);
    }
    int64_t bad_mask = 0, last_k_1 = (1 << k) - 1, last_km1_1 = (1 << (k - 1)) - 1, rev_bad_mask = 0;
    for (auto c: bad_str) {
        bad_mask <<= 1;
        if (c == 'B') bad_mask |= 1;
    }
    for (int64_t i = bad_str.size() - 1; i >= 0; --i) {
        rev_bad_mask <<= 1;
        if (bad_str[i] == 'B') rev_bad_mask |= 1;
    }
    vector<vector<int64_t>> dp((n >> 1) + (n & 1) + 1, vector<int64_t>(1 << (k - 1), 0));
    for (auto &v: dp[k - 1]) v = 1;
    for (int64_t i = k - 1; i < (n >> 1) + (n & 1); ++i) {
        for (int64_t mask = 0; mask < (1 << (k - 1)); ++mask) {
            if ((mask << 1) != bad_mask && (mask << 1) != rev_bad_mask)
                dp[i + 1][(mask << 1) & last_km1_1] += dp[i][mask];
            if (((mask << 1) | 1) != bad_mask && ((mask << 1) | 1) != rev_bad_mask)
                dp[i + 1][((mask << 1) | 1) & last_km1_1] += dp[i][mask];
        }
    }
    int64_t res = 0;
    for (int64_t mask = 0; mask < (1 << (k - 1)); ++mask) {
        int64_t full_mask = mask;
        for (int64_t j = n & 1; j + 1 < k; ++j) {
            full_mask <<= 1;
            full_mask |= (mask >> j) & 1;
        }
        bool is_bad = false;
        for (int64_t j = 0; j + (n & 1) + 1 < k; ++j) {
            if (((full_mask >> j) & last_k_1) == bad_mask) is_bad = true;
        }
        if (!is_bad) res += dp[(n >> 1) + (n & 1)][mask];
    }
    return res;
}

//int64_t my_sol(int64_t n, int64_t k, const string &bad_str) {
//    int64_t now_n = k * 2 - (n % 2), base_cnt = 0;
//    string temp_str(now_n, 'A');
//    rec_sol(temp_str, 0, now_n, base_cnt, bad_str);
//    vector<int64_t> dp(n + 1, 0);
//    dp[k] = base_cnt;
//    bool is_s_eq = bad_str.substr(0, k - 1) == bad_str.substr(1);
//    for (int64_t i = k; i < n / 2 + n % 2; ++i) {
//        if (k == 0) dp[i + 1] = dp[i] * 2;
//        else dp[i + 1] = dp[i] * 2 - (!is_s_eq);
//    }
//    return dp[n / 2 + n % 2];
//}

namespace Test {
    random_device dev;
    mt19937 rng(dev());

    int64_t randint(int64_t a, int64_t b) { return uniform_int_distribution(a, b)(rng); }

    pair<string, int64_t> gen() {
        int64_t n = randint(1, 7), k = randint(1, 4);
        string str(k, 'A');
        for (auto &c: str) if (randint(0, 1)) c = 'B';
        return {str, n};
    }

    void Test() {
        while (true) {
            auto [bad_str, n] = gen();
//            int64_t fr = 0, fb = 0;
//            string str(n, 'A');
//            rec_sol(str, 0, n, n, fr, bad_str);
//            fb = bin_sol(n, n, bad_str);
            auto f30 = for_30_sol(n, bad_str.size(), bad_str), f100 = for_100_sol(n, bad_str.size(), bad_str);
            if (f30 != f100) {
                cout << bad_str << "\n" << n << "\n\n";
                cout << "f30: " << f30 << "\nf100: " << f100;
                break;
            }
            cout << "\n\n";
        }
    }
}

int main() {
    string s, ttt;
    std::getline(cin, s), std::getline(cin, ttt);
    int64_t n = stoi(ttt), k = s.size();
    cout << for_100_sol(n, k, s);

//    Test::Test();
//    if (n <= 20) {
//        int64_t res = 0;
//        string str(n, 'A');
//        rec_sol(str, 0, n, n, res, s);
//        cout << res;
//        return 0;
//    }
//    Test::Test();
    return 0;
}
