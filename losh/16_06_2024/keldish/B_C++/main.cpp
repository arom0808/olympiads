#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int64_t n, k;
    cin >> n >> k;
    if (k % 2 == 1 || (n - 1) * n < k) {
        cout << "No\n";
        return 0;
    }
    vector<int32_t> vals(n);
//    set<int32_t> free_vals;
    vector<bool> swapped(n);
    for (int32_t i = 0; i < n; ++i) vals[i] = i + 1;
    int64_t now_val = 0;
    int32_t l = 0;
    for (; l < n && !swapped[l]; ++l) {
        int32_t r = min<int64_t>(n - 1, (k - now_val) / 2 + l);
//        auto it= prev(fre)
        for (; l < r && (now_val + 2 * (r - l) > k || swapped[r]); --r) {}
        if (l < r && now_val + std::abs(vals[r] - l - 1) + std::abs(vals[l] - r - 1) <= k && !swapped[r]) {
            now_val += std::abs(vals[r] - l - 1) + std::abs(vals[l] - r - 1);
            swap(vals[l], vals[r]);
            swapped[l] = swapped[r] = true;
        }
    }
//    for (; l < r;) {
//        if (now_val + std::abs(vals[r] - l - 1) + std::abs(vals[l] - r - 1) <= k) {
//            now_val += std::abs(vals[r] - l - 1) + std::abs(vals[l] - r - 1);
//            swap(vals[l], vals[r]);
//        }
//    }
//    if (l == r && now_val < k && vals.size() > 1 && vals[l + 1] == l + 2) {
//        if (now_val + std::abs(vals[l] - l - 2) + std::abs(vals[l + 1] - l - 1)) {
//            now_val += std::abs(vals[l] - l - 2) + std::abs(vals[l + 1] - l - 1);
//            swap(vals[l], vals[l + 1]);
//        }
//    }
    if (now_val != k) cout << "No\n";
    else {
        cout << "Yes\n";
        for (auto v: vals) cout << v << " ";
    }
    return 0;
}
