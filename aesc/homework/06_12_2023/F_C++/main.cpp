#include <iostream>

using namespace std;

void transport_md3(int64_t &max_div_3, int64_t &max_div_11, int64_t &max_no_div);

void transport_md11(int64_t &max_div_3, int64_t &max_div_11, int64_t &max_no_div);

void transport_md3(int64_t &max_div_3, int64_t &max_div_11, int64_t &max_no_div) {
    if (max_div_3 > max_div_11 && max_div_3 % 11 == 0) {
        transport_md11(max_div_3, max_div_11, max_no_div);
        max_div_11 = max_div_3;
    } else if (max_div_3 > max_no_div) max_no_div = max_div_3;
}

void transport_md11(int64_t &max_div_3, int64_t &max_div_11, int64_t &max_no_div) {
    if (max_div_11 > max_div_3 && max_div_11 % 3 == 0) {
        transport_md3(max_div_3, max_div_11, max_no_div);
        max_div_3 = max_div_11;
    } else if (max_div_11 > max_no_div) max_no_div = max_div_11;
}


int main() {
    int64_t n, max_div_3 = 0, max_div_11 = 0, max_no_div = 0;
    cin >> n;
    for (int64_t i = 0, num; i < n; ++i) {
        cin >> num;
        if (num % 3 == 0 && num > max_div_3) {
            transport_md3(max_div_3, max_div_11, max_no_div);
            max_div_3 = num;
        } else if (num % 11 == 0 && num > max_div_11) {
            transport_md11(max_div_3, max_div_11, max_no_div);
            max_div_11 = num;
        } else if (num > max_no_div) {
            max_no_div = num;
        }
    }
    int64_t v1 = max_div_3 * max_div_11, v2 = max_div_3 * max_no_div, v3 = max_div_11 * max_no_div;
    int64_t res = 0;
    if (v1 > res && v1 % 33 == 0) res = v1;
    if (v2 > res && v2 % 33 == 0) res = v2;
    if (v3 > res && v3 % 33 == 0) res = v3;
    if (res == 0) cout << -1;
    else cout << res;
    return 0;
}
