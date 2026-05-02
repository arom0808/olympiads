#include <iostream>
#include <deque>

using namespace std;

const int maxn = 1001;
int ans[maxn][maxn];
int n, q;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> q;
    deque<pair<int, int> > deq;
    for (auto &row: ans) for (auto &j: row) j = -1;
    for (int i = 0, x, y; i < n; ++i) {
        cin >> x >> y;
        deq.emplace_back(x, y);
        ans[x][y] = 0;
    }
    while (!deq.empty()) {
        auto [x,y] = deq.front();
        deq.pop_front();
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (!(i || j)) continue;
                auto nx = x + i, ny = y + j;
                if (nx < 0 || nx > 1000 || ny < 0 || ny > 1000 || ans[nx][ny] != -1) continue;
                deq.emplace_back(nx, ny);
                ans[nx][ny] = ans[x][y] + 1;
            }
        }
    }
    for (int i = 0, x, y; i < q; ++i) {
        cin >> x >> y;
        cout << ans[x][y] << "\n";
    }
    return 0;
}
