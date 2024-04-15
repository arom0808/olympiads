#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool dfs(const vector<set<int32_t>> &g, vector<int32_t> &rm, vector<int32_t> &used, int32_t timer, int32_t v) {
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

struct Order {
    int32_t time = 0, x = 0, y = 0;
};

inline int32_t to_digit(char c) { return c - '0'; }

int main() {
    int32_t m;
    cin >> m;
    vector<Order> orders(m);
    vector<set<int32_t>> g(m);
    string temp_str;
    for (int32_t i = 0, st, ft, sx, sy, fx, fy; i < m; ++i) {
        cin >> temp_str >> sx >> sy >> fx >> fy;
        st = (to_digit(temp_str[0]) * 10 + to_digit(temp_str[1])) * 60 + to_digit(temp_str[3]) * 10 +
             to_digit(temp_str[4]);
        ft = st + std::abs(sx - fx) + std::abs(sy - fy);
        for (int32_t j = 0; j < i; ++j)
            if (orders[j].time + std::abs(sx - orders[j].x) + std::abs(sy - orders[j].y) < st)
                g[j].insert(i);
        orders[i] = {ft, fx, fy};
    }
    vector<int32_t> rm(m, -1), used(m, -1);
    int32_t timer = 0, ans = 0;
    for (int32_t v = 0; v < m; ++v) {
        if (dfs(g, rm, used, timer, v)) {
            ++ans;
            ++timer;
        }
    }
    cout << m - ans;
    return 0;
}
