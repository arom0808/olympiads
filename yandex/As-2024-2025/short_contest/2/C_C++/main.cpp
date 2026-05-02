#include <iostream>

using namespace std;

const int64_t mod = 998244353;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int64_t n, m;
    cin >> n >> m;
    int64_t ans = 0;
    for (int64_t bl_sz = 2; n >= bl_sz / 2; bl_sz <<= 1, m >>= 1) {
        if (!(m & 1)) continue;
        int64_t c_ans = (n + 1) / bl_sz * (bl_sz >> 1) + std::max<int64_t>((n + 1) % bl_sz - bl_sz / 2, 0);
        ans = (ans + c_ans % mod) % mod;
    }
    cout << ans;
    return 0;
}
