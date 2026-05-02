#include <iostream>
#include <vector>

using namespace std;

void stupid_solve() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<string> ss(n);
    for (auto &cs: ss) cin >> cs;
    vector<vector<int> > ans(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j + ss[i].size() <= s.size(); ++j) {
            if (s.substr(j, ss[i].size()) == ss[i]) ans[i].push_back(j);
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i].size() << " ";
        for (auto v: ans[i]) cout << v + 1 << " ";
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    stupid_solve();
    return 0;
}
