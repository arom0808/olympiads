#include <iostream>

using namespace std;

int main() {
    uint32_t n;
    cin >> n;
    uint32_t min_i = 0, max_i = 0;
    int64_t before_min_sum = 0, with_min_sum = 0, before_max_sum = 0, with_max_sum = 0, sum = 0;
    int32_t min_el = 2e9, max_el = -2e9, el;
    for (uint32_t i = 0; i < n; ++i) {
        cin >> el;
        if (el < min_el) {
            min_el = el, min_i = i;
            before_min_sum = sum, with_min_sum = sum + el;
        }
        if (el > max_el) {
            max_el = el, max_i = i;
            before_max_sum = sum, with_max_sum = sum + el;
        }
        sum += el;
    }
    if (min_i < max_i) cout << with_max_sum - before_min_sum;
    else cout << with_min_sum - before_max_sum;
    return 0;
}
