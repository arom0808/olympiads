#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string str, find_str;
    std::getline(cin, str), std::getline(cin, find_str);
    str = find_str + '\n' + str;
    vector<int32_t> z(str.size(), 0);
    int32_t left = 0, right = 0;
    bool found = false;
    for (int32_t i = 1; i < str.size(); ++i) {
        if (i <= right) z[i] = min(right - i + 1, z[i - left]);
        while (i + z[i] < str.size() && str[z[i]] == str[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > right) left = i, right = i + z[i] - 1;
        if (i > find_str.size() && z[i] == find_str.size()) {
            cout << i - find_str.size() << ' ';
            found = true;
        }
    }
    if (!found) cout << 0;
    cout << '\n';
    return 0;
}
