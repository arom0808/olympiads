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
// bool arr[maxn];
// vector<int> ricars;

bool req(int x) {
    auto it = cache.find(x);
    if (it != cache.end()) return it->second;
    char res;
    if (x == 0) res = '<';
    else if (x == n - 1) res = '>';
    else {
        // res = arr[x - 1] ? '>' : '<';
        cout << "? " << x - 1 << "\n";
        cout.flush();
        cin >> res;
    }
    if (res == '-') exit(0);
    cache.emplace(x, res == '>');
    return res == '>';
}

int find_first_right(int l, int r) {
    --l;
    while (r - l != 1) {
        int mid = (l + r) >> 1;
        if (req(mid)) r = mid;
        else l = mid;
    }
    return r;
}

int find_first_left(int l, int r) {
    --l;
    while (r - l != 1) {
        int mid = (l + r) >> 1;
        if (!req(mid)) r = mid;
        else l = mid;
    }
    return r;
}

int find_right_in_suffix(int l, int r) {
    if (req(r)) return r;
    for (int k = 0; r - (1 << k) >= l; ++k) {
        int pos = r - (1 << k);
        if (req(pos)) return pos;
    }
    return -1;
}

int find_right_in_prefix(int l, int r) {
    if (req(r)) return l;
    for (int k = 0; l + (1 << k) <= r; ++k) {
        int pos = l + (1 << k);
        if (req(pos)) return pos;
    }
    return -1;
}

int find_left_in_prefix(int l, int r) {
    if (!req(l)) return l;
    for (int k = 0; l + (1 << k) <= r; ++k) {
        int pos = l + (1 << k);
        if (!req(pos)) return pos;
    }
    return -1;
}

int find_left_in_suffix(int l, int r) {
    if (!req(r)) return r;
    for (int k = 0; r - (1 << k) >= l; ++k) {
        int pos = r - (1 << k);
        if (!req(pos)) return pos;
    }
    return -1;
}

void rec_solve(int l, int r, bool on_suf) {
    if (l >= r) return;
    bool vl = req(l), vr = req(r);
    if (!vl && !vr) {
        int p1;
        if (!on_suf) p1 = find_right_in_prefix(l, r);
        else p1 = find_right_in_suffix(l, r);
        if (p1 == -1) return;
        p1 = find_first_right(l, p1);
        ans.push_back(p1);
        rec_solve(l, p1 - 1, true);
        rec_solve(p1, r, false);
    } else if (!vl && vr) {
        int p1;
        if (!on_suf) p1 = find_left_in_prefix(l, r);
        else p1 = find_left_in_suffix(l, r);
        if (p1 == -1) return;
        ans.push_back(p1);
        rec_solve(l, p1 - 1, true);
        rec_solve(p1, r, false);
    } else if (vl && !vr) {
        int p1 = find_first_left(l, r);
        rec_solve(l, p1 - 1, true);
        rec_solve(p1, r, false);
    } else {
        int p1 = find_left_in_prefix(l, r);
        if (p1 == -1) p1 = find_left_in_suffix(l, r);
        if (p1 == -1) return;
        p1 = find_first_right(p1, r);
        ans.push_back(p1);
        rec_solve(l, p1 - 1, false);
        rec_solve(p1, r, false);
    }
}

void solve() {
    cin >> n >> m;
    n += 2;
    rec_solve(0, n - 1, false);
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    vector<int> rans;
    for (auto v: ans) {
        if (rans.empty()) rans.push_back(v);
        else if ((v - rans.back()) & 1) rans.push_back(v);
        else rans.push_back(v - 1);
    }
    cout << "! ";
    for (auto v: rans) cout << v - 1 << " ";
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
    // freopen("input.txt", "r",stdin);
    // cin >> n >> m;
    // ricars.resize(m);
    // for (auto &v: ricars) cin >> v;
    // sort(ricars.begin(), ricars.end());
    // for (int i = 0; i < n; ++i) {
    //     int dl, dr;
    //     auto it1 = lower_bound(ricars.begin(), ricars.end(), i);
    //     if (it1 == ricars.begin()) dl = 1e9;
    //     else dl = i - *prev(it1);
    //     auto it2 = upper_bound(ricars.begin(), ricars.end(), i);
    //     if (it2 == ricars.end()) dr = 1e9;
    //     else dr = (*it2) - i;
    //     bool res = dr < dl;
    //     if (!binary_search(ricars.begin(), ricars.end(), i)) res = !res;
    //     arr[i] = res;
    // }
    // for (int i = 0; i < n; ++i) cout << (arr[i] ? '>' : '<');
    // cout << "\n";
    solve();
    return 0;
}
