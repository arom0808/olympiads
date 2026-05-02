#include <iostream>
#include <vector>

using namespace std;

constexpr int maxN = 1.5e7;
constexpr int max_primes_cnt = 1e6, max_prime_p = 24;
constexpr int maxn = 3e5;

int mind[maxN + 1], pos_by_prime[maxN + 1];
vector<int> primes;
int ppcnts[max_primes_cnt][max_prime_p];

void erat_init() {
    for (int i = 2; i <= maxN; ++i) {
        if (!mind[i]) {
            mind[i] = i;
            pos_by_prime[i] = primes.size();
            primes.push_back(i);
        }
        for (auto p: primes) {
            if (p > i || 1ll * i * p > maxN) break;
            mind[i * p] = p;
        }
    }
}

void solve() {
    erat_init();
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        int cdiv = 0, cdcnt = 0;
        while (val > 1) {
            if (mind[val] == cdiv) ++cdcnt;
            else cdiv = mind[val], cdcnt = 1;
            val /= cdiv;
            ++ppcnts[pos_by_prime[cdiv]][cdcnt];
        }
    }
    for (int i = 0; i < primes.size(); ++i) ppcnts[i][0] = n;
    int best_res = n;
    for (int pid = 0; pid < primes.size(); ++pid) {
        for (int i = 0; i + 1 < max_prime_p; ++i) {
            if (ppcnts[pid][i] > ppcnts[pid][i + 1]) {
                best_res = std::min(best_res, ppcnts[pid][i] - ppcnts[pid][i + 1]);
                break;
            }
        }
    }
    if (best_res == n) cout << "-1\n";
    else cout << best_res << "\n";
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
