#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string str;
    cin >> str;
    vector<int32_t> zp(str.size(), 0), suf(str.size(), 0);
    zp[0] = str.size();
    for (int32_t i = 1, l = 0, r = 0; i < str.size(); ++i) {
        if (i <= r) zp[i] = min(r - i + 1, zp[i - l]);
        while (i + zp[i] < zp.size() && str[zp[i]] == str[i + zp[i]]) ++zp[i];
        if (i + zp[i] > r) l = i, r = i + zp[i] - 1;
    }
    reverse(str.begin(), str.end());
    for (int32_t i = 1; i < str.size(); ++i) {
        int32_t j = suf[i - 1];
        while (j > 0 && str[i] != str[j]) j = suf[j - 1];
        suf[i] = j + (str[i] == str[j]);
    }
    reverse(suf.begin(), suf.end());
    reverse(str.begin(), str.end());
    int32_t start = 0, len = 0;
    for (int32_t i = 1; i + 1 < str.size(); ++i) {
        int32_t cr = min(zp[i], suf[i]);
        if (cr > len) start = i, len = cr;
    }
    if (!len) cout << "Just a legend";
    else cout << str.substr(start, len);
    return 0;
}