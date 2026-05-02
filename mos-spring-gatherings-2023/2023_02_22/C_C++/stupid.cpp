#include <iostream>

using namespace std;

constexpr int maxn = 1e5;

bool check_dig(int num, int dig) {
    for (; num; num /= 10) if (num % 10 == dig) return true;
    return false;
}


int n;
int digs[maxn];

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> digs[i];
    for (int sv = 1; sv <= 1000; ++sv) {
        bool ok = true;
        for (int i = 0; i < n && ok; ++i) ok = check_dig(i + sv, digs[i]);
        if (ok) {
            cout << sv << "\n";
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    solve();
    return 0;
}