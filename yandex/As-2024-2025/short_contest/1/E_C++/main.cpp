#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Ceil {
    int32_t h, x, y;

    bool operator<(const Ceil &other) const {
        if (h != other.h) return h < other.h;
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

const int32_t maxn = 1000;
bool used[maxn][maxn];
set<Ceil> ready_ceils;
int32_t ceils[maxn][maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n, m, k;
    cin >> n >> m >> k;
    for (int32_t i = 0; i < n; ++i) for (int32_t j = 0; j < m; ++j) cin >> ceils[i][j];
    for (int32_t i = 0; i < n; ++i) {
        ready_ceils.emplace(ceils[i][0], i, 0);
        if (m > 1) ready_ceils.emplace(ceils[i][m - 1], i, m - 1);
        used[i][0] = used[i][m - 1] = true;
    }
    for (int32_t i = 0; i < m; ++i) {
        ready_ceils.emplace(ceils[0][i], 0, i);
        if (n > 1) ready_ceils.emplace(ceils[n - 1][i], n - 1, i);
        used[0][i] = used[n - 1][i] = true;
    }
    int32_t under_ceils = 0;
    for (int32_t l = 1; l <= k; ++l) {
        while (!ready_ceils.empty() && ready_ceils.begin()->h <= l) {
            auto [h,x,y] = *ready_ceils.begin();
            ready_ceils.erase(ready_ceils.begin());
            ++under_ceils;
            if (x > 0 && !used[x - 1][y]) ready_ceils.emplace(ceils[x - 1][y], x - 1, y), used[x - 1][y] = true;
            if (x + 1 < n && !used[x + 1][y]) ready_ceils.emplace(ceils[x + 1][y], x + 1, y), used[x + 1][y] = true;
            if (y > 0 && !used[x][y - 1]) ready_ceils.emplace(ceils[x][y - 1], x, y - 1), used[x][y - 1] = true;
            if (y + 1 < m && !used[x][y + 1]) ready_ceils.emplace(ceils[x][y + 1], x, y + 1), used[x][y + 1] = true;
        }
        cout << n * m - under_ceils << "\n";
    }
    return 0;
}
