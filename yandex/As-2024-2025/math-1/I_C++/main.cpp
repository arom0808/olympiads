#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int N = 5800079;
constexpr int maxn = 400000;

int mind[N + 1];
vector<int> primes;
int len_by_n[maxn + 1];
vector<int> poss_by_dig[10];
constexpr int poss_lens[10] = {193103, 372659, 269735, 367442, 266371, 252109, 200904, 300462, 194076, 293623};

void erat_init() {
    primes.reserve(maxn);
    for (int i = 2; i <= N; ++i) {
        if (!mind[i]) {
            mind[i] = i;
            primes.push_back(i);
        }
        for (auto p: primes) {
            if (p > mind[i] || 1ll * i * p > N) break;
            mind[p * i] = p;
        }
    }
    for (int i = 0; i < 10; ++i) poss_by_dig[i].reserve(poss_lens[i]);
    string temp_str;
    temp_str.reserve(10);
    for (int i = 0; i < primes.size(); ++i) {
        temp_str.clear();
        int clen = 0;
        for (int num = primes[i]; num; num /= 10, ++clen) temp_str.push_back(num % 10);
        reverse(temp_str.begin(), temp_str.end());
        for (int j = 0; j < temp_str.size(); ++j) poss_by_dig[temp_str[j]].push_back(len_by_n[i] + j);
        len_by_n[i + 1] = len_by_n[i] + clen;
    }
}

int t_poses[10];

void solve_test(int n, int k) {
    k = len_by_n[n] - k;
    for (int i = 0; i < 10; ++i) t_poses[i] = 0;
    int made = 0, next_pos = 0;
    for (int _ = 0; _ < k; ++_) {
        for (int i = 9; i >= 0; --i) {
            while (t_poses[i] < poss_lens[i] && poss_by_dig[i][t_poses[i]] < next_pos) ++t_poses[i];
            if (t_poses[i] < poss_lens[i] && made + len_by_n[n] - poss_by_dig[i][t_poses[i]] >= k) {
                cout << i;
                ++made;
                next_pos = poss_by_dig[i][t_poses[i]] + 1;
                break;
            }
        }
    }
    cout << "\n";
}

void solve() {
    erat_init();
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        solve_test(n, k);
    }
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
