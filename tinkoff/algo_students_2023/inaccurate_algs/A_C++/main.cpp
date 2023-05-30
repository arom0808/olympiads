//void IterateAllStrikePositions(std::uint32_t start_i, std::uint32_t start_j, std::uint32_t N,
//                               const std::function<void(std::uint32_t, std::uint32_t)> &function) {
//    for (std::uint32_t i = 0, j = start_j; i < N; ++i) if (i != start_i) function(i, j);
//    for (std::uint32_t i = start_i, j = 0; j < N; ++j) if (j != start_j) function(i, j);
//    for (auto i = static_cast<std::int32_t>(start_i), j = static_cast<std::int32_t>(start_j);
//         i >= 0 && j >= 0; --i, --j)
//        if (i != start_i || j != start_j)
//            function(i, j);
//    for (auto i = static_cast<std::int32_t>(start_i), j = static_cast<std::int32_t>(start_j);
//         i >= 0 && j < N; --i, ++j)
//        if (i != start_i || j != start_j)
//            function(i, j);
//    for (auto i = static_cast<std::int32_t>(start_i), j = static_cast<std::int32_t>(start_j);
//         i < N && j >= 0; ++i, --j)
//        if (i != start_i || j != start_j)
//            function(i, j);
//    for (auto i = static_cast<std::int32_t>(start_i), j = static_cast<std::int32_t>(start_j);
//         i < N && j < N; ++i, ++j)
//        if (i != start_i || j != start_j)
//            function(i, j);
//}
//
////struct Changes {
////    std::pair<std::uint32_t, std::uint32_t> coords_table_changed;
////    std::uint32_t start_count_not_strike;
////    std::map<std::pair<std::uint32_t, std::uint32_t>, std::uint32_t> start_strike_cnts_values;
////};
//
//void MiniChange(std::vector<std::vector<bool>> &table, std::vector<std::vector<std::uint32_t>> &strike_cnts,
//                std::uint32_t &count_not_strike) {
//    std::uint32_t start_i = Random::GetRandom_0_N(), start_j = Random::GetRandom_0_N();
////    changes.coords_table_changed = {start_i, start_j};
////    changes.start_count_not_strike = count_not_strike;
////    changes.start_strike_cnts_values.clear();
////    changes.start_strike_cnts_values.emplace(std::pair<std::uint32_t, std::uint32_t>{start_i, start_j},
////                                             strike_cnts[start_i][start_j]);
//    if (table[start_i][start_j]) if (strike_cnts[start_i][start_j] == 0) --count_not_strike;
//    IterateAllStrikePositions(
//            start_i, start_j, strike_cnts.size(),
//            [&table, &strike_cnts, &count_not_strike, start_i, start_j]
//                    (std::uint32_t i, std::uint32_t j) {
//                if (!table[i][j]) return;
////                if (start_strike_cnts_values.find({i, j}) == start_strike_cnts_values.end())
////                    start_strike_cnts_values.emplace(std::pair<std::uint32_t, std::uint32_t>{i, j}, strike_cnts[i][j]);
//                if (!table[start_i][start_j]) {
//                    if (strike_cnts[i][j] == 0) --count_not_strike;
//                    ++strike_cnts[i][j];
//                    ++strike_cnts[start_i][start_j];
//                } else {
//                    --strike_cnts[i][j];
//                    --strike_cnts[start_i][start_j];
//                    if (strike_cnts[i][j] == 0) ++count_not_strike;
//                }
//            });
//    if (!table[start_i][start_j]) if (strike_cnts[start_i][start_j] == 0) ++count_not_strike;
//    table[start_i][start_j] = !table[start_i][start_j];
//}
//
////void ReverseChanges(std::vector<std::vector<bool>> &table, std::vector<std::vector<std::uint32_t>> &strike_cnts,
////                    std::uint32_t &count_not_strike, const Changes &changes) {
////    table[changes.coords_table_changed.first][changes.coords_table_changed.second] = !table[changes.coords_table_changed.first][changes.coords_table_changed.second];
////    count_not_strike = changes.start_count_not_strike;
////    for (const auto &c: changes.start_strike_cnts_values)
////        strike_cnts[c.first.first][c.first.second] = c.second;
////}
//
//struct OneTable {
//public:
//    std::vector<std::vector<bool>> table;
//    std::vector<std::vector<std::uint32_t>> strike_cnts;
//    std::uint32_t count_not_strike;
//
//    friend void swap(OneTable &a, OneTable &b) {
//        using std::swap;
//        swap(a.table, b.table);
//        swap(a.strike_cnts, b.strike_cnts);
//        swap(a.count_not_strike, b.count_not_strike);
//    }
//
////    void swap(OneTable &other) {
////        using std::swap;
////        table.swap(other.table);
////        strike_cnts.swap(other.strike_cnts);
////        std::swap(count_not_strike, other.count_not_strike);
////    }
//
//    bool operator<(const OneTable &other) const {
//        if(this->count_not_strike!=other.count_not_strike)
//        return this->count_not_strike + this->salt > other.count_not_strike + other.salt;
//    }
//
//    OneTable(const OneTable &other) = default;
//
//    OneTable &operator=(const OneTable &other) = default;
//
////    OneTable &operator=(OneTable &&other)  noexcept {}
//
//    OneTable(OneTable &&other) noexcept: table(std::move(other.table)), strike_cnts(std::move(other.strike_cnts)),
//                                         count_not_strike(other.count_not_strike), salt(other.salt) {}
//
//    explicit OneTable(std::uint32_t N) : table(N, std::vector<bool>(N, false)),
//                                         strike_cnts(N, std::vector<std::uint32_t>(N, 0)), count_not_strike(0),
//                                         salt(Random::GetRandomSalt()) {}
//};
//
//void GetSolForThisInput(std::uint32_t N) {
//    Random::InitN(N);
//    std::vector<OneTable> tables(110, OneTable(N));
//    while (std::min_element(tables.begin(), std::next(tables.begin(), 10), [](const OneTable &a, const OneTable &b) {
//        return a.count_not_strike > b.count_not_strike;
//    })->count_not_strike < N) {
//        for (std::uint32_t i = 0; i < 10; ++i) {
//            for (std::uint32_t j = (i + 1) * 10; j < (i + 2) * 10; ++j) {
//                std::copy(tables[i].table.begin(), tables[i].table.end(), tables[j].table.begin());
//                std::copy(tables[i].strike_cnts.begin(), tables[i].strike_cnts.end(), tables[j].strike_cnts.begin());
//                tables[j].count_not_strike = tables[i].count_not_strike;
//                tables[j].salt = Random::GetRandomSalt();
//                MiniChange(tables[j].table, tables[j].strike_cnts, tables[j].count_not_strike);
//            }
//        }
//        std::partial_sort(tables.begin(), std::next(tables.begin(), 10), tables.end());
//    }
//}
//
//



//#include <random>
//#include <functional>
//#include <algorithm>
//#include <map>
//#include <fstream>
//#include <unordered_set>
//#include <set>
//#include <iostream>
//#include <chrono>
//#include <vector>
//
//namespace Random {
//    std::random_device dev;
////    std::uint32_t seed = dev();
//    std::uint32_t seed = 1337866407;
//    std::mt19937 rng(seed);
//
//    std::uint32_t GetRandom(std::uint32_t from, std::uint32_t to) {
//        return std::uniform_int_distribution<std::uint32_t>(from, to)(rng);
//    }
//};

//struct pair_hash {
//    inline std::size_t operator()(const std::pair<std::uint32_t, std::uint32_t> &v) const {
//        return (static_cast<std::uint64_t>(v.first) << 32) + v.second;
//    }
//};

//struct OneTable {
//    std::vector<std::vector<std::uint8_t>> strikes_cnts;
//    std::unordered_map<std::uint8_t, std::unordered_set<std::uint8_t>> free_ceils;
//    std::vector<std::uint8_t> queue_positons;
//    std::uint8_t queen_cnts;
//    std::uint32_t free_cnt;
//
//    explicit OneTable(std::uint8_t N) : strikes_cnts(N, std::vector<std::uint8_t>(N, 0)), queen_cnts(0),
//                                        free_cnt(N * N), queue_positons(N, 0) {
//        std::unordered_set<std::uint8_t> temp_free_ceils;
//        for (std::uint8_t i = 0; i < N; ++i) temp_free_ceils.emplace(i);
//        for (std::uint8_t i = 0; i < N; ++i) free_ceils.emplace(i, temp_free_ceils);
//    }
//
//    friend void swap(OneTable &a, OneTable &b) {
//        using std::swap;
//        swap(a.strikes_cnts, b.strikes_cnts);
//        swap(a.free_ceils, b.free_ceils);
//        swap(a.queue_positons, b.queue_positons);
//        swap(a.queen_cnts, b.queen_cnts);
//        swap(a.free_cnt, b.free_cnt);
//    }
//
//    bool operator<(const OneTable &other) const {
//        if (queen_cnts != other.queen_cnts) return queen_cnts > other.queen_cnts;
//        return free_cnt > other.free_cnt;
//    }
//
//    OneTable &operator=(const OneTable &other) = default;
//
//    OneTable(const OneTable &other) = default;
//
//    OneTable(OneTable &&other) noexcept: strikes_cnts(std::move(other.strikes_cnts)),
//                                         free_ceils(std::move(other.free_ceils)),
//                                         queue_positons(std::move(other.queue_positons)),
//                                         queen_cnts(other.queen_cnts), free_cnt(other.free_cnt) {
//        other.free_cnt = other.queen_cnts = 0;
//    }
//};

//void IterateAllStrikePositions(std::uint8_t start_i, std::uint8_t start_j, std::uint8_t N,
//                               const std::function<void(std::uint8_t, std::uint8_t)> &function) {
//    for (std::uint8_t i = 0, j = start_j; i < N; ++i) if (i != start_i) function(i, j);
//    for (std::uint8_t i = start_i, j = 0; j < N; ++j) if (j != start_j) function(i, j);
//    for (auto i = static_cast<std::int16_t>(start_i), j = static_cast<std::int16_t>(start_j);
//         i >= 0 && j >= 0; --i, --j)
//        if (i != start_i || j != start_j)
//            function(i, j);
//    for (auto i = static_cast<std::int16_t>(start_i), j = static_cast<std::int16_t>(start_j);
//         i >= 0 && j < N; --i, ++j)
//        if (i != start_i || j != start_j)
//            function(i, j);
//    for (auto i = static_cast<std::int16_t>(start_i), j = static_cast<std::int16_t>(start_j);
//         i < N && j >= 0; ++i, --j)
//        if (i != start_i || j != start_j)
//            function(i, j);
//    for (auto i = static_cast<std::int16_t>(start_i), j = static_cast<std::int16_t>(start_j);
//         i < N && j < N; ++i, ++j)
//        if (i != start_i || j != start_j)
//            function(i, j);
//}

//std::pair<std::uint8_t, std::uint8_t> MiniChange(OneTable &table, std::uint8_t N) {
//    if (table.free_cnt == 0) return {0, 0};
//    auto temp_start_it = *std::next(table.free_ceils.begin(), Random::GetRandom(0, table.free_ceils.size() - 1));
//    auto start_i = temp_start_it.first;
//    auto start_j = *std::next(temp_start_it.second.begin(), Random::GetRandom(0, temp_start_it.second.size() - 1));
//    table.queue_positons[start_i] = start_j;
//    ++table.queen_cnts;
//    ++table.strikes_cnts[start_i][start_j];
//    --table.free_cnt;
//    temp_start_it.second.erase(start_j);
//    table.free_ceils.erase(start_i);
//    IterateAllStrikePositions(
//            start_i, start_j, N,
//            [&table](std::uint8_t i, std::uint8_t j) {
//                if (table.strikes_cnts[i][j] == 0) {
//                    --table.free_cnt;
//                    auto it = table.free_ceils.find(i);
//                    if (it != table.free_ceils.end()) {
//                        it->second.erase(j);
//                        if (it->second.empty())
//                            table.free_ceils.erase(it);
//                    }
//                }
//                ++table.strikes_cnts[i][j];
//            });
//    return {start_i, start_j};
//}

//void ReverseChanges(OneTable &table, std::uint8_t N, std::pair<std::uint8_t, std::uint8_t> changes) {
//    auto start_i = changes.first, start_j = changes.second;
//    table.queue_positons[start_i] = 0;
//    --table.queen_cnts;
//    --table.strikes_cnts[start_i][start_j];
//    ++table.free_cnt;
//    auto temp_it = table.free_ceils.find(start_i);
//    if (temp_it == table.free_ceils.end())
//        table.free_ceils.emplace(start_i, std::unordered_set<std::uint8_t>{start_j});
//    else temp_it->second.emplace(start_j);
//    IterateAllStrikePositions(
//            start_i, start_j, N,
//            [&table](std::uint8_t i, std::uint8_t j) {
//                if (table.strikes_cnts[i][j] == 1) {
//                    ++table.free_cnt;
//                    auto it = table.free_ceils.find(i);
//                    if (it == table.free_ceils.end()) table.free_ceils.emplace(i, std::unordered_set<std::uint8_t>{j});
//                    else it->second.emplace(j);
//                }
//                --table.strikes_cnts[i][j];
//            });
//}
//
//bool RecSol(std::uint8_t now_ready, std::uint8_t N, OneTable &table) {
//    if (now_ready == N) return true;
//    if (table.free_cnt == 0) return false;
//    for (std::uint8_t i = 0; i < N - now_ready; ++i) {
//        auto changes = MiniChange(table, N);
//        if (RecSol(now_ready + 1, N, table)) return true;
//        ReverseChanges(table, N, changes);
//    }
//    return false;
//}
//
//std::vector<std::uint8_t> RecSolForInp(std::uint8_t N) {
//    OneTable table(N);
//    RecSol(0, N, table);
//    return table.queue_positons;
//}

//std::vector<std::uint16_t> GetMinFreeForQueenCnt(std::uint8_t N) {
//    std::vector<std::uint16_t> results(N);
//    long double a = -0.000028, b = 0.015806, c = -3.026342, d = 199.354983;
//    for (std::uint32_t i = 0; i < N; ++i) {
//        if (i == 0) results[i] = N * N;
//        else {
//            long double x = static_cast<long double>(200) / static_cast<long double>(N) * static_cast<long double>(i);
//            long double y = a * std::pow(x, 3.0) + b * std::pow(x, 2.0) + c * x + d;
//            y = y / (static_cast<long double>(200) / std::pow(static_cast<long double>(N), 2));
//            results[i] = static_cast<std::uint16_t>(std::max<long double>(0, y - 250));
//        }
//    }
//    return results;
//}

//std::vector<std::uint8_t> GetSolForThisInput(std::uint8_t N) {
//    std::vector<OneTable> tables(65, OneTable(N));
////    std::vector<std::uint16_t> min_free_for_queen_cnt = GetMinFreeForQueenCnt(N);
//    std::int16_t pre_queen_cnt = -1;
//    std::vector<std::uint32_t> free_on_queen_cnt(N);
//    while (tables.front().queen_cnts < N) {
//        if (pre_queen_cnt == tables.front().queen_cnts) {
//            tables.clear();
//            tables.resize(65, OneTable(N));
//            pre_queen_cnt = -1;
////            std::cout << "asdasd";
//            continue;
//        } else pre_queen_cnt = tables.front().queen_cnts;
//        free_on_queen_cnt[tables.front().queen_cnts] = tables.front().free_cnt;
//        for (std::uint32_t i = 0; i < 15; ++i) {
//            if (tables[i].free_cnt == 0) continue;
//            for (std::uint32_t j = 15 + i * 3; j < 15 + (i + 1) * 3; ++j) {
//                tables[j] = tables[i];
//                MiniChange(tables[j], N);
//            }
//        }
//        std::nth_element(tables.begin(), std::next(tables.begin(), 15), tables.end());
//        std::sort(tables.begin(), std::next(tables.begin(), 15));
////        std::sort(tables.begin(), std::next(tables.begin(), 2));
//    }
//    std::ofstream o_f(std::string("out_") + std::to_string(N) + ".txt");
//    for (const auto &r: free_on_queen_cnt) o_f << r << "\n";
//    o_f.close();
//    return tables.front().queue_positons;
//}

//bool
//RecSol(std::uint8_t ready, std::uint8_t N, std::vector<std::vector<std::uint8_t>> &steps,
//       std::vector<std::uint16_t> &free_on_queen_cnt,
//       std::vector<std::vector<uint8_t>> &table, std::vector<std::uint8_t> &res, std::uint16_t &free_count) {
//    if (ready == N) return true;
//    if (free_count < free_on_queen_cnt[ready]) return false;
//    std::shuffle(steps[ready].begin(), steps[ready].end(), Random::rng);
//    for (std::uint8_t ss_i = 0, i = steps[ready][i]; ss_i < N; ++ss_i, i = steps[ready][i]) {
//        if (table[ready][i] != 0) continue;
//        --free_count;
//        for (std::int16_t now_i = ready, now_j = i; now_i < N && now_j >= 0; ++now_i, --now_j) {
//            if (table[now_i][now_j] == 0 && (now_i != ready || now_j != i)) --free_count;
//            ++table[now_i][now_j];
//        }
//        for (std::int16_t now_i = ready, now_j = i; now_i < N && now_j < N; ++now_i, ++now_j) {
//            if (table[now_i][now_j] == 0 && (now_i != ready || now_j != i)) --free_count;
//            ++table[now_i][now_j];
//        }
//        for (std::int16_t now_i = ready, now_j = i; now_i < N; ++now_i) {
//            if (table[now_i][now_j] == 0 && (now_i != ready || now_j != i)) --free_count;
//            ++table[now_i][now_j];
//        }
//        table[ready][i] -= 2;
//        if (RecSol(ready + 1, N, steps, free_on_queen_cnt, table, res, free_count)) {
//            res[ready] = i;
//            return true;
//        }
//        table[ready][i] += 2;
//        for (std::int16_t now_i = ready, now_j = i; now_i < N && now_j >= 0; ++now_i, --now_j) {
//            --table[now_i][now_j];
//            if (table[now_i][now_j] == 0 && (now_i != ready || now_j != i)) ++free_count;
//        };
//        for (std::int16_t now_i = ready, now_j = i; now_i < N && now_j < N; ++now_i, ++now_j) {
//            --table[now_i][now_j];
//            if (table[now_i][now_j] == 0 && (now_i != ready || now_j != i)) ++free_count;
//        }
//        for (std::int16_t now_i = ready, now_j = i; now_i < N; ++now_i) {
//            --table[now_i][now_j];
//            if (table[now_i][now_j] == 0 && (now_i != ready || now_j != i)) ++free_count;
//        }
//        ++free_count;
//    }
//    return false;
//}
//
//std::vector<std::uint8_t> GetSolRec(std::uint8_t N) {
//    std::vector<std::uint16_t> free_on_queen_cnt = GetMinFreeForQueenCnt(N);
//    std::vector<std::vector<uint8_t>> table(N, std::vector<std::uint8_t>(N, 0));
//    std::vector<std::uint8_t> res(N, 0);
//    std::vector<std::uint8_t> temp(N, 0);
//    std::iota(temp.begin(), temp.end(), 0);
//    std::vector<std::vector<std::uint8_t>> steps(N, temp);
//    std::uint16_t free_count = N * N;
////    for(auto&&rr:steps)
////        std::shuffle(rr.begin(), rr.end(), Random::rng);
//    RecSol(0, N, steps, free_on_queen_cnt, table, res, free_count);
//    return res;
//}
//
//void BeautifulPrintRes(const std::vector<std::uint8_t> &res) {
//    for (std::uint32_t i = 0; i < res.size(); ++i) {
//        for (std::uint32_t j = 0; j < res.size(); ++j)
//            std::cout << (j == res[i] ? 'X' : '_');
//        std::cout << "\n";
//    }
//}
//
//void IterateAllStrikePositions(std::uint32_t start_i, std::uint32_t start_j, std::uint32_t N,
//                               const std::function<void(std::uint32_t, std::uint32_t)> &function) {
//    for (std::uint32_t i = 0, j = start_j; i < N; ++i) if (i != start_i) function(i, j);
//    for (std::uint32_t i = start_i, j = 0; j < N; ++j) if (j != start_j) function(i, j);
//    for (auto i = static_cast<std::int32_t>(start_i), j = static_cast<std::int32_t>(start_j);
//         i >= 0 && j >= 0; --i, --j)
//        if (i != start_i || j != start_j)
//            function(i, j);
//    for (auto i = static_cast<std::int32_t>(start_i), j = static_cast<std::int32_t>(start_j);
//         i >= 0 && j < N; --i, ++j)
//        if (i != start_i || j != start_j)
//            function(i, j);
//    for (auto i = static_cast<std::int32_t>(start_i), j = static_cast<std::int32_t>(start_j);
//         i < N && j >= 0; ++i, --j)
//        if (i != start_i || j != start_j)
//            function(i, j);
//    for (auto i = static_cast<std::int32_t>(start_i), j = static_cast<std::int32_t>(start_j);
//         i < N && j < N; ++i, ++j)
//        if (i != start_i || j != start_j)
//            function(i, j);
//}
//
//bool IsOk(const std::vector<std::uint8_t> &res) {
//    std::vector<std::vector<char>> table(res.size(), std::vector<char>(res.size(), '0'));
//    for (std::uint32_t i = 0; i < res.size(); ++i) {
//        table[i][res[i]] = '2';
//        bool is_ok = true;
//        IterateAllStrikePositions(i, res[i], res.size(), [&table, &is_ok](std::uint32_t i, std::uint32_t j) {
//            if (table[i][j] == '2') is_ok = false;
//            table[i][j] = '1';
//        });
//        if (!is_ok) return false;
//    }
//    return true;
//}

#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <unordered_set>
#include <functional>

namespace Random {
    std::random_device dev;
    std::uint32_t seed = dev();
//    std::uint32_t seed = 1337866407;
    std::mt19937 rng(seed);

    std::uint32_t GetRandom32(std::uint32_t from, std::uint32_t to) {
        return std::uniform_int_distribution<std::uint32_t>(from, to)(rng);
    }

    std::uint8_t GetRandom8(std::uint8_t from, std::uint8_t to) {
        return std::uniform_int_distribution<std::uint8_t>(from, to)(rng);
    }
};


struct OneTable {
    std::vector<std::vector<std::uint8_t>> strikes_cnts;
    std::vector<std::uint8_t> rows_free_cnts;
    std::unordered_set<std::uint8_t> rows_that_have_free_ceils;
    std::vector<std::uint8_t> queue_positons;
    std::uint8_t queen_cnts;
    std::uint32_t free_cnt;

    explicit OneTable(std::uint8_t N) : strikes_cnts(N, std::vector<std::uint8_t>(N, 0)),
                                        rows_free_cnts(N, N), queen_cnts(0),
                                        free_cnt(N * N), queue_positons(N, 0) {
        for (std::uint8_t i = 0; i < N; ++i) rows_that_have_free_ceils.emplace(i);
    }

    friend void swap(OneTable &a, OneTable &b) {
        using std::swap;
        swap(a.strikes_cnts, b.strikes_cnts);
        swap(a.rows_free_cnts, b.rows_free_cnts);
        swap(a.rows_that_have_free_ceils, b.rows_that_have_free_ceils);
        swap(a.queue_positons, b.queue_positons);
        swap(a.queen_cnts, b.queen_cnts);
        swap(a.free_cnt, b.free_cnt);
    }

    bool operator<(const OneTable &other) const {
        if (queen_cnts != other.queen_cnts) return queen_cnts > other.queen_cnts;
        return free_cnt > other.free_cnt;
    }

    OneTable &operator=(const OneTable &other) = default;

    OneTable(const OneTable &other) = default;

    OneTable(OneTable &&other) noexcept: strikes_cnts(std::move(other.strikes_cnts)),
                                         rows_free_cnts(std::move(other.rows_free_cnts)),
                                         rows_that_have_free_ceils(std::move(other.rows_that_have_free_ceils)),
                                         queue_positons(std::move(other.queue_positons)),
                                         queen_cnts(other.queen_cnts), free_cnt(other.free_cnt) {
        other.free_cnt = other.queen_cnts = 0;
    }
};

void IterateAllStrikePositions(std::uint32_t start_i, std::uint32_t start_j, std::uint32_t N,
                               const std::function<void(std::uint32_t, std::uint32_t)> &function) {
    for (std::uint32_t i = 0, j = start_j; i < N; ++i) if (i != start_i) function(i, j);
    for (std::uint32_t i = start_i, j = 0; j < N; ++j) if (j != start_j) function(i, j);
    for (auto i = static_cast<std::int32_t>(start_i), j = static_cast<std::int32_t>(start_j);
         i >= 0 && j >= 0; --i, --j)
        if (i != start_i || j != start_j)
            function(i, j);
    for (auto i = static_cast<std::int32_t>(start_i), j = static_cast<std::int32_t>(start_j);
         i >= 0 && j < N; --i, ++j)
        if (i != start_i || j != start_j)
            function(i, j);
    for (auto i = static_cast<std::int32_t>(start_i), j = static_cast<std::int32_t>(start_j);
         i < N && j >= 0; ++i, --j)
        if (i != start_i || j != start_j)
            function(i, j);
    for (auto i = static_cast<std::int32_t>(start_i), j = static_cast<std::int32_t>(start_j);
         i < N && j < N; ++i, ++j)
        if (i != start_i || j != start_j)
            function(i, j);
}

bool IsOk(const std::vector<std::uint8_t> &res) {
    std::vector<std::vector<char>> table(res.size(), std::vector<char>(res.size(), '0'));
    for (std::uint32_t i = 0; i < res.size(); ++i) {
        table[i][res[i]] = '2';
        bool is_ok = true;
        IterateAllStrikePositions(i, res[i], res.size(), [&table, &is_ok](std::uint32_t i, std::uint32_t j) {
            if (table[i][j] == '2') is_ok = false;
            table[i][j] = '1';
        });
        if (!is_ok) return false;
    }
    return true;
}

std::pair<std::uint8_t, std::uint8_t> MiniChange(OneTable &table, std::uint8_t N) {
    if (table.free_cnt == 0) return {0, 0};
    auto start_i = *std::next(table.rows_that_have_free_ceils.begin(),
                              Random::GetRandom8(0, table.rows_that_have_free_ceils.size() - 1));
    auto temp_s_j = Random::GetRandom8(0, table.rows_free_cnts[start_i] - 1);
    std::uint8_t start_j;
    for (std::uint8_t i = 0, i_n = 0; i < N; ++i) {
        if (table.strikes_cnts[start_i][i] == 0) {
            if (i_n == temp_s_j) {
                start_j = i;
                break;
            } else ++i_n;
        }
    }
    table.queue_positons[start_i] = start_j;
    ++table.queen_cnts;
    ++table.strikes_cnts[start_i][start_j];
    --table.rows_free_cnts[start_i];
    table.rows_that_have_free_ceils.erase(start_i);
    --table.free_cnt;
    IterateAllStrikePositions(
            start_i, start_j, N,
            [&table](std::uint8_t i, std::uint8_t j) {
                if (table.strikes_cnts[i][j] == 0) {
                    --table.free_cnt;
                    --table.rows_free_cnts[i];
                    if (table.rows_free_cnts[i] == 0) table.rows_that_have_free_ceils.erase(i);
                }
                ++table.strikes_cnts[i][j];
            });
    return {start_i, start_j};
}

std::vector<std::uint8_t> GetSolForThisInput(std::uint8_t N) {
    std::vector<OneTable> tables(65, OneTable(N));
//    std::vector<std::uint16_t> min_free_for_queen_cnt = GetMinFreeForQueenCnt(N);
    std::int16_t pre_queen_cnt = -1;
    std::vector<std::uint32_t> free_on_queen_cnt(N);
    while (tables.front().queen_cnts < N) {
        if (pre_queen_cnt == tables.front().queen_cnts) {
            tables.clear();
            tables.resize(65, OneTable(N));
            pre_queen_cnt = -1;
//            std::cout << "asdasd";
            continue;
        } else pre_queen_cnt = tables.front().queen_cnts;
        free_on_queen_cnt[tables.front().queen_cnts] = tables.front().free_cnt;
        for (std::uint32_t i = 0; i < 15; ++i) {
            if (tables[i].free_cnt == 0) continue;
            for (std::uint32_t j = 15 + i * 3; j < 15 + (i + 1) * 3; ++j) {
                tables[j] = tables[i];
                MiniChange(tables[j], N);
            }
        }
        std::nth_element(tables.begin(), std::next(tables.begin(), 15), tables.end());
        std::sort(tables.begin(), std::next(tables.begin(), 15));
//        std::sort(tables.begin(), std::next(tables.begin(), 2));
    }
    return tables.front().queue_positons;
}

int main() {
//    std::cout << "seed: " << Random::seed << "\n";
    std::uint32_t N;
    std::cin >> N;
//    auto start_time = std::chrono::steady_clock::now();
    auto res = GetSolForThisInput(N);
//    std::cout << "\n" << std::chrono::duration_cast<std::chrono::milliseconds>(
//            std::chrono::steady_clock::now() - start_time).count() << "\n\n";
//    for (std::uint32_t i = 5; i <= 200; ++i) {
//        std::cout << i << ": " << IsOk(res) << "\n";
//    }
//    BeautifulPrintRes(res);
//    if (N == 4) std::cout << "3 1 4 2";
    /*else*/ for (const auto &r: res) std::cout << static_cast<std::uint32_t>(r) + 1 << " ";
//    std::cout << "\n" << IsOk(res);
    return 0;
}