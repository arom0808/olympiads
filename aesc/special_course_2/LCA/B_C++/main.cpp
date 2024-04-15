#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

void
build_tree(const vector<list<int32_t>> &rg, vector<list<int32_t>> &rvs, vector<list<int32_t>> &rts, vector<int32_t> &hs,
           vector<int32_t> &cts, int32_t v, int32_t p, int32_t h, int32_t &mh, int32_t &t) {
    hs[v] = h;
    cts[v] = ++t;
    rvs[h].push_back(v);
    rts[h].push_back(cts[v]);
    if (h > mh) mh = h;
    for (auto u: rg[v]) if (u != p) build_tree(rg, rvs, rts, hs, cts, u, v, h + 1, mh, t);
};

int main() {
    int32_t n;
    cin >> n;
    vector<list<int32_t>> rg(n);
    for (int32_t i = 1, v, u; i < n; ++i) {
        cin >> v >> u;
        rg[v - 1].push_back(u - 1);
        rg[u - 1].push_back(v - 1);
    }
    vector<list<int32_t>> rvs(n), rts(n);
    vector<int32_t> hs(n), cts(n);
    int32_t mh = 0, t = 0;
    build_tree(rg, rvs, rts, hs, cts, 0, -1, 0, mh, t);
    vector<vector<int32_t>> vs(mh + 1), ts(mh + 1);
    for (int32_t i = 0; i <= mh; ++i) {
        vs[i].resize(rvs[i].size());
        ts[i].resize(rts[i].size());
        copy(rvs[i].begin(), rvs[i].end(), vs[i].begin());
        copy(rts[i].begin(), rts[i].end(), ts[i].begin());
    }
    int32_t m;
    cin >> m;
    for (int32_t i = 0, v, k; i < m; ++i) {
        cin >> v >> k;
        --v;
        if (k >= hs[v])
            cout << "1\n";
        else
            cout << vs[hs[v] - k][distance(ts[hs[v] - k].begin(),
                                           upper_bound(ts[hs[v] - k].begin(), ts[hs[v] - k].end(), cts[v])) - 1] + 1
                 << "\n";
    }
    return 0;
}
