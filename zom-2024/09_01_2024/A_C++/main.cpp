#include <iostream>
#include <limits>
#include <vector>

using namespace std;

const uint32_t inf = numeric_limits<uint32_t>::max();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    uint32_t n, m;
    cin >> n >> m;
    uint32_t temp, fx = inf, fy = inf, sx = inf, sy = inf;
    for (uint32_t i = 0; i < n; ++i) {
        for (uint32_t j = 0; j < m; ++j) {
            cin >> temp;
            if (temp == 1) {
                if (fx == inf) fx = i, fy = j;
                else sx = i, sy = j;
            }
        }
    }
    uint32_t mr = 0;
    if (fx < sx) mr = max(mr, m * sx);
    else if (fx > sx) mr = max(mr, m * (n - sx - 1));
    if (fy < sy) mr = max(mr, n * sy);
    else if (fy > sy) mr = max(mr, n * (m - sy - 1));
    swap(fx, sx);
    swap(fy, sy);
    if (fx < sx) mr = max(mr, m * sx);
    else if (fx > sx) mr = max(mr, m * (n - sx - 1));
    if (fy < sy) mr = max(mr, n * sy);
    else if (fy > sy) mr = max(mr, n * (m - sy - 1));
    cout << mr;
    return 0;
}
