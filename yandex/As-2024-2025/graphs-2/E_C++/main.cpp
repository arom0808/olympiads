#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

constexpr int maxn = 3010;

int n;

void init_cycle(int arr[maxn], int cycles[maxn], int v, int cid) {
    while (cycles[v] == -1) cycles[v] = cid, v = arr[v];
}

void init_cycles(int arr[maxn], int cycles[maxn], int &cycles_cnt) {
    for (int i = 0; i < n; ++i) cycles[i] = -1;
    cycles_cnt = 0;
    for (int i = 0; i < n; ++i) if (cycles[i] == -1) init_cycle(arr, cycles, i, cycles_cnt++);
}

int sap[maxn], sbp[maxn];
int ca[maxn], cb[maxn];
int cnta = 0, cntb = 0;
vector<pair<int, int> > g[maxn];
int used[maxn];
pair<int, int> mt[maxn];
int timer = 0;

bool dfs(int v) {
    if (used[v] == timer) return false;
    used[v] = timer;
    for (auto [u, eid]: g[v]) {
        if (mt[u].first != -1) continue;
        mt[u] = {v, eid};
        return true;
    }
    for (auto [u,eid]: g[v]) {
        if (!dfs(mt[u].first)) continue;
        mt[u] = {v, eid};
        return true;
    }
    return false;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> sap[i], --sap[i];
    for (int i = 0; i < n; ++i) cin >> sbp[i], --sbp[i];
    init_cycles(sap, ca, cnta);
    init_cycles(sbp, cb, cntb);
    for (int i = 0; i < n; ++i) g[ca[i]].emplace_back(cb[i], i);
    for (int i = 0; i < cnta; ++i) sort(g[i].begin(), g[i].end());
    for (int i = 0; i < cnta; ++i)
        g[i].erase(unique(g[i].begin(), g[i].end(),
                          [](const pair<int, int> &a, const pair<int, int> &b) { return a.first == b.first; }),
                   g[i].end());
    for (int i = 0; i < cntb; ++i) mt[i] = {-1, -1};
    ++timer;
    int ans_cnt = 0;
    for (int i = 0; i < cnta; ++i) if (dfs(i)) ++ans_cnt, ++timer;
    cout << n - ans_cnt << "\n";
    vector<int> unused;
    for (int i = 0; i < cntb; ++i) if (mt[i].first != -1) unused.push_back(mt[i].second);
    sort(unused.begin(), unused.end());
    for (int i = 0; i < n; ++i) if (!binary_search(unused.begin(), unused.end(), i)) cout << i + 1 << " ";
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
