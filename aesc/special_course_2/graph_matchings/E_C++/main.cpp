#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool dfs(const vector<vector<int32_t>> &g, vector<int32_t> &rm, vector<int32_t> &used, int32_t timer, int32_t v) {
    if (used[v] == timer) return false;
    used[v] = timer;
    for (auto u: g[v]) {
        if (rm[u] == -1) {
            rm[u] = v;
            return true;
        }
    }
    for (auto u: g[v]) {
        if (dfs(g, rm, used, timer, rm[u])) {
            rm[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int32_t n;
    cin >> n;
    vector<pair<int32_t, int32_t>> exams(n);
    vector<int32_t> days;
    days.reserve(n * 2);
    for (auto &[a, b]: exams) {
        cin >> a >> b;
        days.push_back(a);
        days.push_back(b);
    }
    sort(days.begin(), days.end());
    days.erase(unique(days.begin(), days.end()), days.end());
    vector<int32_t> g_sizes(days.size(), 0);
    for (auto &[a, b]: exams) {
        a = distance(days.begin(), lower_bound(days.begin(), days.end(), a));
        b = distance(days.begin(), lower_bound(days.begin(), days.end(), b));
        ++g_sizes[a];
        ++g_sizes[b];
    }
    vector<vector<int32_t>> g(days.size());
    for (int32_t i = 0; i < days.size(); ++i) g[i].reserve(g_sizes[i]);
    for (int32_t i = 0; i < n; ++i) {
        g[exams[i].first].push_back(i);
        g[exams[i].second].push_back(i);
    }
    vector<int32_t> rm(n, -1), used(days.size(), -1);
    int32_t timer = 0, ans = 0;
    for (int32_t v = 0; v < days.size() && ans < n; ++v) {
        if (dfs(g, rm, used, timer, v)) {
            ++ans;
            ++timer;
        }
    }
    if (ans < n) {
        cout << "-1";
        return 0;
    }
    cout << days[*max_element(rm.begin(), rm.end())];
    return 0;
}
