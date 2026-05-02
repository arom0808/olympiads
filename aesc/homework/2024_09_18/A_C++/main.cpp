#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const int64_t maxm = 15;
int64_t n, m;
int64_t coins[maxm];
vector<int64_t> now_seq, best_res;

void rec(int64_t level = 0, int64_t sum = 0) {
    if (level == m) {
        if (sum == n && (best_res.empty() || now_seq.size() < best_res.size())) best_res = now_seq;
        return;
    }
    rec(level + 1, sum);
    now_seq.push_back(coins[level]);
    rec(level + 1, sum + coins[level]);
    now_seq.push_back(coins[level]);
    rec(level + 1, sum + coins[level] * 2);
    now_seq.pop_back();
    now_seq.pop_back();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    for (int64_t i = 0; i < m; ++i) cin >> coins[i];
    if (accumulate(begin(coins), next(begin(coins), m), 0ll) * 2 < n) {
        cout << "-1\n";
        return 0;
    }
    rec();
    if (best_res.empty()) cout << "0\n";
    else {
        cout << best_res.size() << "\n";
        for (auto coin: best_res) cout << coin << " ";
    }
    return 0;
}
