#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    int64_t n;
    cin >> n;
    vector<int64_t> dp1(10, 1), dp2(10, 0);
    dp1[0] = 0;
    for (int64_t i = 1; i < n; ++i) {
        for (int64_t prd = 0; prd < 10; ++prd)
            for (int64_t ch = -1; ch <= 1; ++ch)
                if (prd + ch >= 0 && prd + ch <= 9)
                    dp2[prd + ch] += dp1[prd];
        dp1.swap(dp2);
        fill(dp2.begin(), dp2.end(), 0ll);
    }
    cout << accumulate(dp1.begin(), dp1.end(), 0ll);
    return 0;
}
