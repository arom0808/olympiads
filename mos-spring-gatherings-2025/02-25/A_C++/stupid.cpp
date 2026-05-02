#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

map<int, bool> cache;
constexpr int maxn = 310;
int n, m;
vector<int> ans;
bool arr[maxn];
vector<int> ricars;

bool req(int x) {
    auto it = cache.find(x);
    if (it != cache.end()) return it->second;
    char res;
        res = arr[x ] ? '>' : '<';
        // cout << "? " << x - 1 << "\n";
        // cout.flush();
        // cin >> res;
    if (res == '-') exit(0);
    cache.emplace(x, res == '>');
    return res == '>';
}

void solve() {
    for (int i = 0; i < n; ++i) arr[i] = req(i);
    vector<int> ans;
    int i = 0;
    while (!arr[i]) ++i;
    ans.push_back(i++);
    for (; i + 1 < n; ++i) {
        if (!arr[i] && arr[i + 1]) {
            if ((i - ans.back()) & 1) ans.push_back(i);
            else ans.push_back(i + 1);
        }
    }
    if (!arr[n - 1]) ans.push_back(n - 1);
    cout << "! ";
    for (auto v: ans) cout << v << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
// #ifdef LOCAL
//     // freopen("input.txt", "r",stdin);
//     // freopen("output.txt", "w",stdout);
// #endif
// #ifdef TEST
// #endif
    freopen("input.txt", "r",stdin);
    cin >> n >> m;
    ricars.resize(m);
    for (auto &v: ricars) cin >> v;
    sort(ricars.begin(), ricars.end());
    for (int i = 0; i < n; ++i) {
        int dl, dr;
        auto it1 = lower_bound(ricars.begin(), ricars.end(), i);
        if (it1 == ricars.begin()) dl = 1e9;
        else dl = i - *prev(it1);
        auto it2 = upper_bound(ricars.begin(), ricars.end(), i);
        if (it2 == ricars.end()) dr = 1e9;
        else dr = (*it2) - i;
        bool res = dr < dl;
        if (!binary_search(ricars.begin(), ricars.end(), i)) res = !res;
        arr[i] = res;
    }
    solve();
    return 0;
}
