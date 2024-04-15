#include <iostream>

using namespace std;

int main() {
    uint32_t n;
    cin >> n;
    int64_t max_sum = -3e9, max_now_end_sum = 0;
    uint32_t best_left, best_right, now_left = 0;
    int32_t el;
    for (uint32_t i = 0; i < n; ++i) {
        cin >> el;
        if (max_now_end_sum > 0) max_now_end_sum += el;
        else max_now_end_sum = el, now_left = i;
        if (max_now_end_sum > max_sum) max_sum = max_now_end_sum, best_left = now_left, best_right = i;
    }
    cout << best_left + 1 << " " << best_right + 1;
    return 0;
}
