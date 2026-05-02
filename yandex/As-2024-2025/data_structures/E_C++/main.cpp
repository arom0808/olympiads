#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int64_t n, p;
    cin >> n;
    vector<int64_t> nums(n);
    for (auto &el: nums) cin >> el;
    cin >> p;
    for (auto &el: nums) el -= p;
    ordered_multiset<int64_t> pre_sums;
    int64_t cs = 0, ans = 0;
    pre_sums.insert(cs);
    for (auto el: nums) {
        cs += el;
        ans += pre_sums.order_of_key(cs + 1);
        pre_sums.insert(cs);
    }
    cout << ans << "\n";
    return 0;
}
