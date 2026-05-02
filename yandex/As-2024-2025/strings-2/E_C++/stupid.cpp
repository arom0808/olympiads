#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;
string s;

void solve() {
    std::getline(cin, s);
     vector<string> ss;
     for (int i = 0; i < s.size(); ++i) for (int j = 1; i + j <= s.size(); ++j) ss.push_back(s.substr(i, j));
     sort(ss.begin(), ss.end());
     ss.erase(unique(ss.begin(), ss.end()), ss.end());
     int k;
     cin>>k,--k;
     if(k  < ss.size()) cout<<ss[k]<<"\n";
     else cout<<ss.back()<<"\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r", stdin);
#endif
    solve();
    return 0;
}
