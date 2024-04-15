#include <iostream>
#include <vector>
#include <deque>

using namespace std;

const uint32_t inf = 2e9;

enum class Plit {
    none = 0, left = 1, right = 2
};

struct QueEl {
    uint32_t i, j, t;
};

uint32_t glob_timer = 1;
vector<vector<vector<uint32_t>>> glob_visited;

uint32_t ways_cnt(uint32_t n, uint32_t m, const vector<vector<Plit>> &table) {
    deque<QueEl> que;
    uint32_t ways_cnt = 0;
    while (true) {
        bool found = false;
        for (uint32_t i = 0; i < n; ++i) {
            for (uint32_t j = 0; j < m; ++j) {
                if (table[i][j] == Plit::none) continue;
                for (uint32_t t = 0; t < 4; ++t) {
                    if (glob_visited[i][j][t] != glob_timer) {
                        que.emplace_back(i, j, t);
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            if (found) break;
        }
        if (!found) break;
        ++ways_cnt;
        while (!que.empty()) {
            auto [i, j, t] = que.front();
            que.pop_front();
            if (glob_visited[i][j][t] == glob_timer) continue;
            glob_visited[i][j][t] = glob_timer;
            if (t == 0 && j > 0) que.emplace_back(i, j - 1, 2);
            if (t == 1 && i > 0) que.emplace_back(i - 1, j, 3);
            if (t == 2 && j + 1 < m) que.emplace_back(i, j + 1, 0);
            if (t == 3 && i + 1 < n) que.emplace_back(i + 1, j, 1);
            if (table[i][j] == Plit::left) {
                if (t == 0) que.emplace_back(i, j, 3);
                if (t == 1) que.emplace_back(i, j, 2);
                if (t == 2) que.emplace_back(i, j, 1);
                if (t == 3) que.emplace_back(i, j, 0);
                if (t == 0 && i + 1 < n) que.emplace_back(i + 1, j, 1);
                if (t == 1 && j + 1 < m) que.emplace_back(i, j + 1, 0);
                if (t == 2 && i > 0) que.emplace_back(i - 1, j, 3);
                if (t == 3 && j > 0) que.emplace_back(i, j - 1, 2);
            } else if (table[i][j] == Plit::right) {
                if (t == 0) que.emplace_back(i, j, 1);
                if (t == 1) que.emplace_back(i, j, 0);
                if (t == 2) que.emplace_back(i, j, 3);
                if (t == 3) que.emplace_back(i, j, 2);
                if (t == 0 && i > 0) que.emplace_back(i - 1, j, 3);
                if (t == 1 && j > 0) que.emplace_back(i, j - 1, 2);
                if (t == 2 && i + 1 < n) que.emplace_back(i + 1, j, 1);
                if (t == 3 && j + 1 < m) que.emplace_back(i, j + 1, 0);
            }
        }
    }
    ++glob_timer;
    return ways_cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint32_t n, m, k;
    cin >> n >> m >> k;
    glob_visited.assign(n, vector<vector<uint32_t>>(m, vector<uint32_t>(4, 0)));
    vector<vector<Plit>> table(n, vector<Plit>(m));
    char tc;
    for (auto &row: table) {
        for (auto &plit: row) {
            cin >> tc;
            if (tc == '\\') plit = Plit::left;
            else if (tc == '/') plit = Plit::right;
            else plit = Plit::none;
        }
    }
    uint32_t best_res = ways_cnt(n, m, table);
    if (k >= 1) {
        for (auto &row: table) {
            for (auto &plit: row) {
                if (plit == Plit::none) continue;
                else if (plit == Plit::left) plit = Plit::right;
                else plit = Plit::left;
                best_res = min(best_res, ways_cnt(n, m, table));
                if (plit == Plit::left) plit = Plit::right;
                else plit = Plit::left;
            }
        }
    }
    if (k == 2) {
        for (uint32_t i1 = 0; i1 < n; ++i1) {
            for (uint32_t j1 = 0; j1 < m; ++j1) {
                for (uint32_t i2 = i1 + 1; i2 < n; ++i2) {
                    for (uint32_t j2 = j1 + 1; j2 < m; ++j2) {
                        if (table[i1][j1] == Plit::none || table[i2][j2] == Plit::none) continue;
                        if (table[i1][j1] == Plit::left) table[i1][j1] = Plit::right;
                        else table[i1][j1] = Plit::left;
                        if (table[i2][j2] == Plit::left) table[i2][j2] = Plit::right;
                        else table[i2][j2] = Plit::left;
                        best_res = min(best_res, ways_cnt(n, m, table));
                        if (table[i1][j1] == Plit::left) table[i1][j1] = Plit::right;
                        else table[i1][j1] = Plit::left;
                        if (table[i2][j2] == Plit::left) table[i2][j2] = Plit::right;
                        else table[i2][j2] = Plit::left;
                    }
                }
            }
        }
    }
    cout << best_res;
    return 0;
}

//#include <iostream>
//#include <vector>
//#include <list>
//#include <deque>
//#include <fstream>
//
//using namespace std;
//
//enum class Plit {
//    none = 0, left = 1, right = 2
//};
//
//const uint32_t inf = 2e9;
//struct QueEl {
//    uint32_t i, j, t;
//};
//
//void rec_sol(vector<vector<Plit>> &table, uint32_t ri, uint32_t rj, uint32_t n, uint32_t m,
//             uint32_t &best_ways_cnt, list<vector<vector<Plit>>> &best_res) {
//    if (ri >= n || rj >= m) {
//        vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(4, false)));
//        deque<QueEl> que;
//        uint32_t ways_cnt = 0;
//        while (true) {
//            bool found = false;
//            for (uint32_t i = 0; i < n; ++i) {
//                for (uint32_t j = 0; j < m; ++j) {
//                    if (table[i][j] == Plit::none) continue;
//                    for (uint32_t t = 0; t < 4; ++t) {
//                        if (!visited[i][j][t]) {
//                            que.emplace_back(i, j, t);
//                            found = true;
//                            break;
//                        }
//                    }
//                    if (found) break;
//                }
//                if (found) break;
//            }
//            if (!found) break;
//            ++ways_cnt;
//            while (!que.empty()) {
//                auto [i, j, t] = que.front();
//                que.pop_front();
//                if (visited[i][j][t]) continue;
//                visited[i][j][t] = true;
//                if (table[i][j] == Plit::left) {
//                    if (t == 0 && i + 1 < n) que.emplace_back(i + 1, j, 1);
//                    if (t == 1 && j + 1 < m) que.emplace_back(i, j + 1, 0);
//                    if (t == 2 && i > 0) que.emplace_back(i - 1, j, 3);
//                    if (t == 3 && j > 0) que.emplace_back(i, j - 1, 2);
//                } else {
//                    if (t == 0 && i > 0) que.emplace_back(i - 1, j, 3);
//                    if (t == 1 && j > 0) que.emplace_back(i, j - 1, 2);
//                    if (t == 2 && i + 1 < n) que.emplace_back(i + 1, j, 1);
//                    if (t == 3 && j + 1 < m) que.emplace_back(i, j + 1, 0);
//                }
//            }
//        }
//        if (ways_cnt < best_ways_cnt) {
//            best_ways_cnt = ways_cnt;
//            best_res.clear();
//            best_res.emplace_back(table);
//        } else if (ways_cnt == best_ways_cnt) best_res.emplace_back(table);
//        return;
//    }
//    if (table[ri][rj] == Plit::none)
//        rec_sol(table, (rj + 1 < m ? ri : ri + 1), (rj + 1 < m ? rj + 1 : 0), n, m, best_ways_cnt, best_res);
//    else {
//        table[ri][rj] = Plit::left;
//        rec_sol(table, (rj + 1 < m ? ri : ri + 1), (rj + 1 < m ? rj + 1 : 0), n, m, best_ways_cnt, best_res);
//        table[ri][rj] = Plit::right;
//        rec_sol(table, (rj + 1 < m ? ri : ri + 1), (rj + 1 < m ? rj + 1 : 0), n, m, best_ways_cnt, best_res);
//    }
//}
//
//int main() {
//    uint32_t n, m;
//    cin >> n >> m;
//    char c;
//    vector<vector<Plit>> table(n, vector<Plit>(m, Plit::none));
//    for (uint32_t i = 0; i < n; ++i) {
//        for (uint32_t j = 0; j < m; ++j) {
//            cin >> c;
//            if (c != '.') table[i][j] = Plit::left;
//        }
//    }
//    uint32_t best_ways_cnt = inf;
//    list<vector<vector<Plit>>> best_res;
//    rec_sol(table, 0, 0, n, m, best_ways_cnt, best_res);
//    ofstream out("out.txt");
//    out << best_ways_cnt << "\n\n";
//    for (auto &br: best_res) {
//        for (uint32_t i = 0; i < n; ++i) {
//            for (uint32_t j = 0; j < m; ++j) {
//                if (br[i][j] == Plit::none) out << '.';
//                else if (br[i][j] == Plit::left) out << '\\';
//                else out << '/';
//            }
//            out << "\n";
//        }
//        out << "\n";
//    }
//    return 0;
//}
