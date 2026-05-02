#include <iostream>
#include <vector>

using namespace std;

// constexpr int maxn = 10100, N = 10020;

// int phi[maxn];
// vector<int> pr;
// int mind[maxn];
// bool dp[maxn];
//
// vector<pair<int, int> > temp;
//
// void er_phi_init() {
//     for (int i = 2; i < N; ++i) {
//         if (!mind[i]) pr.push_back(mind[i] = i);
//         for (auto v: pr) {
//             if (v > mind[i] || v * i >= N) break;
//             mind[v * i] = v;
//         }
//     }
//     phi[1] = 1;
//     for (int i = 2; i < N; ++i) {
//         if (mind[i] == i) {
//             phi[i] = i - 1;
//             continue;
//         }
//         temp.clear();
//         for (int val = i; val != 1; val /= mind[val]) {
//             if (temp.empty() || temp.back().first != mind[val]) temp.emplace_back(mind[val], mind[val]);
//             else temp.back().second *= mind[val];
//         }
//         phi[i] = 1;
//         for (auto [v,mv]: temp) phi[i] *= mv - mv / v;
//     }
// }

void solve() {
    int n;
    cin>>n;
    if(n<4) 
    // er_phi_init();
    // phi[1] = 0;
    // dp[0] = false;
    // for (int i = 1; i < N; ++i) {
    //     if (!dp[i - 1] || !dp[phi[i]]) dp[i] = true;
    // }
    // for (int i = 1; i < N; ++i) cout << dp[i] << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
