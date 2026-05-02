#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>

using namespace std;
using ll = long long;

constexpr int maxn = 1510;

bool table[maxn][maxn];
int pf[maxn][maxn];
int n, m, k;
ll ans = 0;

int rect_sum(int i0, int j0, int i1, int j1) {
    return pf[i1][j1] - pf[i0][j1] - pf[i1][j0] + pf[i0][j0];
}

int find_left_one(int j0, int f, int t, int rs, int cnt, int r) {
    int l = j0 - 1;
    while (r - l != 1) {
        int mid = (l + r) / 2;
        if (rect_sum(f, mid, t, rs) >= cnt) l = mid;
        else r = mid;
    }
    return l;
}

int find_up_one(int i0, int f, int t, int bs, int cnt, int r) {
    int l = i0 - 1;
    while (r - l != 1) {
        int mid = (l + r) / 2;
        if (rect_sum(mid, f, bs, t) >= cnt) l = mid;
        else r = mid;
    }
    return l;
}

int find_right_one(int j1, int f, int t, int rs, int cnt, int l) {
    int r = j1 + 1;
    while (r - l != 1) {
        int mid = (l + r) / 2;
        if (rect_sum(f, rs, t, mid) >= cnt) r = mid;
        else l = mid;
    }
    return r;
}

int find_bottom_one(int i1, int f, int t, int bs, int cnt, int l) {
    int r = i1 + 1;
    while (r - l != 1) {
        int mid = (l + r) / 2;
        if (rect_sum(bs, f, mid, t) >= cnt) r = mid;
        else l = mid;
    }
    return r;
}

int temp_cnts[2][10];

void rec_split(int i0, int j0, int i1, int j1) {
    if (i1 - i0 < 1 || j1 - j0 < 1) return;
    if (i1 - i0 == 1 && j1 - j0 == 1) {
        if (k == 0 && !table[i0][j0]) ++ans;
        if (k == 1 && table[i0][j0]) ++ans;
        return;
    }
    if (j1 - j0 >= i1 - i0) {
        int right_start = (j0 + j1) / 2;
        for (int f = i0; f < i1; ++f) {
            for (int t = f + 1; t <= i1; ++t) {
                for (int i = 0; i <= k + 1; ++i) {
                    temp_cnts[0][i] = find_left_one(j0, f, t, right_start, i,
                                                    i == 0 ? right_start : temp_cnts[0][i - 1] + 1);
                }
                for (int i = 0; i <= k + 1; ++i) {
                    temp_cnts[1][i] = find_right_one(j1, f, t, right_start, i,
                                                     i == 0 ? right_start : temp_cnts[1][i - 1] - 1);
                }
                for (int lcnt = 0; lcnt <= k; ++lcnt) {
                    int rcnt = k - lcnt;
                    if (temp_cnts[0][lcnt + 1] >= temp_cnts[0][lcnt] ||
                        temp_cnts[1][rcnt] >= temp_cnts[1][rcnt + 1])
                        continue;
                    ans += (temp_cnts[1][rcnt + 1] - temp_cnts[1][rcnt]) *
                            (temp_cnts[0][lcnt] - temp_cnts[0][lcnt + 1]);
                }
            }
        }
        rec_split(i0, j0, i1, right_start);
        rec_split(i0, right_start, i1, j1);
    } else {
        int bottom_start = (i0 + i1) / 2;
        for (int f = j0; f < j1; ++f) {
            for (int t = f + 1; t <= j1; ++t) {
                for (int i = 0; i <= k + 1; ++i)
                    temp_cnts[0][i] = find_up_one(i0, f, t, bottom_start, i,
                                                  i == 0 ? bottom_start : temp_cnts[0][i - 1] + 1);
                for (int i = 0; i <= k + 1; ++i)
                    temp_cnts[1][i] = find_bottom_one(i1, f, t, bottom_start, i,
                                                      i == 0 ? bottom_start : temp_cnts[1][i - 1] - 1);
                for (int ucnt = 0; ucnt <= k; ++ucnt) {
                    int bcnt = k - ucnt;
                    if (temp_cnts[0][ucnt + 1] >= temp_cnts[0][ucnt] ||
                        temp_cnts[1][bcnt] >= temp_cnts[1][bcnt + 1])
                        continue;
                    ans += (temp_cnts[0][ucnt] - temp_cnts[0][ucnt + 1]) *
                            (temp_cnts[1][bcnt + 1] - temp_cnts[1][bcnt]);
                }
            }
        }
        rec_split(i0, j0, bottom_start, j1);
        rec_split(bottom_start, j0, i1, j1);
    }
}

void solve() {
    cin >> n >> m >> k;
    char c;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> c;
            table[i][j] = c == '1';
        }
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            pf[i + 1][j + 1] = pf[i][j + 1] + pf[i + 1][j] - pf[i][j] + table[i][j];
    rec_split(0, 0, n, m);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    solve();
    return 0;
}
