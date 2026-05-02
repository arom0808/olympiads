#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main() {
    freopen("test.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n;
    cin >> n;
    vector<int32_t> weights(n);
    for (auto &el: weights) cin >> el;
    vector<int32_t> perm(n);
    vector<vector<int32_t>> best_perms;
    iota(perm.begin(), perm.end(), 0);
    int64_t best_res = 0;
    do {
        int64_t res = 0;
        for (int32_t i = 0; i < n; ++i) res += weights[i] * std::abs(perm[i] - i);
        if (res == best_res) best_perms.push_back(perm);
        if (res > best_res) best_res = res, best_perms.clear(), best_perms.push_back(perm);
    } while (next_permutation(perm.begin(), perm.end()));
//    cout << best_res ;
    cout << best_res << "\n";
//    for (const auto &bp: best_perms) {
//        vector<int32_t> res(n);
//        for (int32_t i = 0; i < n; ++i) res[bp[i]] = weights[i];
//        for (auto el: res) cout << el << " ";
//        cout << "\n";
//    }
//    cout << "\n" << n;
    return 0;
}
