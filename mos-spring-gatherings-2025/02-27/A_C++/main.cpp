#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

constexpr int maxn = 1010, maxq = 2e5 + 10;

int n, q;
bool cycled[maxn][maxn];
int dir[maxn][maxn];

int ans = 0;

void solve() {
    cin >> n >> q;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t = 1;
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    cin >> t;
#endif
#ifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    while (t--) solve();
    return 0;
}
