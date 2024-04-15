#include <iostream>
#include <vector>

using namespace std;

const uint32_t inf = 1e9;

uint32_t get_dp(const vector<uint32_t> &cuts, vector<vector<uint32_t>> &dp, uint32_t from, uint32_t to) {
    if (dp[from][to] != inf) return dp[from][to];
    if (from + 1 == to) return dp[from][to] = 0;
    uint32_t mv = inf;
    for (uint32_t i = from + 1, nv; i < to; ++i) {
        nv = get_dp(cuts, dp, from, i) + get_dp(cuts, dp, i, to);
        if (nv < mv) mv = nv;
    }
    return dp[from][to] = mv + cuts[to] - cuts[from];
}

int main() {
    uint32_t l, n;
    cin >> l >> n;
    vector<uint32_t> cuts(n + 2);
    cuts.front() = 0;
    cuts.back() = l;
    for (uint32_t i = 1; i <= n; ++i) cin >> cuts[i];
    vector<vector<uint32_t>> dp(n + 2, vector<uint32_t>(n + 2, inf));
    cout << get_dp(cuts, dp, 0, n + 1);
    return 0;
}
