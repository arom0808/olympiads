#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint32_t t;
    cin >> t;
    string temp_str;
    vector<uint32_t> cnts(256, 0);
    for (uint32_t _ = 0, n, m; _ < t; ++_) {
        cin >> n >> m >> temp_str;
        fill(cnts.begin(), cnts.end(), 0);
        for (auto c: temp_str) ++cnts[c];
        uint32_t odd_cnt = 0;
        for (auto c: cnts) if (c % 2 != 0) ++odd_cnt;
        if (odd_cnt > m) cout << "NO\n";
        else cout << "YES\n";
    }
    return 0;
}
