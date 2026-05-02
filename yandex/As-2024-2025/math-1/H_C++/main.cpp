#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 1e8, max_primes_cnt = 6000000;

int mind[maxn + 1], mindp[maxn + 1];
vector<int> primes;
int n;

void erat_init() {
    primes.reserve(max_primes_cnt);
    for (int i = 2; i <= n; ++i) {
        if (!mind[i]) {
            mind[i] = i;
            primes.push_back(i);
            mindp[i] = 1;
        }
        for (auto p: primes) {
            if (p > i || 1ll * i * p > n) break;
            mind[p * i] = p;
            mindp[p * i] = 1;
        }
        if (1ll * i * mind[i] <= n) mindp[i * mind[i]] = mindp[i] * mind[i];
    }
    mind[1] = 1;
    long long cs = 1;
    for (int i = 2, j = 2; i <= n; ++i, ++j) {
        cs += mind[i] = mind[i / (mindp[i] * mind[i])] * (mindp[i] * (mind[i] - 1));
        if (j == 100 || i == n) cout << cs << " ", cs = 0, j = 0;
    }
}

void solve() {
    cin >> n;
    if (n == 1) {
        cout << "1\n";
        return;
    }
    erat_init();
    // for (int i = 1, j = 1; i <= n; ++i, ++j) {
    //     cs += mind[i];
    // }
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
