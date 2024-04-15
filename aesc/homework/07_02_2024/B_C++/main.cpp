#include <iostream>

using namespace std;

int main() {
    uint32_t n;
    cin >> n;
    int32_t arr[n];
    for (auto &el: arr) cin >> el;
    uint32_t max_id = 0, max_cnt = 0;
    for (uint32_t i = 0; i < n; ++i) {
        if (arr[i] > arr[max_id]) max_id = i, max_cnt = 0;
        if (arr[i] == arr[max_id]) ++max_cnt;
    }
    cout << max_cnt;
    return 0;
}
