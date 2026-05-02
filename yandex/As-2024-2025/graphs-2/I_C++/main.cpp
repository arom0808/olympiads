#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 5e4 + 10;



int nx, mx, ny, my;
vector<pair<int, int> > gx[maxn], gy[maxn];

void task1() {

}

void task2() {
}

void solve() {
    int task;
    cin >> task >> nx >> mx;
    for (int i = 0, u, v, w; i < mx; ++i) {
        cin >> u >> v >> w, --u, --v;
        gx[u].emplace_back(v, w), gx[v].emplace_back(u, w);
    }
    cin >> ny >> my;
    for (int i = 0, u, v, w; i < my; ++i) {
        cin >> u >> v >> w, --u, --v;
        gy[u].emplace_back(v, w), gy[v].emplace_back(u, w);
    }
    if (task == 1) task1();
    else task2();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
