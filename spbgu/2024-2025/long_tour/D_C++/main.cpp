#include <iostream>

using namespace std;

constexpr int maxn = 50;

char t1[maxn * 2][maxn * 2], t2[maxn * 3][maxn * 3];

int n;

void t2_step(int &i, int &j) {
    if (++j > i) ++i, j = 0;
}

void solve_petya() {
    int i2 = 0, j2 = 0;
    for (int i = 0; i < 3 * n; ++i) for (int j = 0; j < 3 * n; ++j) t2[i][j] = '0';
    for (int i = 0; i < 2 * n; ++i, t2_step(i2, j2)) {
        for (int j = 0; j < 2 * n; ++j, t2_step(i2, j2)) {
            cin >> t1[i][j];
            t2[i2][j2] = t2[j2][i2] = t1[i][j];
        }
    }
    for (int i = 0; i < 3 * n; ++i) {
        for (int j = 0; j < 3 * n; ++j) cout << t2[i][j];
        cout << "\n";
    }
}

void solve_natasha() {
    int i2 = 0, j2 = 0;
    for (int i = 0; i < 2 * n; ++i) for (int j = 0; j < 2 * n; ++j) t1[i][j] = '0';
    for (int i = 0; i < 3 * n; ++i) for (int j = 0; j < 3 * n; ++j) cin >> t2[i][j];
    for (int i = 0; i < 2 * n; ++i, t2_step(i2, j2))
        for (int j = 0; j < 2 * n; ++j, t2_step(i2, j2))
            t1[i][j] = t2[i2][j2];
    for (int i = 0; i < 2 * n; ++i) {
        for (int j = 0; j < 2 * n; ++j) cout << t1[i][j];
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    string type;
    cin >> type >> n;
    if (type == "Petya") solve_petya();
    else solve_natasha();
    return 0;
}
