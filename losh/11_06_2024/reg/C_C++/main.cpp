#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int32_t maxn = 4e5;
int32_t n, m, k;

struct Action {
    int32_t time, type, val;
};

int32_t sol_for_first(const vector<int32_t> &line) {
    vector<vector<int32_t>> switchers_on_balloons(line.size());
    vector<int32_t> first_left_balloon(line.size(), -1), first_right_balloon(line.size(), -1);
    for (int32_t i = 0, lb = -1; i < n; ++i) {
        if (line[i] == 1) lb = i;
        else {
            first_left_balloon[i] = lb;
            if (lb != -1 && line[i] == 2) switchers_on_balloons[lb].push_back(i);
        }
    }
    for (int32_t i = n - 1, lb = -1; i >= 0; --i) {
        if (line[i] == 1) lb = i;
        else first_right_balloon[i] = lb;
    }
    vector<Action> acts;
    for (int32_t i = 0; i < n; ++i)
        if (line[i] == 2 && first_right_balloon[i] != -1)
            acts.emplace_back(first_right_balloon[i] - i, 0, i);
    for (int32_t i = 0, f_c = 0; i < n; ++i) {
        if (line[i] == 1) acts.emplace_back(f_c, 1, i);
        else ++f_c;
    }
    sort(acts.begin(), acts.end(), [](const Action &a, const Action &b) {
        if (a.time != b.time) return a.time < b.time;
        if (a.type != b.type) return a.type < b.type;
        return a.val < b.val;
    });
    int32_t min_x = 0;
    int32_t best_res = -1;
    multiset<int32_t> set_change, set_const;
    vector<pair<bool, int32_t>> what_set(n, pair<bool, int32_t>{false, -1});
    for (int32_t i = 0; i < n; ++i) {
        if (line[i] != 2) continue;
        if (first_left_balloon[i] != -1)
            set_change.insert(i - first_left_balloon[i]),
                    what_set[i] = {false, i - first_left_balloon[i]};
        else min_x = max(min_x, first_right_balloon[i] - i);
    }
    for (int32_t x = 0, aid = 0; x < n; ++x) {
        for (; aid < acts.size() && acts[aid].time <= x; ++aid) {
            auto [time, type, val] = acts[aid];
            if (type == 0) {
                if (what_set[val].second != -1) {
                    if (!what_set[val].first) set_change.erase(set_change.find(what_set[val].second));
                    else set_const.erase(set_const.find(what_set[val].second));
                    what_set[val].second = -1;
                }
            } else {
                int32_t pos = val - x;
                for (auto sw: switchers_on_balloons[val]) {
                    if (what_set[sw].second != -1) {
                        set_change.erase(set_change.find(what_set[sw].second));
                        set_const.insert(sw - pos);
                        what_set[sw] = {true, sw - pos};
                    }
                }
            }
        }
        if (x >= min_x) {
            int32_t res = x + max(set_change.empty() ? 0 : ((*set_change.rbegin()) + x),
                                  set_const.empty() ? 0 : (*set_const.rbegin()));
            if (best_res == -1 || res < best_res) best_res = res;
        }
    }
    return best_res;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    vector<int32_t> line(n);
    for (int32_t i = 0, pos; i < m; ++i) cin >> pos, --pos, line[pos] = 1;
    for (int32_t i = 0, pos; i < k; ++i) cin >> pos, --pos, line[pos] = (line[pos] == 0 ? 2 : 1);
    int32_t r1 = sol_for_first(line);
    reverse(line.begin(), line.end());
    int32_t r2 = sol_for_first(line);
    cout << min(r1, r2) << "\n";
    return 0;
}
