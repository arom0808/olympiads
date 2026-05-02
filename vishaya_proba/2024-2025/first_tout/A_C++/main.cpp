#include <iostream>
#include <vector>
#include <functional>
#include <set>

using namespace std;
using ll = int64_t;

constexpr int maxn = 1e6;
vector<int> g[maxn];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        g[i].clear();
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
