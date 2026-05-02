#include <iostream>

using namespace std;

constexpr int maxn = 100;

// char dp[maxn][maxn][maxn][maxn];

int n, m;

inline bool is_win(int x1, int y1, int x2, int y2) {
    return x1 == x2 && y1 == y2;
}

inline bool is_lose(int x1, int y1, int x2, int y2) {
    return x2 < x1 || y1 < y2;
}

void solve() {
    cin >> n >> m;
    int x1 = 0, y1 = m - 1, x2 = n - 1, y2 = 0;
    while (true) {
        char c;
        cin >> c;
        if (c == 'R') ++y2;
        else --x2;
        if (is_win(x1, y1, x2, y2) || is_lose(x1, y1, x2, y2)) return;
        if (x2 - x1 > y1 - y2) ++x1, cout << "D\n";
        else --y1, cout << "L\n";
        cout.flush();
        if (is_win(x1, y1, x2, y2) || is_lose(x1, y1, x2, y2)) return;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // #ifdef LOCAL
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif
    solve();
    return 0;
}
