#include <iostream>

using namespace std;

constexpr int maxp = 1000;

bool used[maxp + 1];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, p;
    string temp_str;
    cin >> n >> p;
    for (int i = 0; i < n; ++i) {
        cin >> temp_str;
        int cs = 0;
        for (auto c: temp_str) {
            if (c == '-') continue;
            if (c >= '0' && c <= '9') cs += (c - '0');
            else cs += (c - 'A') + 10;
        }
        used[cs % p] = true;
    }
    for (int cs = 0; cs < p; ++cs) {
        if (used[cs] || cs > 875) continue;
        string ans(25, '0');
        for (int cp = 0; cs; ++cp) {
            int cd = std::min(cs, 35);
            cs -= std::min(35, cs);
            if (cd < 10) ans[cp] = '0' + cd;
            else ans[cp] = 'A' + (cd - 10);
        }
        for (int i = 0; i < ans.size(); ++i) {
            if (i && i % 5 == 0) cout << "-";
            cout << ans[i];
        }
        cout << "\n";
        return 0;
    }
    cout << "Impossible\n";
    return 0;
}
