#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

constexpr int maxn = 3e5;

struct Task {
    int l, r, id;

    bool operator<(const Task &t) const {
        return l < t.l;
    }
};

Task tasks[maxn];
vector<int> ans[maxn];
int n, m;

struct SCmp {
    bool operator()(const int t1, const int t2) const {
        if (tasks[t1].r != tasks[t2].r) return tasks[t1].r < tasks[t2].r;
        return tasks[t1].id < tasks[t2].id;
    }
};

bool check_mcc(int max_con_cnt) {
    set<int, SCmp> cts;
    for (int day = 0, i = 0; day < m; ++day) {
        for (; i < n && tasks[i].l <= day; ++i)
            cts.insert(i);
        ans[day].clear();
        for (int j = 0; j < max_con_cnt && !cts.empty(); ++j) {
            ans[day].push_back(tasks[*cts.begin()].id);
            cts.erase(cts.begin());
        }
        if (!cts.empty() && tasks[*cts.begin()].r <= day + 1) return false;
    }
    return true;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> tasks[i].l >> tasks[i].r, --tasks[i].l, tasks[i].id = i;
    sort(begin(tasks), next(begin(tasks), n));
    int l = 0, r = n;
    while (r - l != 1) {
        int mid = (l + r) / 2;
        if (!check_mcc(mid)) l = mid;
        else r = mid;
    }
    check_mcc(r);
    cout << r << "\n";
    for (int i = 0; i < m; ++i) {
        cout << ans[i].size() << " ";
        for (auto el: ans[i]) cout << el + 1 << " ";
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    solve();
#endif
    return 0;
}
