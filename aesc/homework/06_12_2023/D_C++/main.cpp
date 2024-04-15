#include <iostream>

using namespace std;

const int32_t inf = 1e9, minus_inf = -1e9;

int main() {
    int32_t n, min_minus = 0, max_minus = minus_inf, min_plus = inf, max_plus = 0, minus_cnt = 0, plus_cnt = 0;
    bool zero_exists = false;
    cin >> n;
    for (int32_t i = 0, num; i < n; ++i) {
        cin >> num;
        if (num < 0) {
            if (num < min_minus) min_minus = num;
            else if (num > max_minus) max_minus = num;
            ++minus_cnt;
        } else if (num > 0) {
            if (num < min_plus) min_plus = num;
            else if (num > max_plus) max_plus = num;
            ++plus_cnt;
        } else zero_exists = true;
    }
    int32_t a = 0, b = 0;
    if (plus_cnt >= 2) {
        a = max_plus;
        b = min_plus;
    }
    if (minus_cnt >= 2 && (!b || min_minus * b < a * max_minus)) {
        a = min_minus;
        b = max_minus;
    }
    if (zero_exists && !b) {
        if (minus_cnt > 0) b = min_minus;
        else b = min_plus;
    }
    if (!zero_exists && !b) {
        if (min_minus * min_minus < min_plus * min_plus) {
            a = min_minus;
            b = min_plus;
        } else {
            a = min_plus;
            b = min_minus;
        }
    }
    cout << a << " " << b;
    return 0;
}
