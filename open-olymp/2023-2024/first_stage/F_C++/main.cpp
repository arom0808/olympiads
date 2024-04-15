#include <iostream>
#include <set>
#include <vector>

using namespace std;

bool OneSol() {
    int32_t n;
    cin >> n;
    string temp_str;
    set<int32_t> vs0, vs1;
    for (int32_t i = 0; i < n; ++i) vs0.insert(i);
    vector<int32_t> out_cnt(n, 0), in_cnt(n, 0);
    vector<vector<bool>> checked(n, vector<bool>(n, false));
    int32_t res = -1;
    for (int32_t reqs_made = 0; reqs_made < 2000; ++reqs_made) {
        if (vs0.empty()) break;
        int32_t best_first = *vs0.begin();
        for (auto v: vs0) if (out_cnt[v] + in_cnt[v] > out_cnt[best_first] + in_cnt[best_first]) best_first = v;
        int32_t best_second = -1;
        for (auto v: vs0)
            if (v != best_first && !checked[best_first][v] &&
                (best_second == -1 || out_cnt[v] + in_cnt[v] > out_cnt[best_second] + in_cnt[best_second]))
                best_second = v;
        if (best_second == -1)
            for (auto v: vs1)
                if (v != best_first && !checked[best_first][v])
                    best_second = v;
        if (best_second == -1) {
            res = best_first + 1;
            break;
        }
        checked[best_first][best_second] = checked[best_second][best_first] = true;
        cout << "? " << best_first + 1 << " " << best_second + 1 << "\n";
        cout.flush();
        cin >> temp_str;
        if (temp_str == "forward") {
            ++out_cnt[best_first], ++in_cnt[best_second];
            if (out_cnt[best_first] == 2) {
                vs0.erase(best_first);
                vs1.insert(best_first);
            }
        } else {
            ++in_cnt[best_first], ++out_cnt[best_second];
            if (out_cnt[best_second] == 2) {
                vs0.erase(best_second);
                vs1.insert(best_second);
            }
        }
        if (in_cnt[best_first] + 2 >= n) {
            res = best_first + 1;
            break;
        }
        if (in_cnt[best_second] + 2 >= n) {
            res = best_second + 1;
            break;
        }
    }
    cout << "! " << res << "\n";
    cout.flush();
    cin >> temp_str;
    return temp_str == "OK";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int32_t g, t;
    cin >> g >> t;
    for (uint32_t i = 0; i < t; ++i) if (!OneSol()) break;
    return 0;
}
