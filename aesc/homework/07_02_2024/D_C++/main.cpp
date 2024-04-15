#include <iostream>

using namespace std;

int main() {
    int32_t n, k, m;
    cin >> n >> k >> m;
    int32_t arr[n];
    for (auto &el: arr) cin >> el;
    int32_t sum = 0;
    for (uint32_t i = 0; i <= k; ++i) sum += arr[i];
    uint32_t i = 0;
    for (; sum != m && i + k + 1 < n; ++i) {
        sum -= arr[i];
        sum += arr[i + k + 1];
    }
    if (sum == m) cout << i + 1;
    else cout << 0;
    return 0;
}
