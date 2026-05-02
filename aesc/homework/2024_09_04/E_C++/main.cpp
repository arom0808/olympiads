#include <iostream>
#include <cstdint>

using namespace std;

const int32_t maxn = 1e6;
const int32_t mod = 1e9 + 7;
int32_t n, k;
int32_t arr[maxn];

void rec(int32_t id = 0, int32_t ns = 0, int32_t nm = 1) {
    if (id == n) {
        if (ns > 0) cout << nm << "\n";
        return;
    }
    if (ns + arr[id] < k) rec(id + 1, ns + arr[id], 1ll * nm * arr[id] % mod);
    rec(id + 1, ns, nm);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int32_t i = 0; i < n; ++i) cin >> arr[i];
    rec();
    return 0;
}
