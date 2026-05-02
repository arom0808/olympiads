#include <iostream>
#include <cstdint>

using namespace std;

const int32_t maxn = 1e6;
int32_t n, k;
int32_t arr[maxn];

int32_t bs(int32_t l, int32_t r) {
    if (r - l == 1) return arr[r] == k ? r + 1 : 0;
    int32_t m = (l + r) / 2;
    if (arr[m] < k) return bs(m, r);
    return bs(l, m);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> k >> n;
    for (int32_t i = 0; i < n; ++i) cin >> arr[i];
    cout << bs(-1, n - 1) << "\n";
    return 0;
}
