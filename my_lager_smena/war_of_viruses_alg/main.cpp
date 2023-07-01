//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("vpt")
//#pragma GCC optimize("rename-registers")
//#pragma GCC optimize("move-loop-invariants")
//#pragma GCC optimize("unswitch-loops")
//#pragma GCC optimize(3)
//#pragma GCC optimize("O3")
//#pragma GCC optimize("inline")
//#pragma GCC optimize("-fgcse")
//#pragma GCC optimize("-fgcse-lm")
//#pragma GCC optimize("-fipa-sra")
//#pragma GCC optimize("-ftree-pre")
//#pragma GCC optimize("-ftree-vrp")
//#pragma GCC optimize("-fpeephole2")
//#pragma GCC optimize("-fsched-spec")
//#pragma GCC optimize("-falign-jumps")
//#pragma GCC optimize("-falign-loops")
//#pragma GCC optimize("-falign-labels")
//#pragma GCC optimize("-fdevirtualize")
//#pragma GCC optimize("-fcaller-saves")
//#pragma GCC optimize("-fcrossjumping")
//#pragma GCC optimize("-fthread-jumps")
//#pragma GCC optimize("-freorder-blocks")
//#pragma GCC optimize("-fschedule-insns")
//#pragma GCC optimize("inline-functions")
//#pragma GCC optimize("-ftree-tail-merge")
//#pragma GCC optimize("-fschedule-insns2")
//#pragma GCC optimize("-fstrict-aliasing")
//#pragma GCC optimize("-falign-functions")
//#pragma GCC optimize("-fcse-follow-jumps")
//#pragma GCC optimize("-fsched-interblock")
//#pragma GCC optimize("-fpartial-inlining")
//#pragma GCC optimize("-freorder-functions")
//#pragma GCC optimize("-findirect-inlining")
//#pragma GCC optimize("-fhoist-adjacent-loads")
//#pragma GCC optimize("-frerun-cse-after-loop")
//#pragma GCC optimize("inline-small-functions")
//#pragma GCC optimize("-finline-small-functions")
//#pragma GCC optimize("-ftree-switch-conversion")
//#pragma GCC optimize("-foptimize-sibling-calls")
//#pragma GCC optimize("-fexpensive-optimizations")
//#pragma GCC optimize("inline-functions-called-once")
//#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <random>
#include <functional>
#include <chrono>

namespace Utils {
//    template<typename T>
//    class FastQueue {
//    public:
//        std::vector<T> in_queue;
//        std::uint32_t left, right;
//        T get()
//
//        explicit FastQueue(std::uint32_t max_size) : in_queue(max_size), left(0), right(0) {}
//    };

    class FastBoolArray {
        const static std::uint16_t last_6_bits = ~(~0u << 6u);
    public:
        std::vector<std::uint64_t> arr;

        [[nodiscard]] inline bool GetValue(std::uint32_t id) const {
            return (arr[id >> 6u] >> (id & last_6_bits)) & 1u;
        }

        inline void SetToTrue(std::uint32_t id) {
            arr[id >> 6u] |= (1ull << (id & last_6_bits));
        }

        inline void SetToFalse(std::uint32_t id) {
            arr[id >> 6u] &= ~(1ull << (id & last_6_bits));
        }

        inline void SetAllToFalse() {
            std::fill(arr.begin(), arr.end(), 0u);
        }

        explicit FastBoolArray(std::uint32_t size) : arr((size >> 6u) + 1u, 0u) {}
    };

    inline std::uint32_t ZipCoordsToNum(std::uint16_t i, std::uint16_t j) {
        return (static_cast<std::uint32_t>(i) << 9u) | j;
    }

    const std::uint16_t last_9_bits = ~(~0u << 9u);

    inline std::uint16_t GetFirstCoord(std::uint32_t num) {
        return num >> 9u;
    }

    inline std::uint16_t GetSecondCoord(std::uint32_t num) {
        return num & last_9_bits;
    }

    inline std::pair<std::uint16_t, std::uint16_t> UnzipCoordsFromNum(std::uint32_t num) {
        return {num >> 9u, num & last_9_bits};
    }

    template<typename T>
    inline T square(T a) { return a * a; }

    template<typename T>
    double
    root_square_mean(typename std::vector<T>::const_iterator first, typename std::vector<T>::const_iterator last,
                     const std::function<double(const T &)> &f) {
        double squares_sum = 0;
        for (auto it = first; it != last; ++it) squares_sum += square(f(*it));
        return std::sqrt(squares_sum / std::distance(first, last));
    }
}

namespace NormalIO {
    std::string temp_str;

    void FastReadWordSmallAlpha(std::string &str) {
        str.clear();
        str.reserve(8);
        auto ch = getchar();
        while (ch < 'a' || ch > 'z') ch = getchar();
        for (; ch >= 'a' && ch <= 'z'; ch = getchar()) str.push_back(static_cast<char>(ch));
    }

    template<typename T>
    T FastReadNum() {
        T res = 0;
        auto ch = getchar();
        while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
        bool minus = ch == '-';
        if (minus) ch = getchar();
        for (; ch >= '0' && ch <= '9'; ch = getchar()) {
            res *= 10;
            res += ch - '0';
        }
        if (minus) return -res;
        return res;
    }

    bool NewTableInput(std::vector<std::int8_t> &table, std::uint16_t K, bool read_word = true) {
        if (read_word) {
            FastReadWordSmallAlpha(temp_str);
            if (temp_str == "o") return true;
        }
        for (std::uint16_t i = 0, c_1, c_2; i < K - 1; ++i) {
            auto t_p_id = FastReadNum<std::int8_t>();
            auto cnt = FastReadNum<std::uint8_t>();
            for (std::uint8_t j = 0; j < cnt; ++j) {
                c_1 = FastReadNum<std::uint16_t>() - 1;
                c_2 = FastReadNum<std::uint16_t>() - 1;
                auto coords = Utils::ZipCoordsToNum(c_1, c_2);
                if (table[coords] == 0) table[coords] = t_p_id + 10;
                else if (table[coords] == 1 || table[coords] >= 10) table[coords] = -t_p_id - 10;
            }
        }
        return false;
    }

    void
    StartInput(std::vector<std::int8_t> &table, std::uint16_t &N, std::uint16_t &M, std::uint16_t &K,
               std::uint16_t &player_id) {
        N = FastReadNum<std::uint16_t>();
        M = FastReadNum<std::uint16_t>();
        K = FastReadNum<std::uint16_t>();
        player_id = FastReadNum<std::uint16_t>();
        table.clear();
        table.resize(Utils::ZipCoordsToNum(N, M) + 1);
        table.shrink_to_fit();
        for (std::uint16_t i = 0; i < N; ++i) {
            for (std::uint16_t j = 0; j < M; ++j) {
                auto t_n = FastReadNum<std::int8_t>();
                if (t_n > 0) {
                    if (t_n == player_id) table[Utils::ZipCoordsToNum(i, j)] = 1;
                    else table[Utils::ZipCoordsToNum(i, j)] = t_n + 10;
                } else if (t_n < 0) {
                    if (t_n == -100) table[Utils::ZipCoordsToNum(i, j)] = -100;
                    else {
                        if (-t_n == player_id) table[Utils::ZipCoordsToNum(i, j)] = 2;
                        else table[Utils::ZipCoordsToNum(i, j)] = t_n - 10;
                    }
                }
            }
        }
    }

    void AfterStepOut(std::uint32_t player_id, const std::vector<std::uint32_t> &doings) {
        std::cout << player_id << " " << doings.size() << " ";
        for (const auto &do_zip: doings) {
            auto [do_x, do_y] = Utils::UnzipCoordsFromNum(do_zip);
            std::cout << do_x + 1 << " " << do_y + 1 << " ";
        }
        std::cout << std::endl;
        std::cout.flush();
    }
}

namespace Random {
    std::random_device dev;
    std::uint32_t seed = dev();
//    std::uint32_t seed = 1111;
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist_00_06(0, 0.4);

    inline bool GetRandBool(float prob) { return std::bernoulli_distribution(prob)(rng); }

    inline double GetRandom00To06() { return dist_00_06(rng); }
//    inline double GetRandom00To06() { return 0; }
}

namespace MySolution {
    class DSU {
    public:
        Utils::FastBoolArray used;
        std::vector<std::uint32_t> parent;
        std::vector<std::uint32_t> size;
        Utils::FastBoolArray life_exists;

//        std::uint32_t get_set_size(std::uint32_t v) {
//            auto a = find_set(v);
//            if (a == 1e9) return 0;
//            return size[a];
//        }

        bool is_set_life_exists(std::uint32_t v) {
            if (!used.GetValue(v)) return false;
            auto a = find_set(v);
            if (a == 1e9) return false;
            return life_exists.GetValue(a);
        }

        void make_set(std::uint32_t v, bool t_life_exists) {
            parent[v] = v;
            size[v] = 1;
            used.SetToTrue(v);
            if (t_life_exists) life_exists.SetToTrue(v);
        }

        std::uint32_t find_set(std::uint32_t v) {
            if (!used.GetValue(v)) return 1e9;
            if (parent[v] == 1e9) return 1e9;
            if (parent[v] == v) return v;
            return parent[v] = find_set(parent[v]);
        }

        void union_sets(std::uint32_t a, std::uint32_t b) {
            a = find_set(a);
            b = find_set(b);
            if (!used.GetValue(a) || !used.GetValue(b)) return;
            if (a == 1e9 || b == 1e9) return;
            if (a != b) {
                if (size[a] < size[b]) std::swap(a, b);
                parent[b] = a;
                size[a] += size[b];
                if (life_exists.GetValue(a) || life_exists.GetValue(b))
                    life_exists.SetToTrue(a);
            }
        }

        void clear() {
            used.SetAllToFalse();
            life_exists.SetAllToFalse();
        }

        explicit DSU(std::uint32_t max_el) : parent(max_el + 1, 1e9), size(max_el + 1, 0),
                                             life_exists(max_el + 1), used(max_el + 1) {}
    };

    enum class Direction : std::uint8_t {
        left = 0,
        left_top = 1,
        top = 2,
        top_right = 3,
        right = 4,
        right_bottom = 5,
        bottom = 6,
        bottom_left = 7
    };

    bool IsDirectionOk(std::uint32_t coord, std::uint16_t N, std::uint16_t M,
                       Direction dir) {
        if (dir == Direction::left) return Utils::GetSecondCoord(coord) > 0;
        if (dir == Direction::left_top) return Utils::GetFirstCoord(coord) > 0 && Utils::GetSecondCoord(coord) > 0;
        if (dir == Direction::top) return Utils::GetFirstCoord(coord) > 0;
        if (dir == Direction::top_right) return Utils::GetFirstCoord(coord) > 0 && Utils::GetSecondCoord(coord) + 1 < M;
        if (dir == Direction::right) return Utils::GetSecondCoord(coord) + 1 < M;
        if (dir == Direction::right_bottom)
            return Utils::GetFirstCoord(coord) + 1 < N && Utils::GetSecondCoord(coord) + 1 < M;
        if (dir == Direction::bottom) return Utils::GetFirstCoord(coord) + 1 < N;
        return Utils::GetFirstCoord(coord) + 1 < N && Utils::GetSecondCoord(coord) > 0;
    }

    std::uint32_t ChangeCoordsToDir(std::uint32_t coord, Direction dir) {
        if (dir == Direction::left)
            return Utils::ZipCoordsToNum(Utils::GetFirstCoord(coord), Utils::GetSecondCoord(coord) - 1);
        if (dir == Direction::left_top)
            return Utils::ZipCoordsToNum(Utils::GetFirstCoord(coord) - 1, Utils::GetSecondCoord(coord) - 1);
        if (dir == Direction::top)
            return Utils::ZipCoordsToNum(Utils::GetFirstCoord(coord) - 1, Utils::GetSecondCoord(coord));
        if (dir == Direction::top_right)
            return Utils::ZipCoordsToNum(Utils::GetFirstCoord(coord) - 1, Utils::GetSecondCoord(coord) + 1);
        if (dir == Direction::right)
            return Utils::ZipCoordsToNum(Utils::GetFirstCoord(coord), Utils::GetSecondCoord(coord) + 1);
        if (dir == Direction::right_bottom)
            return Utils::ZipCoordsToNum(Utils::GetFirstCoord(coord) + 1, Utils::GetSecondCoord(coord) + 1);
        if (dir == Direction::bottom)
            return Utils::ZipCoordsToNum(Utils::GetFirstCoord(coord) + 1, Utils::GetSecondCoord(coord));
        return Utils::ZipCoordsToNum(Utils::GetFirstCoord(coord) + 1, Utils::GetSecondCoord(coord) - 1);
    }

    void MakeConnectComp(std::vector<std::int8_t> &table, std::uint16_t N, std::uint16_t M,
                         DSU &dsu) {
        dsu.clear();
        for (std::uint16_t i = 0; i < N; ++i) {
            for (std::uint16_t j = 0; j < M; ++j) {
                auto coords = Utils::ZipCoordsToNum(i, j);
                if (table[coords] == 0 || table[coords] == -100) continue;
                for (std::uint8_t dir = 0; dir < 8; ++dir) {
                    if (!IsDirectionOk(coords, N, M, static_cast<Direction>(dir))) continue;
                    auto sec_coords = ChangeCoordsToDir(coords, static_cast<Direction>(dir));
                    auto &t_val = table[coords], &s_val = table[sec_coords];
                    if (s_val == 0 || s_val == -100) continue;
                    if ((std::abs(t_val) >= 10 || std::abs(s_val) >= 10) && std::abs(t_val) != std::abs(s_val))
                        continue;
                    std::uint32_t this_set = dsu.find_set(coords);
                    if (this_set == 1e9) {
                        dsu.make_set(coords, t_val == 1 || t_val >= 10);
                        this_set = dsu.find_set(coords);
                    }
                    std::uint32_t second_set = dsu.find_set(sec_coords);
                    if (second_set == 1e9) {
                        dsu.make_set(sec_coords, s_val == 1 || s_val >= 10);
                        second_set = dsu.find_set(sec_coords);
                    }
                    dsu.union_sets(this_set, second_set);
                }
            }
        }
    }

    struct BFSQueueElem {
        std::uint32_t coords, level;

        explicit BFSQueueElem(std::uint32_t coords, std::uint32_t level) : coords(coords), level(level) {}
    };

//    template<typename T>
//    void Reset2dArray(std::vector<std::vector<T>> &vec, std::uint16_t N, std::uint16_t M, const T &def_value) {
//        for (std::uint32_t i = 0; i < std::min<std::uint16_t>(N, vec.size()); ++i) {
//            std::fill(vec[i].begin(),
//                      std::next(vec[i].begin(), std::min<std::uint16_t>(M, vec[i].size())), def_value);
//            vec[i].resize(M, def_value);
//        }
//        if (vec.size() < N) vec.resize(N, std::vector<T>(M, def_value));
//    }

    inline bool CheckForBFS(const std::vector<std::int8_t> &table, DSU &dsu, std::uint32_t coords) {
        if (table[coords] == 2) return !dsu.is_set_life_exists(coords);
        return table[coords] == 0;
    }

    std::uint32_t
    BFSForMyCrest(std::uint16_t N, std::uint16_t M, std::uint32_t start_coords, std::queue<BFSQueueElem> &queue,
                  Utils::FastBoolArray &visited,
                  const std::vector<std::int8_t> &table) {
        std::uint32_t res = 0;
        visited.SetAllToFalse();
        queue.emplace(start_coords, 0);
        while (!queue.empty()) {
            auto [coords, level] = queue.front();
            queue.pop();
            if (visited.GetValue(coords) || level > 1) continue;
            visited.SetToTrue(coords);
            if (table[coords] == 1) ++res;
            if (table[coords] >= 10 || table[coords] < 0) continue;
            for (std::uint8_t dir = 0; dir < 8; ++dir) {
                if (!IsDirectionOk(coords, N, M, static_cast<Direction>(dir))) continue;
                auto sec_coords = ChangeCoordsToDir(coords, static_cast<Direction>(dir));
                if (!visited.GetValue(sec_coords) && level < 1) {
                    if (table[coords] == 1) queue.emplace(sec_coords, level + 1);
                    else if (table[coords] == 2) queue.emplace(sec_coords, level);
                }
            }
        }
        return res;
    }

    void BFS(std::uint16_t N, std::uint16_t M, std::queue<BFSQueueElem> &queue,
             Utils::FastBoolArray &visited, std::vector<std::int32_t> &dist,
             const std::vector<std::int8_t> &table, DSU &dsu) {
//        auto bfs_start_time = std::chrono::steady_clock::now();
        visited.SetAllToFalse();
        std::fill(dist.begin(), dist.end(), -1);
        // auto after_init = std::chrono::steady_clock::now();
//        std::cout << "bfs init time: "
//                  << std::chrono::duration_cast<std::chrono::milliseconds>(
//                          after_init - bfs_start_time).count() << "ms\n";
//        std::chrono::time_point<std::chrono::steady_clock> del_time;
        while (!queue.empty()) {
            // auto loop_start_time = std::chrono::steady_clock::now();
            auto [coords, level] = queue.front();
            queue.pop();
            // auto after_del = std::chrono::steady_clock::now();
            if (visited.GetValue(coords)) continue;
            visited.SetToTrue(coords);
            dist[coords] = level;
            if (!CheckForBFS(table, dsu, coords) && level != 0) continue;
            for (std::uint8_t dir = 0; dir < 8; ++dir) {
                if (!IsDirectionOk(coords, N, M, static_cast<Direction>(dir))) continue;
                auto sec_coords = ChangeCoordsToDir(coords, static_cast<Direction>(dir));
                if (!visited.GetValue(sec_coords)) queue.emplace(sec_coords, level + 1);
            }
        }
    }

    void
    SoftMax(std::vector<std::pair<double, std::uint32_t>> &vals, std::uint16_t n) {
        double sum = 0;
        for (std::uint32_t i = 0; i < n; ++i) {
            vals[i].first = std::exp(vals[i].first);
            sum += vals[i].first;
        }
        for (std::uint32_t i = 0; i < n; ++i) vals[i].first /= sum;
    }

//    double
//    FindMedian(std::vector<std::pair<double, std::pair<std::uint32_t, std::uint32_t>>> &a, std::uint32_t n) {
//        if (a.empty()) return 0;
//        auto t_cmp = [](const std::pair<double, std::pair<std::uint32_t, std::uint32_t>> &a,
//                        const std::pair<double, std::pair<std::uint32_t, std::uint32_t>> &b) {
//            return a.first < b.first;
//        };
//        if (n % 2 == 0) {
//            std::nth_element(a.begin(), a.begin() + n / 2, a.end(), t_cmp);
//            std::nth_element(a.begin(), a.begin() + (n - 1) / 2, a.end(), t_cmp);
//            return (a[(n - 1) / 2].first + a[n / 2].first) / 2;
//        } else {
//            std::nth_element(a.begin(), a.begin() + n / 2, a.end(), t_cmp);
//            return a[n / 2].first;
//        }
//    }

    inline bool MayPositionsCmpByProb(const std::pair<double, std::uint32_t> &a,
                                      const std::pair<double, std::uint32_t> &b) {
        return a.first < b.first;
    }

    void GetMaxNRandomDistributedIds(std::vector<std::pair<double, std::uint32_t>> &a,
                                     std::set<std::uint32_t> &need_ids, std::uint32_t size,
                                     std::uint32_t max_n_to_get) {
//        auto t_cmp = [](const std::pair<double, std::pair<std::uint16_t, std::uint16_t>> &a,
//                        const std::pair<double, std::pair<std::uint32_t, std::uint32_t>> &b) {
//            return a.first < b.first;
//        };
//        std::shuffle(a.begin(), a.end(), rng);
        std::sort(a.rbegin(), std::next(a.rbegin(), size), MayPositionsCmpByProb);
        need_ids.clear();
        for (std::uint32_t i = 0;
             i < 2 * max_n_to_get && need_ids.size() < max_n_to_get && need_ids.size() < size; ++i) {
            auto now_prob_val = Random::GetRandom00To06();
            for (std::uint32_t j = 0; j < size; ++j) {
                now_prob_val -= a[j].first;
                if (now_prob_val <= 0) {
                    need_ids.emplace(j);
                    break;
                }
            }
        }
    }

    void ApplyMyMoves(std::vector<std::int8_t> &table, const std::vector<std::uint32_t> &doings) {
        for (auto coords: doings) {
            if (table[coords] == 0) table[coords] = 1;
            else if (table[coords] >= 10) table[coords] = 2;
        }
    }


    void GetMaxNDoings(std::vector<std::int8_t> &table, std::uint16_t N, std::uint16_t M, std::uint16_t K,
                       std::uint16_t player_id, DSU &dsu,
                       std::vector<std::pair<double, std::uint32_t>> &probs_may_motion_poses,
                       std::queue<BFSQueueElem> &queue_my_linked_crep,
                       std::queue<BFSQueueElem> &queue_my_unlinked_crep, std::queue<BFSQueueElem> &queue_their_crest,
                       std::queue<BFSQueueElem> &queue_their_linked_crep,
                       std::queue<BFSQueueElem> &queue_their_unlinked_crep,
                       std::queue<BFSQueueElem> &queue_my_crest,
                       std::vector<std::int32_t> &dists_my_linked_crep,
                       std::vector<std::int32_t> &dists_my_unlinked_crep, std::vector<std::int32_t> &dists_their_crest,
                       std::vector<std::int32_t> &dists_their_linked_crep,
                       std::vector<std::int32_t> &dists_their_unlinked_crep,
                       std::vector<std::int32_t> &mul_cnt,
                       Utils::FastBoolArray &visited,
                       std::set<std::uint32_t> &motion_poses,
                       std::uint32_t max_n_doings, std::vector<std::uint32_t> &doings) {
        // auto start_cycle_time = std::chrono::steady_clock::now();
        MakeConnectComp(table, N, M, dsu);
        // auto after_con_map_time = std::chrono::steady_clock::now();
//            std::cout << "Making map connections time: "
//                      << std::chrono::duration_cast<std::chrono::milliseconds>(
//                              after_con_map_time - start_cycle_time).count() << "ms\n";
        std::uint32_t may_motion_pos_cnt = 0;
        for (std::uint16_t i = 0; i < N; ++i) {
            for (std::uint16_t j = 0; j < M; ++j) {
                auto coords = Utils::ZipCoordsToNum(i, j);
                if (table[coords] == 0 || table[coords] >= 10) {
                    for (std::uint8_t dir = 0; dir < 8; ++dir) {
                        if (!IsDirectionOk(coords, N, M, static_cast<Direction>(dir))) continue;
                        auto sec_coords = ChangeCoordsToDir(coords, static_cast<Direction>(dir));
                        if (table[sec_coords] == 1 ||
                            (table[sec_coords] == 2 && dsu.is_set_life_exists(sec_coords))) {
                            if (may_motion_pos_cnt < probs_may_motion_poses.size())
                                probs_may_motion_poses[may_motion_pos_cnt].second = coords;
                            else probs_may_motion_poses.emplace_back(0, coords);
                            ++may_motion_pos_cnt;
                            break;
                        }
                    }
                }
                if (table[coords] == 2) {
                    if (dsu.is_set_life_exists(coords)) queue_my_linked_crep.emplace(coords, 0);
                    else queue_my_unlinked_crep.emplace(coords, 0);
                }
                if (table[coords] >= 10)
                    queue_their_crest.emplace(coords, 0);
                if (table[coords] <= -10) {
                    if (dsu.is_set_life_exists(coords))
                        queue_their_linked_crep.emplace(coords, 0);
                    else
                        queue_their_unlinked_crep.emplace(coords, 0);
                }
            }
        }
        // auto after_queues_adding_map_time = std::chrono::steady_clock::now();
//            std::cout << "Queues adding time: "
//                      << std::chrono::duration_cast<std::chrono::milliseconds>(
//                              after_queues_adding_map_time - after_con_map_time).count() << "ms\n";
        BFS(N, M, queue_their_crest, visited, dists_their_crest, table, dsu);
        BFS(N, M, queue_their_unlinked_crep, visited, dists_their_unlinked_crep, table, dsu);
        BFS(N, M, queue_their_linked_crep, visited, dists_their_linked_crep, table, dsu);
        BFS(N, M, queue_my_unlinked_crep, visited, dists_my_unlinked_crep, table, dsu);
        BFS(N, M, queue_my_linked_crep, visited, dists_my_linked_crep, table, dsu);
        // auto after_bfs_time = std::chrono::steady_clock::now();
//            std::cout << "BFS-s time: "
//                      << std::chrono::duration_cast<std::chrono::milliseconds>(
//                              after_bfs_time - after_queues_adding_map_time).count() << "ms\n";
        for (std::uint32_t i = 0; i < may_motion_pos_cnt; ++i) {
            auto &[prob, coords] = probs_may_motion_poses[i];
            mul_cnt[coords] = 0;
            auto r = BFSForMyCrest(N, M, coords, queue_my_crest, visited, table);
            auto x = dists_my_unlinked_crep[coords];
            auto y = dists_their_crest[coords];
            auto z = dists_their_linked_crep[coords];
            auto k = dists_their_unlinked_crep[coords];
            auto p = dists_my_linked_crep[coords];
            probs_may_motion_poses[i].first = 0;
            if (r < 4) mul_cnt[coords] += 3;
            if (p <= 1 && y >= 1 && z >= 1 && Random::GetRandBool(0.1f)) ++mul_cnt[coords];
            if (x >= 0) probs_may_motion_poses[i].first -= x * 2;
            if (y >= 0) {
                if (y <= (N + M) / K / 2) probs_may_motion_poses[i].first -= y * 2;
                else probs_may_motion_poses[i].first -= y * 4;
            }
            if (z >= 0 || k >= 0) {
                if (z >= 0) probs_may_motion_poses[i].first += z * 2;
                if (k >= 0) probs_may_motion_poses[i].first += k;
            } else ++mul_cnt[coords];

        }
        double root_sc_mean = Utils::root_square_mean<std::pair<double, uint32_t>>
                (probs_may_motion_poses.begin(), std::next(probs_may_motion_poses.begin(), may_motion_pos_cnt),
                 [](const std::pair<double, uint32_t> &v) { return v.first; });
        for (std::uint32_t i = 0; i < may_motion_pos_cnt; ++i)
            probs_may_motion_poses[i].first += root_sc_mean * mul_cnt[probs_may_motion_poses[i].second];
        std::shuffle(probs_may_motion_poses.begin(), probs_may_motion_poses.end(), Random::rng);
        SoftMax(probs_may_motion_poses, may_motion_pos_cnt);
        GetMaxNRandomDistributedIds(probs_may_motion_poses, motion_poses, may_motion_pos_cnt, max_n_doings);
        doings.clear();
        doings.reserve(motion_poses.size());
        for (auto id: motion_poses) doings.emplace_back(probs_may_motion_poses[id].second);
        // auto after_counting = std::chrono::steady_clock::now();
//            std::cout << "counting time: "
//                      << std::chrono::duration_cast<std::chrono::milliseconds>(
//                              after_counting - after_bfs_time).count() << "ms\n";
    }

    void MainSol() {
        // auto f_s_time = std::chrono::steady_clock::now();
        std::vector<std::int8_t> table;
        std::uint16_t N, M, K, player_id;
        NormalIO::StartInput(table, N, M, K, player_id);
        // auto after_first_input_time = std::chrono::steady_clock::now();
//        std::cout << "First input time: "
//                  << std::chrono::duration_cast<std::chrono::milliseconds>(after_first_input_time - f_s_time).count()
//                  << "ms\n";
        Utils::FastBoolArray visited(Utils::ZipCoordsToNum(N, M) + 1),
                is_need_to_mul(Utils::ZipCoordsToNum(N, M) + 1),
                crep_visited_by_start(Utils::ZipCoordsToNum(N, M) + 1);
        std::queue<BFSQueueElem> queue_my_linked_crep, queue_my_unlinked_crep, queue_their_crest, queue_their_linked_crep, queue_their_unlinked_crep, queue_my_crest;
        std::vector<std::int32_t> dists_my_linked_crep(Utils::ZipCoordsToNum(N, M) + 1),
                dists_my_unlinked_crep(Utils::ZipCoordsToNum(N, M) + 1),
                dists_their_crest(Utils::ZipCoordsToNum(N, M) + 1),
                dists_their_linked_crep(Utils::ZipCoordsToNum(N, M) + 1),
                dists_their_unlinked_crep(Utils::ZipCoordsToNum(N, M) + 1),
                mul_cnt(Utils::ZipCoordsToNum(N, M) + 1);
        DSU dsu(Utils::ZipCoordsToNum(N, M) + 1);
//        std::vector<std::pair<std::uint32_t, std::uint32_t>> may_motion_pos;
//        std::vector<std::int32_t> not_softed_probs_may_motion_poses;
        std::vector<std::pair<double, std::uint32_t>> probs_may_motion_poses;
        std::set<std::uint32_t> motion_poses;
        probs_may_motion_poses.reserve(90000);
        std::vector<std::uint32_t> doings, full_doings;
        // auto after_first_init_time = std::chrono::steady_clock::now();
//        std::cout << "First init time: "
//                  << std::chrono::duration_cast<std::chrono::milliseconds>(
//                          after_first_init_time - after_first_input_time).count() << "ms\n";
        bool is_first = true;
        while (true) {
            full_doings.clear();
            for (std::uint32_t i = 0; i < 3 && full_doings.size() < 3; ++i) {
                GetMaxNDoings(table, N, M, K, player_id, dsu, probs_may_motion_poses, queue_my_linked_crep,
                              queue_my_unlinked_crep,
                              queue_their_crest, queue_their_linked_crep, queue_their_unlinked_crep, queue_my_crest,
                              dists_their_linked_crep, dists_my_unlinked_crep, dists_their_crest,
                              dists_their_linked_crep,
                              dists_their_unlinked_crep, mul_cnt, visited, motion_poses,
                              3 - full_doings.size(),
                              doings);
                full_doings.insert(full_doings.end(), doings.begin(), doings.end());
                ApplyMyMoves(table, doings);
            }
            NormalIO::AfterStepOut(player_id, full_doings);
            // auto after_out = std::chrono::steady_clock::now();
//            std::cout << "out time: "
//                      << std::chrono::duration_cast<std::chrono::milliseconds>(
//                              after_out - after_counting).count() << "ms\n";
            bool is_stop = NormalIO::NewTableInput(table, K);
            if (is_stop) break;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    MySolution::MainSol();
    return 0;
}

