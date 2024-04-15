#include <iostream>
#include <vector>

using namespace std;

uint32_t bits_cnt(uint64_t n) {
    uint32_t res = 0;
    while (n) {
        n = n & (n - 1);
        ++res;
    }
    return res;
}

const uint64_t mod = 1e9 + 7;

int main() {
    uint64_t a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a <= 1000 && b <= 1000 && c <= 1000 && d <= 1000) {
        uint64_t res = 0;
        for (uint64_t n = a; n <= b; ++n)
            for (uint64_t k = c; k <= d; ++k)
                if (!((~n) & k))
                    ++res;
        cout << res;
    } else {
        if (b < 2) {
            if (b == 0) cout << 1;
            else cout << 2;
            return 0;
        }
        uint32_t ml = __lg(b);
        vector<uint64_t> dp(ml + 2);
        dp[0] = 1;
        dp[1] = 2;
        for (uint32_t i = 0; i <= ml + 1; ++i) {

        }
    }
    return 0;
}
