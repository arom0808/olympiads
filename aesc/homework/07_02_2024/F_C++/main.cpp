#include <iostream>

using namespace std;

inline bool cat(int32_t num) { return num == 0; }

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n;
    cin >> n;
    int32_t arr[n];
    for (auto &val: arr) cin >> val;
    int32_t pos_to_insert = n - 1, t;
    for (int32_t i = n - 1; i >= 0; --i) {
        if (!cat(arr[i])) continue;
        t = arr[i];
        for (int32_t j = i; j < pos_to_insert; ++j) arr[j] = arr[j + 1];
        arr[pos_to_insert--] = t;
    }
    for (auto el: arr) cout << el << " ";
    return 0;
}
