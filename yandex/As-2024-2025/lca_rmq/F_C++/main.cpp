#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>

using namespace std;

constexpr int maxn = 1500, inf = 1e9;

int raw_table[maxn][maxn];

int n, q;

namespace ST {
    int table[2][maxn][maxn][11];
    int first_pow = 0;

    void merge(int a1[11], int a2[11], int a3[11], int a4[11], int res[11]) {
        int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
        for (int i = 0; i < 11; ++i) {
            res[i] = a1[i1];
            if (a2[i2] < res[i]) res[i] = a2[i2];
            if (a3[i3] < res[i]) res[i] = a3[i3];
            if (a4[i4] < res[i]) res[i] = a4[i4];
            if (a1[i1] == res[i]) ++i1;
            if (a2[i2] == res[i]) ++i2;
            if (a3[i3] == res[i]) ++i3;
            if (a4[i4] == res[i]) ++i4;
        }
    }

    void gen_next() {
        int pid = first_pow & 1, nid = !pid;
        int k = first_pow + 1;
        for (int i = 0; i + (1 << k) <= n; ++i)
            for (int j = 0; j + (1 << k) <= n; ++j)
                merge(table[pid][i][j], table[pid][i][j + (1 << (k - 1))],
                      table[pid][i + (1 << (k - 1))][j], table[pid][i + (1 << (k - 1))][j + (1 << (k - 1))],
                      table[nid][i][j]);
    }

    void step_pow() {
        ++first_pow;
        gen_next();
    }

    void init() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                table[0][i][j][0] = raw_table[i][j];
                for (int k = 1; k < 11; ++k) table[0][i][j][k] = inf;
            }
        }
        gen_next();
    }

    void min_val(int i, int j, int sz, int res[11]) {
        int k = __lg(sz);
        int pid = first_pow & 1, nid = !pid;
        int pk = k == first_pow ? pid : nid;
        merge(table[pk][i][j], table[pk][i][j + sz - (1 << k)], table[pk][i + sz - (1 << k)][j],
              table[pk][i + sz - (1 << k)][j + sz - (1 << k)], res);
    }
}

bool is_sarr_ok(int arr[11]) {
    for (int i = 10; i >= q; --i) if (arr[i] != inf) return false;
    return true;
}

int anspf[maxn + 1];
bool used[maxn][maxn];

void solve() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> raw_table[i][j];
    ST::init();
    int tarr[11];
    for (int k = 1; (1 << k) <= n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (used[i][j]) continue;
                int l = 1 << (k - 1), r = std::min(std::min(n - i, n - j) + 1, 1 << (k + 1));
                if (l >= r) continue;
                ST::min_val(i, j, r - 1, tarr);
                if (is_sarr_ok(tarr)) continue;
                while (r - l != 1) {
                    int mid = (l + r) / 2;
                    ST::min_val(i, j, mid, tarr);
                    if (is_sarr_ok(tarr)) l = mid;
                    else r = mid;
                }
                ++anspf[1];
                --anspf[l + 1];
                used[i][j] = true;
            }
        }
        ST::step_pow();
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (used[i][j]) continue;
            int r = std::min(n - i, n - j) + 1;
            ++anspf[1];
            --anspf[r];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += anspf[i];
        cout << ans << "\n";
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
