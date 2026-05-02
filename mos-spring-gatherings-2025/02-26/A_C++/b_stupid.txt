
#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 1e6 + 10;

int n;
char s[maxn];

vector<char> hall;
vector<int> turns;

bool rec_solve(int sp, int cp, bool dir) {
    if (sp == n || cp < 0) return sp == n && cp == -1 && !dir;
//    if (cp > n - sp) return false;
    if (cp < hall.size()) {
        if (dir) {
            if (s[sp] != hall[cp]) return false;
            if (rec_solve(sp + 1, cp + 1, dir)) return true;
            turns.push_back(cp + 1);
            if (rec_solve(sp + 1, cp, !dir)) return true;
            turns.pop_back();
        } else {
            if (s[sp] == hall[cp]) return false;
            if (rec_solve(sp + 1, cp - 1, dir)) return true;
            turns.push_back(cp);
            if (rec_solve(sp + 1, cp, !dir)) return true;
            turns.pop_back();
        }
    } else {
        if (!dir) return false;
        hall.push_back(s[sp]);
        if (rec_solve(sp + 1, cp + 1, dir)) return true;
        turns.push_back(cp + 1);
        if (rec_solve(sp + 1, cp, !dir)) return true;
        turns.pop_back();
        hall.pop_back();
    }
    return false;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> s[i];
    hall.clear(), turns.clear();
    if ((n & 1) || (!rec_solve(0, 0, true))) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    cout << hall.size() << "\n";
    for (auto c: hall) cout << c;
    cout << "\n";
    cout << turns.size() << "\n";
    for (auto t: turns) cout << t << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t = 1;
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    cin >> t;
    while (t--) solve();
    return 0;
}
