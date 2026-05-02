#include <iostream>
//#include <fstream>
#include <vector>
#include <random>

using namespace std;

const int32_t maxn = 3000;

int32_t t, n, p, k, a, p_id;
int32_t field[maxn][maxn];
int32_t ncx = -1, ncy = -1, ncs = -1;
int32_t lx = -1e9, ly = -1e9, step_id = 0;

namespace Rand {
    random_device dev;
    uint32_t seed = dev();
//    uint32_t seed = 3105308183;
    mt19937 rng(seed);

    template<typename T>
    T randint(T a, T b) {
        return uniform_int_distribution(a, b)(rng);
    }
}

struct Block{

};

void gen_nc() {
    ncs = Rand::randint(n / 4, n);
    ncx = Rand::randint(ncs - n - 1, n - ncs + 1);
    ncy = Rand::randint(ncs - n - 1, n - ncs + 1);
}

pair<int32_t, int32_t> try_make_move() {
    for (int32_t x = ncx; x < ncx + ncs; ++x) {
        int32_t y = -x + ncx + ncy + ncs - 1;
        if (field[y + a][x + a] == 0) return {x, y};
        y = x + ncy - ncx - ncs + 1;
        if (field[y + a][x + a] == 0) return {x, y};
    }
    for (int32_t x = ncx - ncs + 1; x < ncx; ++x) {
        int32_t y = x + ncy - ncx + ncs - 1;
        if (field[y + a][x + a] == 0) return {x, y};
        y = -x + ncx + ncy - ncx + 1;
        if (field[y + a][x + a] == 0) return {x, y};
    }
    ncs = -1;
    return {0, 0};
}

pair<int32_t, int32_t> make_move() {
    if (step_id % 2 == 1) {
        if (lx >= -n && ly >= -n) {
            if (ly + 1 <= n && field[ly + a + 1][lx + a] == 0) return {lx, ly + 1};
            if (ly - 1 >= n && field[ly + a - 1][lx + a] == 0) return {lx, ly - 1};
            if (lx + 1 <= n && field[ly + a][lx + a + 1] == 0) return {lx + 1, ly};
            if (lx - 1 >= n && field[ly + a][lx + a - 1] == 0) return {lx - 1, ly};
        }
    }
    if (ncs == -1) gen_nc();
    auto [x, y] = try_make_move();
    while (ncs == -1) {
        gen_nc();
        auto [nx, ny] = try_make_move();
        x = nx, y = ny;
    }
    return {x, y};
}

int32_t used[maxn][maxn];
vector<pair<int32_t, int32_t>> n_visited;
int32_t timer = 0;
bool border_met = false;

void dfs(int32_t x, int32_t y, int32_t np_id) {
    if (used[y + a][x + a] == timer || border_met) return;
    used[y + a][x + a] = timer;
    if (x < -n || x > n || y < -n || y > n) {
        border_met = true;
        return;
    }
    if (field[y + a][x + a] == np_id) return;
    n_visited.emplace_back(x, y);
    dfs(x - 1, y, np_id);
    dfs(x + 1, y, np_id);
    dfs(x, y - 1, np_id);
    dfs(x, y + 1, np_id);
}

void check_and_fill() {
    for (int32_t np_id = 1; np_id <= k; ++np_id) {
        ++timer;
        for (int32_t y = -n; y <= n; ++y) {
            for (int32_t x = -n; x <= n; ++x) {
                if (field[y + a][x + a] != 0 || used[y + a][x + a] == timer) continue;
                n_visited.clear();
                border_met = false;
                dfs(x, y, np_id);
                if (!border_met) {
                    for (auto [tx, ty]: n_visited) {
                        if (field[ty + a][tx + a] != -1) field[ty + a][tx + a] = np_id;
                    }
                }
            }
        }
    }
}

int main() {
    cin >> t >> n >> p >> k >> a >> p_id;
    a /= 2;
    for (auto &line: field) for (int &el: line) el = -2;
    for (int32_t y = n, val; y >= -n; --y) {
        for (int32_t x = -n; x <= n; ++x) {
            cin >> val;
            field[y + a][x + a] = val;
        }
    }
//    ofstream of(string("ot") + to_string(p_id) + ".txt");
//    of << "seed: " << Rand::seed << "\n";
//    for (int32_t y = n; y >= -n; --y) {
//        for (int32_t x = -n; x <= n; ++x)
//            of << field[y + a][x + a] << " ";
//        of << "\n";
//    }
//    of << "\n";
//    of.flush();
    while (true) {
        ++step_id;
        int32_t num, x, y;
        cin >> num >> x >> y;
        if (num == -1) {
            ++n;
            for (int32_t i = -n; i <= n; ++i)
                field[a - n][a + i] = field[a + n][a + i] = field[a + i][a - n] = field[a + i][a + n] = 0;
            cin >> num >> x >> y;
            while (num != -1) {
                field[y + a][x + a] = -1;
                cin >> num >> x >> y;
            }
        } else if (num == -2) {
            auto [mx, my] = make_move();
            field[my + a][mx + a] = p_id;
            check_and_fill();
            cout << mx << " " << my << "\n";
            cout.flush();
        } else if (num == -3) {
            return 0;
        } else {
            field[y + a][x + a] = num;
            lx = x, ly = y;
            check_and_fill();
        }
    }
    return 0;
}
