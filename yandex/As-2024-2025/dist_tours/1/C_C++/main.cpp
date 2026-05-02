#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <chrono>

using namespace std;

constexpr int32_t maxn = 10, maxk = 101, maxmask = 8748;
int32_t n, m, k;
int32_t max_val[maxn * maxn];
int32_t cur_val[maxn * maxn];

namespace StupidSol {
    using TimePoint = chrono::time_point<chrono::steady_clock>;

    vector<int32_t> to_update;
    vector<vector<pair<int32_t, int32_t> > > hist;
    vector<vector<pair<int32_t, pair<int32_t, int32_t> > > > act_options;
    TimePoint start_time;
    int32_t rec_calls_cnt = 0;
    bool is_continue = true;

    bool can_continue() {
        return chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start_time).count() < 950;
    }

    int32_t updated_value(int32_t to_upd_cur_val, int32_t to_upd_max_val) {
        int32_t new_val = to_upd_cur_val ? to_upd_cur_val * 2 : 1;
        return std::min(new_val, to_upd_max_val);
    }

    void reverse_updates(int32_t year) {
        to_update.clear();
        for (auto [pos, pre_val]: hist[year]) {
            cur_val[pos] = pre_val;
            if (cur_val[pos] != max_val[pos]) to_update.push_back(pos);
        }
    }

    void update(int32_t year) {
        for (int32_t i = 0; i < to_update.size();) {
            hist[year].emplace_back(to_update[i], cur_val[to_update[i]]);
            cur_val[to_update[i]] = updated_value(cur_val[to_update[i]], max_val[to_update[i]]);
            if (cur_val[to_update[i]] == max_val[to_update[i]]) to_update.erase(next(to_update.begin(), i));
            else ++i;
        }
    }

    int64_t max_ans = 0;

    void rec_sol(int32_t year, int32_t x, int32_t y, int64_t cur_ans) {
        if (!is_continue) return;
        cur_ans += cur_val[x * m + y];
        if (year + 1 == k) {
            max_ans = std::max(max_ans, cur_ans);
            return;
        }
        if (++rec_calls_cnt == 100) {
            rec_calls_cnt = 0;
            is_continue = can_continue();
        }
        if (!is_continue) return;
        hist[year].clear();
        hist[year].emplace_back(x * m + y, cur_val[x * m + y]);
        update(year);
        cur_val[x * m + y] = 0;
        to_update.push_back(x * m + y);
        act_options[year].clear();
        for (int32_t nx = x - 1; nx <= x + 1; ++nx) {
            for (int32_t ny = nx != x ? y : y - 1; ny <= y + 1; ny += 2) {
                if (nx < 0 || nx >= n || ny < 0 || ny >= m || cur_val[nx * m + ny] != max_val[nx * m + ny]) continue;
                act_options[year].emplace_back(cur_val[nx * m + ny], make_pair(nx, ny));
            }
        }
        sort(act_options[year].rbegin(), act_options[year].rend());
        for (auto [next_val, pos]: act_options[year])
            rec_sol(year + 1, pos.first, pos.second, cur_ans);
        reverse_updates(year);
    }
}

namespace SmartSol {
    int32_t dp[maxn][maxn][maxk][maxmask];
    constexpr int max_edges_dp = 9;

    void in_step(int &i, int &j, int dir) {
        if (dir == 0) --i;
        else if (dir == 1) ++j;
        else if (dir == 2) ++i;
        else --j;
    }

    // pair<int, int> step(int i, int j, int dir) {
    // in_step(i, j, dir);
    // return {i, j};
    // }

    int invert(int dir) {
        if (dir < 2) return dir + 2;
        return dir - 2;
    }

    int encode_dir_by_prev(int dir, int pre_dir) {
        return dir - (dir >= invert(pre_dir));
    }

    int decode_dir_by_prev(int en_dir, int pre_dir) {
        return en_dir + (en_dir >= invert(pre_dir));
    }

    array<int, max_edges_dp> temp_way;

    void decode_way(int mask, int edges_cnt = max_edges_dp) {
        temp_way[0] = mask % 4;
        mask /= 4;
        for (int i = 1; i < edges_cnt; ++i) {
            temp_way[i] = decode_dir_by_prev(mask % 3, temp_way[i - 1]);
            mask /= 3;
        }
    }

    int encode_way(int edges_cnt = max_edges_dp) {
        int mask = temp_way[0], mul = 4;
        for (int i = 1; i < edges_cnt; ++i) {
            mask += encode_dir_by_prev(temp_way[i], temp_way[i - 1]) * mul;
            mul *= 3;
        }
        return mask;
    }

    struct DpUpdate {
        int i, j, mask;
    };

    array<DpUpdate, 3> temp_dp_updates;

    void calc_dp_updates(int si, int sj, int mask, int max_level = max_edges_dp) {
        temp_dp_updates[0].i = temp_dp_updates[1].i = temp_dp_updates[2].i = -1;
        decode_way(mask, max_level);
        bool ok_way = true;
        for (int i = si, j = sj, level = 1; level <= max_level; ++level) {
            in_step(i, j, invert(temp_way[level - 1]));
            if (i < 0 || i >= n || j < 0 || j >= m) {
                ok_way = false;
                break;
            }
            cur_val[i * m + j] = std::min((level == 1 ? 0 : (1 << (level - 2))), max_val[i * m + j]);
        }
        if (ok_way) {
            int last_way_val = temp_way[max_edges_dp - 1];
            for (int i = max_edges_dp - 1; i > 0; --i) temp_way[i] = temp_way[i - 1];
            int calcuted_cnt = 0;
            for (int dir = 0, i = si, j = sj; dir < 4; ++dir, i = si, j = sj) {
                in_step(i, j, dir);
                if (i < 0 || i >= n || j < 0 || j >= m || cur_val[i * m + j] != max_val[i * m + j]) continue;
                temp_way[0] = dir;
                temp_dp_updates[calcuted_cnt++] = {i, j, encode_way(std::min(max_level + 1, max_edges_dp))};
            }
            for (int i = 0; i < max_edges_dp - 1; ++i) temp_way[i] = temp_way[i + 1];
            temp_way[max_edges_dp - 1] = last_way_val;
        }
        for (int i = si, j = sj, level = 1; level <= max_level; ++level) {
            in_step(i, j, invert(temp_way[level - 1]));
            if (i < 0 || i >= n || j < 0 || j >= m) return;
            cur_val[i * m + j] = max_val[i * m + j];
        }
    }

    array<DpUpdate, 3> cached_updates[maxn][maxn][maxmask];

    void init() {
        temp_dp_updates = {-1, -1, -1};
        for (int i = 0; i < maxn; ++i)
            for (int j = 0; j < maxn; ++j)
                for (int mask = 0; mask < maxmask; ++mask)
                    cached_updates[i][j][mask] = temp_dp_updates;
    }

    void calc_cached_updates(int max_level) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int mask = 0; mask < maxmask; ++mask) {
                    calc_dp_updates(i, j, mask, max_level);
                    cached_updates[i][j][mask] = temp_dp_updates;
                }
            }
        }
    }

    void solve() {
        for (int mask = 0; mask < maxmask; ++mask) dp[0][0][1][mask] = max_val[0];
        for (int t = 1; t < k; ++t) {
            if (t <= max_edges_dp + 1) calc_cached_updates(t - 1);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    for (int mask = 0; mask < maxmask; ++mask) {
                        if (dp[i][j][t][mask] == 0) continue;
                        for (int uid = 0; uid < 3 && cached_updates[i][j][mask][uid].i != -1; ++uid) {
                            auto [ni,nj,nmask] = cached_updates[i][j][mask][uid];
                            dp[ni][nj][t + 1][nmask] =
                                    std::max(dp[ni][nj][t + 1][nmask], dp[i][j][t][mask] + max_val[ni * m + nj]);
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int mask = 0; mask < maxmask; ++mask) {
                    ans = std::max(ans, dp[i][j][k][mask]);
                }
            }
        }
        cout << ans << "\n";
    }
}

void main_solve() {
    cin >> n >> m >> k;
    StupidSol::start_time = chrono::steady_clock::now();
    StupidSol::hist.resize(k);
    StupidSol::act_options.resize(k);
    for (int32_t i = 0; i < n; ++i)
        for (int32_t j = 0; j < m; ++j)
            cin >> max_val[i * m + j], cur_val[i * m + j] = max_val[i * m + j];
    SmartSol::init();
    SmartSol::solve();
    // if (k <= 10) {
    StupidSol::rec_sol(0, 0, 0, 0);
    cout << StupidSol::max_ans << "\n";
    // }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    main_solve();
#else
    main_solve();
#endif
    return 0;
}
