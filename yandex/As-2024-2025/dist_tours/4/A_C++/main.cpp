#pragma GCC optimize("Ofast,O3")

#include <iostream>
// #include <map>
#include <vector>
#include <algorithm>
#include <random>
#include <cstring>
#include <chrono>

using namespace std;

using ll = int64_t;
constexpr int maxn = 1e6;
constexpr ll inf = 1e18;

int n, k;
int nums_used[maxn];
int ans[maxn];
int bans[maxn];
int bres = 0;
vector<int> vs[maxn * 2];
int cur_res = 0;
chrono::time_point<chrono::steady_clock> start_time;

namespace Clever {
    mt19937 rng(254322);

    uniform_real_distribution<double> ddist;
    bernoulli_distribution bdist(0.5);

    constexpr int iters = 10000;

    void init_nums_used() {
        for (int i = 0; i < k; ++i) {
            for (auto cnum: vs[(i * 2) ^ ans[i]]) {
                if (!nums_used[cnum]) ++cur_res;
                ++nums_used[cnum];
            }
        }
    }

    void reverse_list(int list_id) {
        for (auto cnum: vs[(list_id * 2) ^ ans[list_id]]) {
            --nums_used[cnum];
            if (!nums_used[cnum]) --cur_res;
        }
        ans[list_id] ^= 1;
        for (auto cnum: vs[(list_id * 2) ^ ans[list_id]]) {
            if (!nums_used[cnum]) ++cur_res;
            ++nums_used[cnum];
        }
    }

    void solve() {
        for (int i = 0; i < k; ++i) ans[i] = bdist(rng);
        init_nums_used();
        bres = cur_res;
        memcpy(bans, ans, sizeof(int) * k);
        double t = 1;
        uniform_int_distribution<int> idist(0, k - 1);
        for (int i = 0; cur_res < n; ++i) {
            t *= 0.99;
            int pre_res = cur_res;
            int cur_change = idist(rng);
            reverse_list(cur_change);
            if (cur_res > bres) {
                bres = cur_res;
                memcpy(bans, ans, sizeof(int) * k);
            }
            if (cur_res <= pre_res && ddist(rng) >= exp((cur_res - pre_res) / t))
                reverse_list(cur_change);
            if (t < 1e-8) t = 0.1;
            if (i + 1 == 100) {
                if (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start_time).count() >=
                    970)
                    break;
                i = 0;
            }
        }
        for (int i = 0; i < k; ++i) cout << bans[i];
    }
}

// namespace Stupid {
//     bool used[maxn];
//
//     void solve() {
//         for (int _i = 0; _i < k; ++_i) {
//             map<pair<int, int>, int> mmp;
//             for (int i = 0; i < k * 2; ++i) {
//                 if (used[i / 2]) continue;
//                 int curuseful = 0, ccunuseful = 0;
//                 for (auto cnum: vs[i]) if (!nums_used[cnum]) ++curuseful;
//                 for (auto cnum: vs[i ^ 1]) if (!nums_used[cnum]) --ccunuseful;
//                 mmp[make_pair(curuseful, ccunuseful)] = i;
//             }
//             int cres = mmp.rbegin()->second;
//             ans[cres / 2] = cres % 2;
//             for (auto cnum: vs[cres]) nums_used[cnum] = true;
//             used[cres / 2] = true;
//         }
//         for (int i = 0; i < k; ++i) cout << ans[i];
//     }
// }

void solve() {
    start_time = chrono::steady_clock::now();
    cin >> n >> k;
    for (int i = 0, csz; i < k; ++i) {
        cin >> csz;
        vs[i * 2].resize(csz);
        for (auto &el: vs[i * 2]) cin >> el;
        sort(vs[i * 2].begin(), vs[i * 2].end());
        vs[i * 2 + 1].reserve(n - csz);
        for (int j = 1; j <= n; ++j)
            if (!binary_search(vs[i * 2].begin(), vs[i * 2].end(), j))
                vs[i * 2 + 1].push_back(j);
    }
    Clever::solve();
    // if (n <= 100 || (n <= 10 && k <= 10) || n <= k) Stupid::solve();
    // else Clever::solve();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    // freopen("input.txt","r",stdin);
    solve();
#endif
    return 0;
}
