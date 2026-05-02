#include <iostream>
#include <vector>

using namespace std;

constexpr long double eps = 1e-6;
constexpr int32_t maxn = 10, maxm = 1e5;
int32_t n, m;
int32_t seg_limit[maxn];
int32_t seg_len[maxn];
int32_t excess_limits[maxm];
int32_t fines[maxm + 1];
int64_t full_len = 0;

bool is_excess_necessary(int32_t t, int32_t a) {
    long double min_t = 0;
    for (int32_t i = 0; i < n; ++i) min_t += static_cast<long double>(seg_len[i]) / (seg_limit[i] + excess_limits[a]);
    return min_t - t > eps;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int32_t i = 0; i < n; ++i) cin >> seg_limit[i];
    for (int32_t i = 0; i < n; ++i) cin >> seg_len[i], full_len += seg_len[i];
    cin >> m;
    excess_limits[0] = 0;
    for (int32_t i = 1; i < m; ++i) cin >> excess_limits[i];
    for (int32_t i = 0; i < m; ++i) cin >> fines[i];
    int32_t q;
    cin >> q;
    for (int32_t i = 0, s, t; i < q; ++i) {
        cin >> s >> t;
        int32_t l = 0, r = m;
        while (r - l > 1) {
            int32_t mid = (l + r) / 2;
            if (is_excess_necessary(t - s, mid)) l = mid;
            else r = mid;
        }
        if (is_excess_necessary(t - s, l)) cout << fines[l] << "\n";
        else cout << "0\n";
    }
    return 0;
}
