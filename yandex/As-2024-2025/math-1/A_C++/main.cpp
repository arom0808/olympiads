#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>
#include <vector>
#include <deque>

using namespace std;
using ll = long long;

namespace Erat {
    constexpr int N = 320000;
    int mind[N + 1];
    vector<int> primes;

    void init() {
        for (int i = 2; i <= N; ++i) {
            if (!mind[i]) {
                primes.push_back(i);
                mind[i] = i;
            }
            for (auto p: primes) {
                if (p > mind[i] || 1ll * p * i > N) break;
                mind[p * i] = p;
            }
        }
    }
}

ll tpws[12] =
        {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000ll, 100000000000ll};
ll min_primes[4] = {2, 3, 5, 7};
vector<ll> ans_nums;

bool check_prime(ll val) {
    for (auto i: Erat::primes) {
        if (1ll * i * i > val) break;
        if (val % i == 0) return false;
    }
    return true;
}

void solve() {
    Erat::init();
    ll a, b;
    cin >> a >> b;
    deque<pair<ll, int> > d;
    for (auto val: min_primes) if (val <= b) d.emplace_back(val, 1);
    while (!d.empty()) {
        auto [val,dcnt] = d.front();
        d.pop_front();
        if (val >= a) ans_nums.push_back(val);
        for (ll i = 1; i < 10; ++i) {
            ll new_val = val + tpws[dcnt] * i;
            if (new_val <= b && check_prime(new_val)) d.emplace_back(new_val, dcnt + 1);
        }
    }
    cout << ans_nums.size() << "\n";
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
