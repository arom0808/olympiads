#include <iostream>

using namespace std;

int n, k;
constexpr int maxk = 1e6;


void solve1() {

}

void solve2() {
}

void solve() {
    cin >> n >> k;
    if (k > __lg(k) + 1) {
        solve1();
    } else {
        solve2();
    }
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
