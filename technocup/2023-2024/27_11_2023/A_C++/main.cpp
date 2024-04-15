#include <iostream>
#include <vector>

using namespace std;

int main() {
    uint32_t n;
    cin >> n;
    vector<uint32_t> poss(n), vals(n);
    for (uint32_t i = 0, t; i < n; ++i) {
        cin >> t;
        poss[t - 1] = i;
    }
    for (uint32_t i = 0, t; i < n; ++i) {
        cin >> t;
        vals[poss[t - 1]] = i;
    }
    uint32_t res = 1;
    for (uint32_t i = 0; i + 1 < n; ++i) if (vals[i] + 1 != vals[i + 1]) ++res;
    cout << res;
    return 0;
}
