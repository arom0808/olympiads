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
    for (auto zv: z) cout << zv << " ";
    return 0;
}
