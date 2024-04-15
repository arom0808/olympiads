#include <iostream>
#include <set>

using namespace std;

int main() {
    uint32_t n, T;
    cin >> n >> T;
    multiset<uint32_t> now_times;
    uint32_t max_res = 0, sum_time = 0;
    for (uint32_t i = 0, x, t; i < n; ++i) {
        cin >> x >> t;
        if (x > T) break;
        sum_time += t;
        now_times.insert(t);
        while (sum_time + x > T && !now_times.empty()) {
            sum_time -= *now_times.rbegin();
            now_times.erase(prev(now_times.end()));
        }
        if (now_times.size() > max_res) max_res = now_times.size();
    }
    cout << max_res;
    return 0;
}
