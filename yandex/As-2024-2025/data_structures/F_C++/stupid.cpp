#include <iostream>
#include <vector>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n, m;
    cin >> n;
    vector<int32_t> nums(n);
    for (auto &el: nums) cin >> el;
    cin >> m;
    for (int32_t i = 0, q, l, r, k; i < m; ++i) {
        cin >> q >> l >> r >> k;
        if (!q) for (int32_t j = l - 1; j < r; ++j) nums[j] = k;
        else {
            bool eq = true;
            for (int32_t j = 0; j < k && eq; ++j) if (nums[l - 1 + j] != nums[r - 1 + j]) eq = false;
            if (eq) cout << "+";
            else cout << "-";
        }
    }
}
