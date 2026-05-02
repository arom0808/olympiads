#include <iostream>
#include <numeric>
#include <list>
#include <vector>

using namespace std;
using ll = long long;

constexpr int maxn = 5e4;
int nums[maxn];
int n;
ll pf[maxn + 1];
ll ans = -1e18;

void stupid_solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> nums[i];
    for (int l = 0; l < n; ++l) {
        for (int r = l + 1; r <= n; ++r) {
            int gcv = nums[l], max_val = -1e7;
            ll  sum = 0;
            for (int i = l; i < r; ++i) {
                gcv = std::gcd(gcv,  nums[i]);
                max_val = std::max(max_val, nums[i]);
                sum += nums[i];
            }
            ans = std::max(ans, 1ll * gcv * (sum - max_val));
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt","r",stdin);
#endif
    stupid_solve();
    return 0;
}
