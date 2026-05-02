#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

constexpr int maxn = 2e5, maxlen = 1e6 + 1, asz = 26;

int n;
string strs[maxn];

namespace Bor {
    int to[maxlen][asz];
    bool term[maxlen];

    int root = 0, nodes_used = 0;
    int d[maxlen];

    int get_new_node() {
        for (int i = 0; i < asz; ++i) to[nodes_used][i] = -1;
        return nodes_used++;
    }

    void init() {
        nodes_used = 0;
        root = get_new_node();
    }

    void add_str(const string &s) {
        int v = root;
        for (auto c: s) {
            if (to[v][c - 'a'] == -1) to[v][c - 'a'] = get_new_node();
            v = to[v][c - 'a'];
        }
        term[v] = true;
    }

    ll get_ans() {

    }
}


void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> strs[i], reverse(strs[i].begin(), strs[i].end());
    sort(strs, strs + n, [](const string &a, const string &b) {
        return a.size() > b.size();
    });
    Bor::init();
    for (int i = 0; i < n; ++i) Bor::add_str(strs[i]);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
