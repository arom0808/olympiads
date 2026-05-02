#include <iostream>
#include <vector>
#include <deque>

using namespace std;

const int32_t maxn = 2e5, maxm = 5;

int32_t parents[maxn];
bool removed[maxn];
int32_t spies[maxm][maxn];
int32_t spies_pos[maxm][maxn];
int32_t spies_precessed[maxm];
vector<int32_t> g[maxn];

void sol_test() {
    int32_t n, m;
    cin >> n >> m;
    parents[0] = -1;
    for (int32_t i = 0; i < n; ++i) g[i].clear();
    for (int32_t i = 1; i < n; ++i) cin >> parents[i], g[parents[i]].push_back(i);
    for (int32_t i = 0; i < n; ++i) removed[i] = false;
    for (int32_t i = 0; i < m; ++i)
        for (int32_t j = 0; j + 1 < n; ++j)
            cin >> spies[i][j], spies_pos[i][spies[i][j]] = j;
    for (int32_t i = 0; i < m; ++i) spies_precessed[i] = 0;
    deque<int32_t> to_remove;
    int32_t removed_cnt = 0;
    int32_t day = 0;
    while (removed_cnt + 1 < n) {
        to_remove.push_back(spies[0][spies_precessed[0]]);
        ++removed_cnt;
        removed[spies[0][spies_precessed[0]]] = true;
        while (!to_remove.empty()) {
            auto cur_n = to_remove.front();
            to_remove.pop_front();
            int32_t max_sp_pos = 0;
            for (int32_t sp = 0; sp < m; ++sp) {
                if (spies_pos[sp][cur_n] > max_sp_pos) max_sp_pos = spies_pos[sp][cur_n];
                if (spies_precessed[sp] - 1 > max_sp_pos) max_sp_pos = spies_precessed[sp] - 1;
            }
            for (int32_t sp = 0; sp < m; ++sp) {
                for (int32_t i = spies_precessed[sp]; i <= max_sp_pos; ++i) {
                    if (!removed[spies[sp][i]]) {
                        to_remove.push_back(spies[sp][i]);
                        removed[spies[sp][i]] = true;
                        ++removed_cnt;
                    }
                }
                spies_precessed[sp] = max_sp_pos + 1;
            }
            for (auto u: g[cur_n]) if (!removed[u]) to_remove.push_back(u), removed[u] = true, ++removed_cnt;
        }
        ++day;
    }
    cout << day << "\n";
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    uint32_t t;
    cin >> t;
    while (t--) {
        sol_test();
    }
    return 0;
}
