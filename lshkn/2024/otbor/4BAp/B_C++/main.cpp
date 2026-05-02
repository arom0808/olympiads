//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,tune=native")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("vpt")
//#pragma GCC optimize("rename-registers")
//#pragma GCC optimize("move-loop-invariants")
//#pragma GCC optimize("unswitch-loops")
//#pragma GCC optimize("inline")

#include <iostream>
#include <map>
#include <set>

using namespace std;

const uint32_t maxn = 3001, eff_diff = 6000;
uint32_t dp[maxn][eff_diff];

int32_t effs[maxn];

inline void init_effs() {
    effs[1] = -1;
    for (uint32_t i = 2; i < maxn; ++i) {
        if (i == 10 || i == 100 || i == 1000) effs[i] = effs[i - 1];
        else effs[i] = effs[i - 1] + 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    init_effs();

//    map<int32_t, map<int32_t, int32_t>> rs;
//
//    int32_t i = 1100;
//    for (int32_t j = i - 1; j > 0; --j) {
//        for (int32_t j_eff = 0 - j, b_eff = 3000 + effs[i - j]; j_eff <= j; ++j_eff) {
//            auto it = rs.find(b_eff + j_eff);
//            if (it == rs.end()) it = rs.emplace(b_eff + j_eff, map<int32_t, int32_t>()).first;
//            auto it2 = it->second.find(3000 + j_eff);
//            if (it2 == it->second.end()) it->second.emplace(3000 + j_eff, 1);
//            else ++it2->second;
//        }
//    }
//    for (const auto& r: rs) {
//        cout << r.first << "\n";
//        for (auto c: r.second) {
//            cout << c.first << ": " << c.second << "\n";
//        }
//        cout << "\n";
//    }

    uint32_t n, P;
    cin >> n >> P;
    for (uint32_t i = 1; i <= n; ++i) dp[i][effs[i] + 3000] = 26;

    for (int32_t i = 2, eni = effs[n - i]; i <= n; ++i) {
        for (int32_t j_eff = 1 - i; j_eff <= i - 1; ++i) {
            for (int32_t j = i - 1, b_eff = 3000 + effs[i - j]; j >= abs(j_eff); --j, b_eff = 3000 + effs[i - j]) {
                dp[i][b_eff + j_eff] = (dp[i][b_eff + j_eff] + dp[j][3000 + j_eff] * 25) % P;
            }
        }
        for (int32_t j = i - 1, b_eff = 3000 + effs[i - j]; j > 0; --j, b_eff = 3000 + effs[i - j])
            for (int32_t j_eff = max(0 - j, 1 - effs[i - j] - eni); j_eff <= j; ++j_eff)
                dp[i][b_eff + j_eff] = (dp[i][b_eff + j_eff] + dp[j][3000 + j_eff] * 25) % P;
//        cout << i << "\n";
//        cout.flush();
    }
    uint32_t res = 0;
    for (int64_t eff = 3001; eff <= 5998; ++eff) res = (res + dp[n][eff]) % P;
    cout << res << "\n";
    return 0;
}
