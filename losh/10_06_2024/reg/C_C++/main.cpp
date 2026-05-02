#include <iostream>
#include <vector>

using namespace std;

const int32_t maxn = 500;
int32_t in_g_id[maxn][maxn];
pair<int32_t, int32_t> pos_by_g_id[maxn * maxn * 2];
int32_t crossing_cnt = 0;
int32_t campus_in_line[maxn], campus_in_col[maxn];
int32_t table[maxn][maxn];
vector<int32_t> g[maxn * maxn * 2], rg[maxn * maxn * 2];
vector<int32_t> topsort;
int32_t comp[maxn * maxn * 2];
int32_t cnt_comp = 0;
bool used[maxn * maxn * 2];
int32_t n;

void dfs1(int32_t v) {
    used[v] = true;
    for (auto u: g[v]) if (!used[u]) dfs1(u);
    topsort.push_back(v);
}

void dfs2(int32_t v) {
    comp[v] = cnt_comp;
    for (auto u: rg[v]) if (comp[u] == -1) dfs2(u);
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (auto &l: in_g_id) for (auto &v: l) v = -1;
    for (auto &[a, b]: pos_by_g_id) a = b = -1;
    for (auto &p: campus_in_line) p = -1;
    for (auto &p: campus_in_col) p = -1;
    for (auto &v: comp) v = -1;
    cin >> n;
    char c;
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            cin >> c;
            if (c == 'O') {
                table[i][j] = 1;
                campus_in_line[i] = j;
                campus_in_col[j] = i;
            } else if (c == '+') {
                table[i][j] = 2;
                in_g_id[i][j] = crossing_cnt * 2;
                pos_by_g_id[crossing_cnt * 2] = {i, j};
                ++crossing_cnt;
            }
        }
    }
    for (int32_t _ = 0; _ < crossing_cnt; ++_) {
        int32_t i = _ * 2;
        auto [p1, p2] = pos_by_g_id[i];
        if (campus_in_line[p1] == -1 && campus_in_col[p2] == -1) {
            cout << "No\n";
            return 0;
        } else if (campus_in_line[p1] == -1) {
            g[i].push_back(i + 1);
            int32_t j;
            if (campus_in_col[p2] < p1) j = in_g_id[p1 - 1][p2];
            else j = in_g_id[p1 + 1][p2];
            if (std::abs(campus_in_col[p2] - p1) > 1) {
                if (j == -1) {
                    cout << "No\n";
                    return 0;
                } else g[j].push_back(j + 1);
            }
        } else if (campus_in_col[p2] == -1) {
            g[i + 1].push_back(i);
            int32_t k;
            if (campus_in_line[p1] < p2) k = in_g_id[p1][p2 - 1];
            else k = in_g_id[p1][p2 + 1];
            if (std::abs(campus_in_line[p1] - p2) > 1) {
                if (k == -1) {
                    cout << "No\n";
                    return 0;
                } else g[k + 1].push_back(k);
            }
        } else {
            int32_t j, k;
            if (campus_in_col[p2] < p1) j = in_g_id[p1 - 1][p2];
            else j = in_g_id[p1 + 1][p2];
            if (campus_in_line[p1] < p2) k = in_g_id[p1][p2 - 1];
            else k = in_g_id[p1][p2 + 1];
            if (std::abs(campus_in_col[p2] - p1) > 1) {
                if (j == -1) g[i + 1].push_back(i);
                else {
                    g[i + 1].push_back(j + 1);
                    g[j].push_back(i);
                }
            }
            if (std::abs(campus_in_line[p1] - p2) > 1) {
                if (k == -1) g[i].push_back(i + 1);
                else {
                    g[i].push_back(k);
                    g[k + 1].push_back(i + 1);
                }
            }
        }
    }
    for (int32_t v = 0; v < crossing_cnt * 2; ++v) for (auto u: g[v]) rg[u].push_back(v);
    for (int32_t v = 0; v < crossing_cnt * 2; ++v) if (!used[v]) dfs1(v);
    reverse(topsort.begin(), topsort.end());
    for (auto v: topsort) if (comp[v] == -1) dfs2(v), ++cnt_comp;
    for (int32_t v = 0; v < crossing_cnt * 2; v += 2) {
        int32_t nxp = comp[v], xp = comp[v + 1];
        if (nxp == xp) {
            cout << "No\n";
            return 0;
        }
        auto [a, b] = pos_by_g_id[v];
        if (nxp < xp) table[a][b] = 4;
        else table[a][b] = 3;
    }
    cout << "Yes\n";
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            if (table[i][j] == 0) cout << '.';
            else if (table[i][j] == 1) cout << 'O';
            else if (table[i][j] == 3) cout << '-';
            else cout << '|';
        }
        cout << '\n';
    }
    return 0;
}
