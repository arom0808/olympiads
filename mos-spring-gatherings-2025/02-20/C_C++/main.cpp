#include <iostream>
#include <random>

using namespace std;

constexpr int n = 100, m = 10;
mt19937 rng(63654);

int randint(int a, int b) {
    return uniform_int_distribution<int>(a, b)(rng);
}

void solve() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m; ++j) {
            int dj = 0;
            if (i <= 2 && !(j & (1 << i))) dj = 1 << i;
            int nj = j + dj;
            if (!(nj & 1)) {
                if (i != 0) cout << "1 ";
                else cout << randint(4, n) << " ";
            } else if (!(nj & 2)) {
                if (i != 1) cout << "2 ";
                else cout << randint(4, n) << " ";
            } else if (!(nj & 4)) {
                if (i != 2) cout << "3 ";
                else cout << randint(4, n) << " ";
            } else {
                int r;
                do r = randint(3, n - 1); while (r == i);
                cout << r + 1 << " ";
            }
            cout << dj << " ";
        }
        cout << "\n";
    }
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
