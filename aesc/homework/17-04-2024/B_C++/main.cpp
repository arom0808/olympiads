#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t k, n;
    cin >> k >> n;
    vector<int32_t> arr(n);
    for (auto &el: arr) cin >> el;
    int32_t l = 0, r = n - 1;
    while (l < r) {
        int32_t m = (l + r) / 2;
        if (arr[m] > k) r = m - 1;
        else if (arr[m] < k) l = m + 1;
        else r = m;
    }
    if (l < n && arr[l] == k) cout << l + 1;
    else cout << 0;
    return 0;
}
