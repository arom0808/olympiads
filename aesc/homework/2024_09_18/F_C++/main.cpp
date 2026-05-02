#include <iostream>
#include <vector>
#include <set>

using namespace std;
using ulll = unsigned __int128;

uint32_t fig_to_num(char c) {
    if (c == 'R') return 1;
    else if (c == 'B') return 2;
    else if (c == 'K') return 3;
    else if (c == 'Q') return 4;
    return 0;
}

const int32_t tab_size = 8;
vector<uint32_t> moves;
uint32_t table[tab_size][tab_size];
set<ulll> used;

ulll zip_table() {
    ulll res = 0;
    int32_t shift = 4;
    for (int32_t i = 0; i < tab_size; ++i)
        for (int32_t j = 0; j < tab_size; ++j)
            if (table[i][j])
                res |= static_cast<ulll>(((i * 8 + j) << 2) | table[i][j]) << shift, ++res, shift += 8;
    return res;
}

bool rec();

bool try_move(int32_t i1, int32_t j1, int32_t i2, int32_t j2) {
    if (!table[i2][j2]) return false;
    moves.push_back(((i1 * 8 + j1) << 6) | (i2 * 8 + j2));
    uint32_t f1 = table[i1][j1], f2 = table[i2][j2];
    table[i1][j1] = 0, table[i2][j2] = f1;
    if (rec()) return true;
    table[i1][j1] = f1, table[i2][j2] = f2;
    moves.pop_back();
    return false;
}

bool rec() {
    ulll zipped_table = zip_table();
    if ((zipped_table & 15u) == 1) return true;
    if (used.find(zipped_table) != used.end()) return false;
    used.insert(zipped_table);
    for (int32_t i1 = 0; i1 < tab_size; ++i1) {
        for (int32_t j1 = 0; j1 < tab_size; ++j1) {
            if (!table[i1][j1]) continue;
            if (table[i1][j1] == 1 || table[i1][j1] == 4) {
                for (int32_t i2 = i1 - 1, j2 = j1; i2 >= 0 && (i2 == i1 - 1 || !table[i2 + 1][j2]); --i2)
                    if (try_move(i1, j1, i2, j2)) return true;
                for (int32_t i2 = i1 + 1, j2 = j1; i2 < tab_size && (i2 == i1 + 1 || !table[i2 - 1][j2]); ++i2)
                    if (try_move(i1, j1, i2, j2)) return true;
                for (int32_t i2 = i1, j2 = j1 - 1; j2 >= 0 && (j2 == j1 - 1 || !table[i2][j2 + 1]); --j2)
                    if (try_move(i1, j1, i2, j2)) return true;
                for (int32_t i2 = i1, j2 = j1 + 1; j2 < tab_size && (j2 == j1 + 1 || !table[i2][j2 - 1]); ++j2)
                    if (try_move(i1, j1, i2, j2)) return true;
            }
            if (table[i1][j1] == 2 || table[i1][j1] == 4) {
                for (int32_t i2 = i1 - 1, j2 = j1 - 1;
                     i2 >= 0 && j2 >= 0 && (i2 == i1 - 1 || !table[i2 + 1][j2 + 1]); --i2, --j2)
                    if (try_move(i1, j1, i2, j2)) return true;
                for (int32_t i2 = i1 - 1, j2 = j1 + 1;
                     i2 >= 0 && j2 < tab_size && (i2 == i1 - 1 || !table[i2 + 1][j2 - 1]); --i2, ++j2)
                    if (try_move(i1, j1, i2, j2)) return true;
                for (int32_t i2 = i1 + 1, j2 = j1 - 1;
                     i2 < tab_size && j2 >= 0 && (i2 == i1 + 1 || !table[i2 - 1][j2 + 1]); ++i2, --j2)
                    if (try_move(i1, j1, i2, j2)) return true;
                for (int32_t i2 = i1 + 1, j2 = j1 + 1;
                     i2 < tab_size && j2 < tab_size && (i2 == i1 + 1 || !table[i2 - 1][j2 - 1]); ++i2, ++j2)
                    if (try_move(i1, j1, i2, j2)) return true;
            }
            if (table[i1][j1] == 3) {
                for (int32_t hor = -1; hor < 2; hor += 2)
                    for (int32_t vert = -1; vert < 2; vert += 2)
                        for (int32_t order = 0, i2 = i1 + vert * (2 - order), j2 = j1 + hor * (1 + order);
                             order < 2; ++order, i2 = i1 + vert * (2 - order), j2 = j1 + hor * (1 + order))
                            if (i2 >= 0 && i2 < tab_size && j2 >= 0 && j2 < tab_size &&
                                try_move(i1, j1, i2, j2))
                                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    char c;
    for (auto &row: table) for (auto &el: row) cin >> c, el = fig_to_num(c);
    if (rec()) {
        for (auto mv: moves)
            cout << static_cast<char>('a' + ((mv >> 6) & ((1u << 3) - 1))) << (8 - (mv >> 9)) << ":"
                 << static_cast<char>('a' + (mv & ((1u << 3) - 1))) << (8 - ((mv >> 3) & ((1u << 3) - 1))) << "\n";
    } else {
        cout << "NO SOLUTION\n";
    }
    return 0;
}
