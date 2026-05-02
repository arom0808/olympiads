#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

int main() {
    freopen("test.txt", "r", stdin);
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, m;
    cin >> n >> m;
    vector<int32_t> ds(n);
    for (int32_t i = 0; i < n; ++i) cin >> ds[i], ds[i] += i;
    for (int32_t i = 0, a, b, c; i < m; ++i) {
        cin >> c >> a, --a;
        if (c == 0) {
            cin >> b;
            ds[a] = a + b;
        } else {
            int32_t mc = 0;
            while (ds[a] < n) ++mc, a = ds[a];
            cout << a + 1 << " " << mc + 1 << "\n";
        }
    }
    return 0;
}
