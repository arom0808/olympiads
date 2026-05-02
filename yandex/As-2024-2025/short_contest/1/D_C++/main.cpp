#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

constexpr int32_t max_vs = 6400000;

vector<int32_t> g[max_vs], t[max_vs];
int32_t n, q;
bool used[max_vs];
int32_t component[max_vs];
int32_t components_cnt = 0;
vector<int32_t> order;
bool used_in_or[max_vs];

void dfs1(int32_t v) {
    used[v] = true;
    for (auto u: g[v]) if (!used[u]) dfs1(u);
    order.push_back(v);
}

void dfs2(int32_t v) {
    component[v] = components_cnt;
    for (int u: t[v]) if (component[u] == 0) dfs2(u);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> q;
    for (int32_t _ = 0, i, j, x; _ < q; ++_) {
        cin >> i >> j >> x, --i, --j;
        used_in_or[i] = used_in_or[j] = true;
        for (int32_t k = 0; k < 30; ++k) {
            if ((x >> k) & 1) {
                g[i * 64 + k * 2].push_back(j * 64 + k * 2 + 1);
                g[j * 64 + k * 2].push_back(i * 64 + k * 2 + 1);
                t[j * 64 + k * 2 + 1].push_back(i * 64 + k * 2);
                t[i * 64 + k * 2 + 1].push_back(j * 64 + k * 2);
            } else {
                g[i * 64 + k * 2 + 1].push_back(i * 64 + k * 2);
                g[j * 64 + k * 2 + 1].push_back(j * 64 + k * 2);
                t[i * 64 + k * 2].push_back(i * 64 + k * 2 + 1);
                t[j * 64 + k * 2].push_back(j * 64 + k * 2 + 1);
            }
        }
    }
    for (int32_t i = 0; i < 64 * n; ++i) if (!used[i]) dfs1(i);
    reverse(order.begin(), order.end());
    for (auto v: order) if (component[v] == 0) dfs2(v), ++components_cnt;
    for (int32_t i = 0; i < n; ++i) {
        if (!used_in_or[i]) {
            cout << "0 ";
            continue;
        }
        int32_t res = 0;
        for (int32_t j = 0; j < 30; ++j) {
            if (component[i * 64 + j * 2 + 1] > component[i * 64 + j * 2]) res |= 1 << j;
        }
        cout << res << " ";
    }
    return 0;
}
