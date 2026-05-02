#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

const int32_t maxn = 2e5, sqrtn = 350;

int32_t dir_a[maxn];
pair<int32_t, int32_t> proxy_a[maxn];
pair<int32_t, int32_t> changed[maxn];
int32_t changed_timer = 1;

int main() {
//    freopen("test.txt", "r", stdin);
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, m;
    cin >> n >> m;
    for (int32_t i = 0; i < n; ++i) cin >> dir_a[i], dir_a[i] += i;
    for (int32_t i = 0; i < n; ++i)
        for (proxy_a[i] = {dir_a[i], 1}; proxy_a[i].first < n && dir_a[proxy_a[i].first] - i < sqrtn;)
            proxy_a[i].first = dir_a[proxy_a[i].first], ++proxy_a[i].second;
    int32_t a, b, c;
    vector<int32_t> temp_vec;
    for (int32_t _ = 0; _ < m; ++_) {
        cin >> c >> a, --a;
        if (c == 0) {
            cin >> b;
            dir_a[a] = a + b;
            temp_vec.clear();
            ++changed_timer;
            int32_t ci = a;
            temp_vec.push_back(ci);
            do temp_vec.push_back(ci = dir_a[ci]); while (ci < n && ci - a < sqrtn);
            int32_t tid = temp_vec.size() - 1;
            for (int32_t i = a; i >= 0 && i > a - sqrtn; --i) {
                if (i != a && changed[dir_a[i]].first != changed_timer) continue;
                while (tid > (i == a ? 1 : 0) && temp_vec[tid] - i >= sqrtn) --tid;
                int32_t dist = (i == a ? 0 : (1 + changed[dir_a[i]].second)) + tid;
                proxy_a[i] = {temp_vec[tid], dist};
                changed[i] = {changed_timer, i == a ? 0 : (1 + changed[dir_a[i]].second)};
            }
        } else {
            int32_t mc = 0;
            while (proxy_a[a].first < n) mc += proxy_a[a].second, a = proxy_a[a].first;
            while (dir_a[a] < n) ++mc, a = dir_a[a];
            cout << a + 1 << " " << mc + 1 << "\n";
        }
    }
    return 0;
}
