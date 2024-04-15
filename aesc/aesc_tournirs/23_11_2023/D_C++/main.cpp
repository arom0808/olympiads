#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Act {
    int32_t x;
    uint32_t t;
};

inline bool is_way(uint32_t v, const Act &l, const Act &r) {
    if (l.t > r.t) return false;
    return v * (r.t - l.t) >= std::abs(l.x - r.x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    uint32_t n, v;
    cin >> n;
    vector<Act> acts(n);
    for (auto &[x, t]: acts) cin >> x >> t;
    cin >> v;
    sort(acts.begin(), acts.end(), [](const Act &a, const Act &b) { return a.t > b.t; });
    vector<uint32_t> max_ways(n, 1);
    for (uint32_t i = 0; i + 1 < n; ++i)
        for (uint32_t j = i + 1; j < n; ++j)
            if (is_way(v, acts[j], acts[i]) && max_ways[i] + 1 > max_ways[j])
                max_ways[j] = max_ways[i] + 1;
    Act fa(0, 0);
    uint32_t max_f = 0;
    for (uint32_t i = 0; i < n; ++i) if (is_way(v, fa, acts[i]) && max_ways[i] > max_f) max_f = max_ways[i];
    uint32_t max_s = *max_element(max_ways.begin(), max_ways.end());
    cout << max_f << " " << max_s;
    return 0;
}
