#include <iostream>

using namespace std;

constexpr int maxn = 20;

int table[maxn][maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> table[i][j];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << table[n - j - 1][i] << " ";
        cout << "\n";
    }
    return 0;
}
