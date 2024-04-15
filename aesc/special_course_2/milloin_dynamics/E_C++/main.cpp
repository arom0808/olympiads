#include <iostream>
#include <set>
#include <vector>

using namespace std;

const int32_t minf = -1e9;

struct Node {
    int32_t cost = minf;
    set<int32_t> childs;
};

struct DpEl {
    int32_t max_with = minf, max_without = minf;
};

DpEl get_dp(const vector<Node> &nodes, vector<DpEl> &dp, uint32_t id) {
    if (dp[id].max_with != minf) return dp[id];
    int32_t mw = 0, mo = 0;
    for (auto child: nodes[id].childs) {
        auto cr = get_dp(nodes, dp, child);
        mw += cr.max_without;
        mo += cr.max_with;
    }
    return dp[id] = {max(mw + nodes[id].cost, mo), mo};
}

int main() {
    int32_t n;
    cin >> n;
    vector<Node> nodes(n);
    int32_t root;
    for (int32_t i = 0, p; i < n; ++i) {
        cin >> p >> nodes[i].cost;
        if (p > 0) nodes[p - 1].childs.insert(i);
        if (p == 0) root = i;
    }
    vector<DpEl> dp(n);
    auto rp = get_dp(nodes, dp, root);
    cout << max(rp.max_with, rp.max_without);
    return 0;
}
