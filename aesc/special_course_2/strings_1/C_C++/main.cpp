#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string str;
    cin >> str;
    vector<int32_t> z(str.size(), 0);
    z[0] = str.size();
    for (int32_t i = 1, l = 0, r = 0; i < str.size(); ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < z.size() && str[z[i]] == str[i + z[i]]) ++z[i];
        if (i + z[i] > r) l = i, r = i + z[i] - 1;
    }
    for (int32_t l = 1; l <= str.size(); ++l) {
        if (str.size() % l != 0) continue;
        bool ok = true;
        for (int32_t cp = 0; cp < str.size(); cp += l) {
            if (z[cp] < l) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << str.size() / l;
            break;
        }
    }
    return 0;
}