#include <iostream>

using namespace std;

const int32_t inf = 1e9;

int main() {
    int32_t n;
    cin >> n;
    int32_t arr[n];
    for (auto &val: arr) cin >> val;
    for (int32_t i = 0; i < n; ++i) {
        if (arr[i] == inf) continue;
        int32_t cnt = 1;
        for (int32_t j = i + 1; j < n; ++j) if (arr[j] == arr[i]) arr[j] = inf, ++cnt;
        if (cnt > 1) cout << arr[i] << " ";
    }
    return 0;
}
