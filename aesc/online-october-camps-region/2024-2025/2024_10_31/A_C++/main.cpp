#include <iostream>

using namespace std;
using ll = int64_t;
constexpr ll maxn = 1e6, inf = 1e18;

ll arr[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t1, t2, d, s;
    cin >> t1 >> t2 >> d >> s;
    for (int i = 0; i < d; ++i) cin >> arr[i];
    int start_t = 0, best_start = 0;
    ll sum_l = 0, best_sum = inf;
    for (int i = 0; i < t1; ++i) sum_l += arr[i];
    for (int i = t1; i < t1 + t2; ++i) sum_l += std::max<ll>(arr[i] - s, 0);
    if (sum_l < best_sum) best_start = start_t, best_sum = sum_l;
    for (++start_t; start_t + t1 + t2 <= d; ++start_t) {
        sum_l -= arr[start_t - 1];
        sum_l += arr[start_t + t1 - 1];
        sum_l -= std::max<ll>(arr[start_t + t1 - 1] - s, 0);
        sum_l += std::max<ll>(arr[start_t + t1 + t2 - 1] - s, 0);
        if (sum_l < best_sum) best_start = start_t, best_sum = sum_l;
    }
    cout << best_start << "\n" << best_sum << "\n";
    return 0;
}
