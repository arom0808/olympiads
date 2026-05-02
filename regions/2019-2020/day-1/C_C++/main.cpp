#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

constexpr int32_t maxn = 2e5 + 1;

int32_t n;
int32_t nums[maxn];
map<int32_t, vector<int32_t> > val_poss;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int32_t i = 0; i < n; ++i) cin >> nums[i], val_poss[nums[i]].push_back(i);
    vector<int32_t> all_dists;
    for (const auto &[val, poss]: val_poss) {
        all_dists.push_back(poss.front());
        all_dists.push_back(n - poss.back() - 1);
        for (int32_t i = 1; i < poss.size(); ++i) all_dists.push_back(poss[i] - poss[i - 1] - 1);
    }
    sort(all_dists.begin(), all_dists.end());
    vector<int64_t> pf(all_dists.size() + 1);
    pf[0] = 0;
    for (int32_t i = 0; i < all_dists.size(); ++i) pf[i + 1] = pf[i] + all_dists[i];
    for (int32_t d = 1; d <= n; ++d) {
        int32_t pos = distance(all_dists.begin(), lower_bound(all_dists.begin(), all_dists.end(), d - 1));
        cout << (1ll * val_poss.size() * (n - d + 1) - (pf.back() - pf[pos] - 1ll * (d - 1) * (pf.size() - pos - 1))) <<
                " ";
    }
    return 0;
}
