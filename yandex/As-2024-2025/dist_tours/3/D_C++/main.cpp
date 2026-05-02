#include <iostream>
#include <deque>

using namespace std;
string temp_s;

int to_str(int val, string &s, int pos) {
    temp_s.clear();
    int sz = 0;
    for (; val; ++sz, val /= 10) temp_s.push_back('0' + val % 10);
    for (int i = 0; i < sz; ++i) s[pos + i] = temp_s[sz - i - 1];
    return sz;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n;
    cin >> n;
    string regexp;
    cin >> regexp;
    // int next_num = 1;
    // deque<pair<int, int> > start_poses;
    // int gsp = 0;
    // for (; ; ++gsp) {
    //
    // }
    int maxnum = 10;
    for (int i = 1; i <= n; ++i) maxnum *= 10;
    int slen = 9, nines = 9;
    for (int i = 2; i <= n + 1; ++i) nines = nines * 10 + 9, slen += nines * i;
    string s(slen, '0');
    for (int num = 1, pos = 0; num < maxnum; ++num) {
        pos += to_str(num, s, pos);
    }
    for (int i = 0; i + n < slen; ++i) {
        bool ok = true;
        for (int j = 0; j < n; ++j) {
            if (regexp[j] != '?' && regexp[j] != s[i + j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << i + 1 << " " << i + n << "\n";
            return 0;
        }
    }
    cout << "0 0";
    return 0;
}
