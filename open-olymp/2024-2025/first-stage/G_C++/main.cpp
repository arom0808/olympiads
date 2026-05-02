#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

constexpr int maxn = 2e5;

int n, m;
pair<int, int> from_len[maxn];
vector<int> g[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m;
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v, u = (u - 1) * 2, v = (v - 1) * 2;
        g[u].push_back(v + 1), g[u + 1].push_back(v);
        g[v].push_back(u + 1), g[v + 1].push_back(u);
    }
    for (int i = 0; i < n * 2; ++i) from_len[i] = {-1, 1e9};
    from_len[0] = {-2, 1};
    deque<int> q;
    q.push_back(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (auto u: g[v]) {
            if (from_len[u].first != -1 || from_len[u].second <= from_len[v].second + 1 ||
                from_len[v].second + 1 > 3 * n + 2)
                continue;
            from_len[u] = {v, from_len[v].second + 1};
            q.push_back(u);
        }
    }
    vector<int> ans;
    if (from_len[(n - 1) * 2].first != -1) ans.push_back((n - 1) * 2);
    else ans.push_back((n - 1) * 2 + 1);
    while (from_len[ans.back()].first != -2) ans.push_back(from_len[ans.back()].first);
    reverse(ans.begin(), ans.end());
    if (ans.size() % 2 == 0) cout << "1 ";
    else cout << "0 ";
    cout << ans.size() << "\n";
    cout << ans[0] / 2 + 1 << " ";
    for (int i = 1; i < ans.size(); ++i) {
        if (i % 2) cout << "+ ";
        else cout << "- ";
        cout << ans[i] / 2 + 1 << " ";
    }
    cout << "\n";
    return 0;
}
