#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct Ceil {
    char left = ' ', top = ' ', right = ' ', bottom = ' ';
};

inline uint32_t count_ones(uint32_t num) {
    if (num == 0) return 0;
    if (num == 1 || num == 2 || num == 4 || num == 8) return 1;
    if (num == 3 || num == 5 || num == 6 || num == 9 || num == 10 || num == 12) return 2;
    if (num == 7 || num == 11 || num == 13 || num == 14) return 3;
    return 4;
}

inline bool is_ok_color(char color, uint32_t mask) {
    if (color == ' ') return false;
    if (color == 'P') return mask & 1;
    if (color == 'C') return (mask >> 1) & 1;
    if (color == 'Z') return (mask >> 2) & 1;
    return (mask >> 3) & 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    uint32_t n, m;
    cin >> n >> m;
    vector<vector<Ceil>> table(n, vector<Ceil>(m));
    for (uint32_t i = 0; i < n; ++i) {
        for (uint32_t j = 0; j + 1 < m; ++j) {
            cin >> table[i][j].right;
            table[i][j + 1].left = table[i][j].right;
        }
    }
    for (uint32_t i = 0; i + 1 < n; ++i) {
        for (uint32_t j = 0; j < m; ++j) {
            cin >> table[i][j].bottom;
            table[i + 1][j].top = table[i][j].bottom;
        }
    }
    uint32_t q;
    cin >> q;
    vector<vector<uint32_t>> used(n, vector<uint32_t>(m, 0));
    deque<pair<uint32_t, uint32_t>> to_visit;
    uint32_t t = 1;
    for (uint32_t _ = 0, a, b, c, d; _ < q; ++_) {
        cin >> a >> b >> c >> d;
        --a;
        --b;
        --c;
        --d;
        uint32_t best_res = 4;
        for (uint32_t mask = 0; mask < 16; ++mask) {
            to_visit.clear();
            to_visit.emplace_back(a, b);
            bool found = false;
            while (!to_visit.empty()) {
                auto [i, j] = to_visit.front();
                to_visit.pop_front();
                if (i == c && j == d) {
                    found = true;
                    break;
                }
                if (used[i][j] == t) continue;
                used[i][j] = t;
                if (i > 0 && is_ok_color(table[i][j].top, mask) && used[i - 1][j] != t)
                    to_visit.emplace_back(i - 1, j);
                if (i + 1 < n && is_ok_color(table[i][j].bottom, mask) && used[i + 1][j] != t)
                    to_visit.emplace_back(i + 1, j);
                if (j > 0 && is_ok_color(table[i][j].left, mask) && used[i][j - 1] != t)
                    to_visit.emplace_back(i, j - 1);
                if (j + 1 < m && is_ok_color(table[i][j].right, mask) && used[i][j + 1] != t)
                    to_visit.emplace_back(i, j + 1);
            }
            if (found && count_ones(mask) < best_res) best_res = count_ones(mask);
            ++t;
        }
        cout << best_res << "\n";
    }
    return 0;
}
