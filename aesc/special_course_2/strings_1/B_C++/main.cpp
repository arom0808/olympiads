#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string str;
    cin >> str;
    vector<int32_t> pr(str.size(), 0);
    for (int32_t i = 1; i < str.size(); ++i) {
        int32_t j = pr[i - 1];
        while (j > 0 && str[i] != str[j]) j = pr[j - 1];
        pr[i] = j + (str[i] == str[j]);
    }
    for (auto v: pr) cout << v << " ";
    return 0;
}
