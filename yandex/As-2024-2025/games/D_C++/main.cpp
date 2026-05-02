#include <iostream>
#include <algorithm>

using namespace std;

constexpr int maxn = 1e5 + 10;
int arr[maxn];
int n;

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    sort(arr, arr + n, greater());
    int i = 0;
    while (i < n && i < arr[i]) ++i;
    --i;
    int x = arr[i] - i;
    int y = i;
    while (y < n && i < arr[y]) ++y;
    y -= i;
    if (x & y & 1) cout << "Second\n";
    else cout << "First\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t = 1;
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    cin >> t;
#endif
    while (t--) solve();
    return 0;
}
