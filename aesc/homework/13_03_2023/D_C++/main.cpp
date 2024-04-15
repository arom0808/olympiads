#include <iostream>

using namespace std;

int main() {
    uint32_t n, k;
    cin >> n >> k;
    uint64_t used1 = 0, used2 = 0;
    int32_t arr[n];
    for (uint32_t i = 0; i < n; ++i) cin >> arr[i];
    for (uint32_t i = 0; i < n; ++i) {
        if ((i < 64 && ((used1 >> i) & 1)) || (i >= 64 && ((used2 >> (i - 64)) & 1))) continue;
        int32_t el = arr[i];
        uint32_t j = i;
        for (; !((j < 64 && ((used1 >> j) & 1)) || (j >= 64 && ((used2 >> (j - 64)) & 1))); j = (j + k) % n) {
            if (j < 64) used1 |= 1ull << j;
            else used2 |= 1ull << (j - 64);
            swap(el, arr[j]);
        }
        arr[j] = el;
    }
    for (auto el: arr) cout << el << " ";
    return 0;
}
