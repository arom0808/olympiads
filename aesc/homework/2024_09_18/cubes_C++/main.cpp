#include <iostream>

using namespace std;

int32_t cube_to_num[256];
string num_to_cube = ".LRBFDU";
int32_t move_table[7][4] = {{0, 0, 0, 0},
                            {1, 6, 1, 5},
                            {2, 5, 2, 6},
                            {5, 3, 6, 3},
                            {6, 4, 5, 4},
                            {4, 1, 3, 2},
                            {3, 2, 4, 1}};
int32_t o_table[9];

int32_t zip_table() {
    int32_t res = 0, p_pos = 0;
    for (int32_t i = 0; i < 9; ++i) {
        if (o_table[i]) res = (res * 6) + o_table[i] - 1;
        else p_pos = i;
    }
    return res * 9 + p_pos;
}

void unzip_table(int32_t zipped_table) {
    for (auto &el: o_table) el = 1;
    o_table[zipped_table % 9] = 0;
    zipped_table /= 9;
    for (int32_t i = 9; i > 0;) {
        --i;
        if (o_table[i] == 0) continue;
        o_table[i] = zipped_table % 6 + 1;
        zipped_table /= 6;
    }
}

void init_stat_arrs() {
    for (int32_t i = 0; i < num_to_cube.size(); ++i) cube_to_num[num_to_cube[i]] = i;
}

bool is_table_ok() {
    for (auto el: o_table) if (el && el != 6) return false;
    return true;
}

const int32_t make_move_poss[4] = {-3, 1, 3, -1};

void make_move(int32_t pos, int32_t mv) {
    o_table[pos] = move_table[o_table[pos]][mv];
    swap(o_table[pos], o_table[pos + make_move_poss[mv]]);
}

namespace Que {
    const int32_t sz = 20000000;
    pair<int32_t, int32_t> v_que[sz];
    int32_t start = 0, end = 0;

    void emplace(int32_t a, int32_t b) {
        v_que[end++] = {a, b};
        if (end == sz) end = 0;
    }

    pair<int32_t, int32_t> pop() {
        if (++start == sz) start = 0;
        return start ? v_que[start - 1] : v_que[sz - 1];
    }

    int32_t size() {
        return end >= start ? end - start : sz - start + end;
    }
}


const int32_t main_poss[4] = {-3, 1, 3, -1};
bool used[16000000];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    init_stat_arrs();
    o_table[4] = cube_to_num['.'];
    char c;
    int32_t in_poss[8] = {0, 1, 2, 5, 8, 7, 6, 3};
    for (int in_pos: in_poss) cin >> c, o_table[in_pos] = cube_to_num[c];
    int32_t moves_cnt = 0;
    Que::emplace(zip_table(), 0);
    used[zip_table()] = true;
    while (Que::size() != 0) {
        auto v_pair = Que::pop();
        auto zp = v_pair.first, level = v_pair.second;
        unzip_table(zp);
        if (is_table_ok()) {
            moves_cnt = level;
            break;
        }
        int32_t point_pos = 0;
        while (o_table[point_pos]) ++point_pos;
        bool cs[4] = {point_pos / 3 > 0, point_pos % 3 < 2, point_pos / 3 < 2, point_pos % 3 > 0};
        for (int32_t i = 0; i < 4; ++i) {
            if (cs[i]) {
                make_move(point_pos + main_poss[i], (i + 2) & 3);
                zp = zip_table();
                if (!used[zp]) {
                    Que::emplace(zp, level + 1);
                    used[zp] = true;
                }
                make_move(point_pos, i);
            }
        }
    }
    cout << moves_cnt << "\n";
    return 0;
}
