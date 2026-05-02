#include <iostream>
#include <vector>
#include <set>

using namespace std;

constexpr int maxn = 5000;

int n;
vector<int> gr[maxn], gb[maxn];
bool apr[maxn][maxn], apb[maxn][maxn];

void solve() {
    cin >> n;
    char c;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            cin >> c;
            if (c == 'B') gb[i].push_back(i + j + 1);
            else gr[i].push_back(i + j + 1);
        }
    }
    for (int v = n - 1; v >= 0; --v) {
        for (auto u: gr[v]) {
            if (apr[v][u]) continue;
            apr[v][u] = true;
            for (int i = u; i < n; ++i) apr[v][i] |= apr[u][i];
        }
        for (auto u: gb[v]) {
            if (apb[v][u]) continue;
            apb[v][u] = true;
            for (int i = u; i < n; ++i) apb[v][i] |= apb[u][i];
        }
        for (int u = v; u < n; ++u) {
            if (apr[v][u] && apb[v][u]) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
