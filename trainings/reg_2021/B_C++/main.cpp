#include <iostream>
#include <cstdint>

using namespace std;

int64_t n, m;

int64_t first_k_rows_sum(int64_t k) {
    return (k * m + 1) * k * m / 2;
}

int64_t first_k_cols_sum(int64_t k) {
    return ((n - 1) * m + k + 1) * n * k / 2;
}

void sol() {
    cin >> n >> m;
    int64_t full_sum = (n * m + 1) * n * m / 2;
    int64_t l = 0, r = n;
    while (l != r) {
        auto mid = (l + r) / 2;
        auto f1 = std::abs(first_k_rows_sum(mid) * 2 - full_sum),
                f2 = std::abs(first_k_rows_sum(mid + 1) * 2 - full_sum);
        if (f1 > f2) l = mid + 1;
        else if (f1 < f2) r = mid;
        else l = mid, r = mid;
    }
    int64_t p1 = l;
    int64_t r1 = std::abs(first_k_rows_sum(l) * 2 - full_sum);
    l = 0, r = m;
    while (l != r) {
        auto mid = (l + r) / 2;
        auto f1 = std::abs(first_k_cols_sum(mid) * 2 - full_sum),
                f2 = std::abs(first_k_cols_sum(mid + 1) * 2 - full_sum);
        if (f1 > f2) l = mid + 1;
        else if (f1 < f2) r = mid;
        else l = mid, r = mid;
    }
    int64_t p2 = l, r2 = std::abs(first_k_cols_sum(l) * 2 - full_sum);
    if (r1 < r2) cout << "H " << p1 + 1 << "\n";
    else cout << "V " << p2 + 1 << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t t;
    cin >> t;
    while (t--) sol();
    return 0;
}
