#include <iostream>

using namespace std;
using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    if (n == 6) cout << 6 << "\n";
    else cout << n << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt","r",stdin);
    solve();
    return 0;
}
