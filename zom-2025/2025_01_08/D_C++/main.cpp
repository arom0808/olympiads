#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int maxn = 1e5;

struct Str {
    char from, to;

    bool operator<(const Str &rhs) const {
        if (from != rhs.from) return from < rhs.from;
        return to < rhs.to;
    }
};

int n;
string strs[maxn];
// char dp[17][1 << 17];

// char get_dp_val(int i, int mask) {
//     if (dp[i][mask]) return dp[i][mask];
//     if (mask & (1 << i)) return dp[i][mask] = 1;
//     dp[i][mask] = 1;
//     bool edge_ex = false;
//     for (int j = 0; j < n; ++j) {
//         if (j == i || (mask & (1 << j)) || strs[i].to != strs[j].from) continue;
//         edge_ex = true;
//         if (get_dp_val(j, mask | (1 << i)) == 1) {
//             dp[i][mask] = 2;
//             break;
//         }
//     }
//     if (!edge_ex) dp[i][mask] = 2;
//     return dp[i][mask];
// }

vector<int> cids;

bool rec_sol(int v) {
    cids.push_back(v);
    bool ans = false, edge_ex = false;
    for (int i = 0; i < n; ++i) {
        if (strs[v].back() == strs[i].front() && find(cids.begin(), cids.end(), i) == cids.end()) {
            edge_ex = true;
            if (!rec_sol(i)) ans = true;
        }
    }
    cids.pop_back();
    if (!edge_ex) ans = true;
    return ans;
}

void solve() {
    cin >> n;
    string temp_str;
    for (int i = 0; i < n; ++i) {
        cin >> strs[i];
        // strs[i].from = temp_str.front(), strs[i].to = temp_str.back();
    }
    // sort(strs, strs + n);
    // bool art = false;
    // do {
    // int last_i = 0;
    // while (last_i + 1 < n && strs[last_i].to == strs[last_i + 1].from) ++last_i;
    // art = art || !(last_i & 1);
    // } while (next_permutation(strs, strs + n));
    bool art = false;
    for (int i = 0; i < n; ++i) if (rec_sol(i)) art = true;
    if (art) cout << "Artem\n";
    else cout << "Boris\n";
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
