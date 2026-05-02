#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

constexpr int maxn = 1e6;
constexpr int max_primes_cnt = 80000, max_prime_pow = 20;

int prime_conds[max_primes_cnt][max_prime_pow];

namespace Erat {
    int mind[maxn + 1];
    vector<int> primes;
    int pos_by_prime[maxn + 1];

    void init() {
        for (int i = 2; i <= maxn; ++i) {
            if (!mind[i]) {
                mind[i] = i;
                pos_by_prime[i] = primes.size();
                primes.push_back(i);
            }
            for (auto p: primes) {
                if (p > i || 1ll * p * i > maxn) break;
                mind[p * i] = p;
            }
        }
    }
}

int comp_sz[maxn], head[maxn], dth[maxn], a[maxn], b[maxn], must_shift[maxn];
int n;

void solve() {
    Erat::init();
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i], --a[i];
    for (int i = 0; i < n; ++i) cin >> b[i], --b[i];
    for (int i = 0; i < n; ++i) head[i] = -1;
    for (int start = 0; start < n; ++start) {
        if (head[start] != -1) continue;
        int csz = 0;
        for (int v = start; !csz || start != v; ++csz) {
            head[v] = start, dth[v] = csz;
            v = a[v];
        }
        comp_sz[start] = csz;
    }
    for (int i = 0; i < n; ++i) must_shift[i] = -1;
    for (int v = 0; v < n; ++v) {
        if (head[v] != head[b[v]]) {
            cout << "No\n";
            return;
        }
        int cd = (comp_sz[head[v]] - dth[v] + dth[b[v]]) % (comp_sz[head[v]]);
        if (must_shift[head[v]] != -1 && must_shift[head[v]] != cd) {
            cout << "No\n";
            return;
        }
        must_shift[head[v]] = cd;
    }
    for (int i = 0; i < Erat::primes.size(); ++i) for (int j = 0; j < max_prime_pow; ++j) prime_conds[i][j] = -1;
    for (int v = 0; v < n; ++v) {
        if (head[v] != v) continue;
        int val = must_shift[v], cmod = comp_sz[v];
        int cdiv = 0, ccnt = 0, cdivp = 0;
        while (cmod > 1) {
            if (Erat::mind[cmod] == cdiv) ++ccnt, cdivp *= cdiv;
            else cdiv = Erat::mind[cmod], ccnt = 1, cdivp = cdiv;
            cmod /= cdiv;
            if (cmod == 1 || Erat::mind[cmod] != cdiv) {
                int cv = val % cdivp;
                int cpos = Erat::pos_by_prime[cdiv];
                if (prime_conds[cpos][ccnt] != -1 && prime_conds[cpos][ccnt] != cv) {
                    cout << "No\n";
                    return;
                }
                prime_conds[cpos][ccnt] = cv;
            }
        }
    }
    for (int i = 0; i < Erat::primes.size(); ++i) {
        int max_p = 0;
        for (int j = max_prime_pow - 1; j; --j) {
            if (prime_conds[i][j] == -1) continue;
            max_p = j;
            break;
        }
        int cv = 1;
        for (int j = 0; j < max_p; ++j) cv *= Erat::primes[i];
        int cmv = -1;
        for (int j = max_p; j; --j, cv /= Erat::primes[i]) {
            if (prime_conds[i][j] == -1) continue;
            if (cmv == -1) cmv = prime_conds[i][j] % cv;
            else if (cmv % cv != prime_conds[i][j] % cv) {
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
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
