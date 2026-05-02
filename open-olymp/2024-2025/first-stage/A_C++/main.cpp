#include <iostream>
#include <vector>

using namespace std;

int n, m;
string expons;
vector<int> let_poss[26];

bool can_get(const string &s, int md) {
    int now_start = 0;
    for (auto c: s) {
        auto &cur_lp = let_poss[c - 'a'];
        int next_pos_id = lower_bound(cur_lp.begin(), cur_lp.end(), now_start) - cur_lp.begin();
        if (next_pos_id == cur_lp.size()) return false;
        now_start = cur_lp[next_pos_id] + md;
    }
    return true;
}

int get_ans(const string &s) {
    int l = 0, r = n;
    while (r - l != 1) {
        int mid = (l + r) / 2;
        if (can_get(s, mid)) l = mid;
        else r = mid;
    }
    if (!l) return -1;
    return l;
}

void solve() {
    cin >> n >> m;
    cin >> expons;
    for (int i = 0; i < n; ++i) let_poss[expons[i] - 'a'].push_back(i);
    string s;
    for (int i = 0; i < m; ++i) {
        cin >> s;
        cout << get_ans(s) << "\n";
    }
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
