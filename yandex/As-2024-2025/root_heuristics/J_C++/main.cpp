#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

constexpr int64_t sqrtl = 64000;

map<int64_t, pair<int64_t, int64_t> > divs;

template<typename T>
inline T ceil(T a, T b) { return (a + b - 1) / b; }

void sol() {
    int64_t l, r;
    cin >> l >> r;
    divs.clear();
    int64_t gmg = l;
    for (int64_t i = 1; i * i <= l; ++i) {
        int64_t min_g = ceil(l, i), max_g = i == 1 ? l : ceil(l, i - 1);
        if (max_g - min_g > 0) divs.emplace(i, make_pair(min_g, max_g - 1)), gmg = std::min(gmg, min_g);
    }
    int64_t ans = std::max<int64_t>(r / 2 - l + 1, 0);
    for (auto [div, pmm]: divs) {
        auto [min_g, max_g] = pmm;
        max_g = std::min(max_g, r / (div + 1));
        ans += std::max<int64_t>(max_g - min_g + 1, 0);
    }
    for (int64_t i = 1; i < gmg; ++i) if ((ceil(l, i) + 1) * i <= r) ++ans;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t t;
    cin >> t;
    while (t--) sol();
    return 0;
}
