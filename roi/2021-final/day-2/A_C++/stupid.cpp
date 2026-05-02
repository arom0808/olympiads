#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

constexpr int maxn = 3e5 + 1;
constexpr ll inf = 2e18;

ll vals[26];
string s;

pair<ll, vector<int> > rec_sol(int pos, int now_max) {
    if (pos == s.size()) return {0, vector<int>()};
    if (s[pos] != '?') {
        auto cv = rec_sol(pos + 1, std::max(now_max, s[pos] - 'A'));
        if (now_max > s[pos] - 'A') cv.first -= vals[s[pos] - 'A'];
        else cv.first += vals[s[pos] - 'A'];
        return cv;
    }
    pair<ll, vector<int> > ans{-inf, vector<int>()};
    for (int i = 0; i < 26; ++i) {
        s[pos] = i + 'A';
        auto cv = rec_sol(pos + 1, std::max(now_max, s[pos] - 'A'));
        if (now_max > s[pos] - 'A') cv.first -= vals[s[pos] - 'A'];
        else cv.first += vals[s[pos] - 'A'];
        cv.second.push_back(-i);
        ans = std::max(ans, cv);
    }
    s[pos] = '?';
    return ans;
}

void solve_test() {
    cin >> s;
    reverse(s.begin(), s.end());
    auto [ans, vv] = rec_sol(0, 0);
    cout << ans << "\n";
    for (auto &c: s) {
        if (c == '?') {
            c = -vv.back() + 'A';
            vv.pop_back();
        }
    }
    reverse(s.begin(), s.end());
    cout << s << "\n";
}

void solve() {
    for (ll i = 0, v = 1; i < 26; i += 2, v *= 10) {
        vals[i] = v;
        vals[i + 1] = v * 5;
    }
    int t;
    cin >> t;
    while (t--) solve_test();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt","r",stdin);
#endif
    solve();
    return 0;
}
