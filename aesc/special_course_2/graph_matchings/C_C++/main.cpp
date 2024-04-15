#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

bool dfs(const vector<set<int64_t>> &g, vector<int64_t> &rm, vector<int64_t> &used, int64_t timer, int64_t v) {
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

struct Act {
    int64_t time = 0, x = 0, y = 0;

    bool operator<(const Act &other) const { return time < other.time; }
};

inline int64_t to_digit(char c) { return c - '0'; }

inline int64_t square(int64_t num) { return num * num; }

int main() {
    int64_t n, v;
    cin >> n >> v;
    vector<Act> acts(n);
    vector<set<int64_t>> g(n);
    string temp_str;
    for (int64_t i = 0, time, x, y; i < n; ++i) {
        cin >> temp_str >> x >> y;
        time = (to_digit(temp_str[0]) * 10 + to_digit(temp_str[1])) * 60 + to_digit(temp_str[3]) * 10 +
               to_digit(temp_str[4]);
        acts[i] = {time, x, y};
    }
    sort(acts.begin(), acts.end());
    for (int64_t i = 0; i < n; ++i)
        for (int64_t j = 0; j < i; ++j)
            if (3600 * (square(acts[i].x - acts[j].x) + square(acts[i].y - acts[j].y)) <=
                square(v) * square(acts[i].time - acts[j].time))
                g[j].insert(i);
    vector<int64_t> rm(n, -1), used(n, -1);
    int64_t timer = 0, ans = 0;
    for (int64_t i = 0; i < n; ++i) {
        if (dfs(g, rm, used, timer, i)) {
            ++ans;
            ++timer;
        }
    }
    cout << n - ans;
    return 0;
}
