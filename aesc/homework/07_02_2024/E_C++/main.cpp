#include <iostream>

using namespace std;

int main() {
    int32_t n;
    cin >> n;
    int32_t arr[n];
    for (auto &el: arr) cin >> el;
    int32_t neg_cnt = 0, pos_cnt = 0, zero_cnt = 0;
    int32_t min_neg = 0, sec_min_neg = 0, max_pos = 0, sec_max_pos = 0;
    for (uint32_t i = 0; i < n; ++i) {
        if (arr[i] < 0) {
            ++neg_cnt;
            if (arr[i] <= min_neg) sec_min_neg = min_neg, min_neg = arr[i];
            else if (arr[i] < sec_min_neg) sec_min_neg = arr[i];
        } else if (arr[i] > 0) {
            ++pos_cnt;
            if (arr[i] >= max_pos) sec_max_pos = max_pos, max_pos = arr[i];
            else if (arr[i] > sec_max_pos) sec_max_pos = arr[i];
        } else ++zero_cnt;
    }
    int32_t n1 = -1e4, n2 = 1e5;
    if (zero_cnt) {
        n1 = 0;
        if (neg_cnt) n2 = min_neg;
        else n2 = max_pos;
    }
    if (neg_cnt >= 2 && min_neg * sec_min_neg > n1 * n2) n1 = min_neg, n2 = sec_min_neg;
    if (pos_cnt >= 2 && max_pos * sec_max_pos > n1 * n2) n1 = max_pos, n2 = sec_max_pos;
    if (neg_cnt && pos_cnt && min_neg * max_pos > n1 * n2) n1 = min_neg, n2 = max_pos;
    if (n1 > n2) swap(n1, n2);
    cout << n1 << " " << n2;
    return 0;
}
