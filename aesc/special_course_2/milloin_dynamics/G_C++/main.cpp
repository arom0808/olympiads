#include <iostream>

using namespace std;

int main() {
    int32_t n, k;
    string st;
    cin >> n >> k >> st;
    int32_t res = 0;
    for (int32_t c = 0; c < n; ++c) {
        for (int32_t shift = 0; shift < 2; ++shift) {
            for (int32_t errs_cnt = 0, l = c, r = c + shift; l >= 0 && r < n; --l, ++r) {
                if (st[l] != st[r]) ++errs_cnt;
                if (errs_cnt <= k) ++res;
                else break;
            }
        }
    }
    cout << res;
    return 0;
}
