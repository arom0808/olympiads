#include <iostream>

using namespace std;

constexpr int maxn = 5e5, maxlen = 1e6 + 1, asz = 26;

namespace AhoCorasic {
    int par[maxlen], link[maxlen], superlink[maxlen], len[maxlen];
    int to[maxlen][asz], go[maxlen][asz];
}

void solve() {
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    solve();
    return 0;
}
