#include <iostream>

using namespace std;
using ll = int64_t;

constexpr ll maxn = 1e5 + 1;
ll tin[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    ll ts, tf, t, n;
    cin >> ts >> tf >> t >> n;
    for (ll i = 0; i < n; ++i) cin >> tin[i];
    ll cur_start_time = 0, near_free_time = ts, best_ans = 1e18, best_time = 0;
    ll i = 0;
    while (i < n && tin[i] == 0) near_free_time += t, ++i;
    if (near_free_time - cur_start_time < best_ans) best_ans = near_free_time - cur_start_time, best_time = 0;
    for (; i < n && near_free_time + t <= tf;) {
        if (near_free_time <= tin[i] - 1) best_ans = 0, best_time = near_free_time;
        else if (best_ans > std::max<ll>(near_free_time - (tin[i] - 1), 0))
            best_ans = std::max<ll>(near_free_time - (tin[i] - 1), 0), best_time = tin[i] - 1;
        cur_start_time = tin[i], near_free_time = std::max(cur_start_time, near_free_time);
        while (i < n && tin[i] <= cur_start_time) near_free_time += t, ++i;
    }
    if (near_free_time + t <= tf) {
        if (best_ans > 0) best_ans = 0, best_time = near_free_time;
    }
    cout << best_time << "\n";
    return 0;
}
