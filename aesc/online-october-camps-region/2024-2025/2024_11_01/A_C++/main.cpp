#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> cars(n), car_poss(n);
    iota(cars.begin(), cars.end(), 0);
    iota(car_poss.begin(), car_poss.end(), 0);
    for (int i = 0, x, y; i < m; ++i) {
        cin >> x >> y, --x, --y;
        int yp = car_poss[y];
        swap(cars[yp], cars[yp + 1]);
        car_poss[cars[yp]] = yp;
        car_poss[cars[yp + 1]] = yp + 1;
    }
    for (auto el: cars) cout << el + 1 << " ";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    solve();
#endif
    return 0;
}
