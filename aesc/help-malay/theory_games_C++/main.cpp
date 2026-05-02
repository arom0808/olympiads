#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
bool win[1000][1000];
vector<int> moves_cnt[1000][1000];

void calc_pos(int i, int j) {
    if (!moves_cnt[i][j].empty()) return;
    if (i + j >= 259) {
        win[i][j] = false;
        moves_cnt[i][j].push_back(0);
        return;
    }
    calc_pos(i * 2, j);
    calc_pos(i + 1, j);
    calc_pos(i, j * 2);
    calc_pos(i, j + 1);
    if (!win[i * 2][j] || !win[i + 1][j] || !win[i][j * 2] || !win[i][j + 1]) {
        win[i][j] = true;
        if (!win[i * 2][j]) for (auto val: moves_cnt[i * 2][j]) moves_cnt[i][j].push_back(val + 1);
        if (!win[i + 1][j]) for (auto val: moves_cnt[i + 1][j]) moves_cnt[i][j].push_back(val + 1);
        if (!win[i][j * 2]) for (auto val: moves_cnt[i][j * 2]) moves_cnt[i][j].push_back(val + 1);
        if (!win[i][j + 1]) for (auto val: moves_cnt[i][j + 1]) moves_cnt[i][j].push_back(val + 1);
        sort(moves_cnt[i][j].begin(), moves_cnt[i][j].end());
        moves_cnt[i][j].erase(unique(moves_cnt[i][j].begin(), moves_cnt[i][j].end()), moves_cnt[i][j].end());
    } else {
        win[i][j] = false;
        for (auto val: moves_cnt[i * 2][j]) moves_cnt[i][j].push_back(val + 1);
        for (auto val: moves_cnt[i + 1][j]) moves_cnt[i][j].push_back(val + 1);
        for (auto val: moves_cnt[i][j * 2]) moves_cnt[i][j].push_back(val + 1);
        for (auto val: moves_cnt[i][j + 1]) moves_cnt[i][j].push_back(val + 1);
        sort(moves_cnt[i][j].begin(), moves_cnt[i][j].end());
        moves_cnt[i][j].erase(unique(moves_cnt[i][j].begin(), moves_cnt[i][j].end()), moves_cnt[i][j].end());
    }
}

void solve() {
    for (int s = 1; s < 242; ++s) {
        calc_pos(17, s);
        if ((win[17 * 2][s] && binary_search(moves_cnt[17 * 2][s].begin(), moves_cnt[17 * 2][s].end(), 1))
            || (win[17 + 1][s] && binary_search(moves_cnt[17 + 1][s].begin(), moves_cnt[17 + 1][s].end(), 1))
            || (win[17][s * 2] && binary_search(moves_cnt[17][s * 2].begin(), moves_cnt[17][s * 2].end(), 1))
            || (win[17][s + 1] && binary_search(moves_cnt[17][s + 1].begin(), moves_cnt[17][s + 1].end(), 1))) {
            cout << "1) " << s << "\n";
            break;
        }
    }
    cout << "2) ";
    bool first = false;
    for (int s = 1; s < 242; ++s) {
        calc_pos(17, s);
        if (win[17][s] && !binary_search(moves_cnt[17][s].begin(), moves_cnt[17][s].end(), 1) &&
            binary_search(moves_cnt[17][s].begin(), moves_cnt[17][s].end(), 3)) {
            cout << s << (first ? "\n" : ", ");
            if (first) break;
            first = true;
        }
    }
    for (int s = 1; s < 242; ++s) {
        calc_pos(17, s);
        if (!win[17][s] && !binary_search(moves_cnt[17][s].begin(), moves_cnt[17][s].end(), 2) &&
            binary_search(moves_cnt[17][s].begin(), moves_cnt[17][s].end(), 4)) {
            cout << "3) " << s << "\n";
            break;
        }
    }
}

int main() {
    solve();
    return 0;
}

ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif