#include <iostream>
#include <random>
#include <set>

using namespace std;
mt19937 rng(2355235);

void solve_ask() {
    int n;
    cin >> n;
    uniform_int_distribution<int> rdst(1, n);
    set<int> start_vs;
    start_vs.insert(n);
    while (start_vs.size() < n && start_vs.size() < 1000) start_vs.insert(rdst(rng));
    cout << start_vs.size() << " 1000\n";
    for (auto v: start_vs) cout << v << " ";
}

constexpr int maxn = 5e4 + 2;
int ng[maxn], nf[maxn];

void solve_answer() {
    int k, l;
    cin >> k >> l;
    int v, pv;
    for (int i = 0; i < maxn; ++i) ng[i] = -1;
    for (int i = 0; i < maxn; ++i) nf[i] = -1;
    int n = 0;
    for (int i = 0; i < k; ++i) {
        cin >> v;
        if (v > n) n = v;
        for (int j = 0; j < l - 1; ++j) {
            pv = v;
            cin >> v;
            if (v > n) n = v;
            ng[pv] = v;
            nf[v] = pv;
        }
    }
    int next_not = -1;
    for (int i = 1; i <= n; ++i) {
        if (ng[i] == -1) {
            next_not = i;
            break;
        }
    }
    int from_not = -1;
    for (int i = 1; i <= n; ++i) {
        if (nf[i] == -1) {
            from_not = i;
            break;
        }
    }
    if (next_not >= 0) {
        ng[next_not] = from_not;
        nf[from_not] = next_not;
    }
    v = 1;
    while (v != -1) {
        cout << v << " ";
        v = ng[v];
        if (v == 1) break;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    string s;
    cin >> s;
    if (s == "ask") solve_ask();
    else solve_answer();
    return 0;
}
