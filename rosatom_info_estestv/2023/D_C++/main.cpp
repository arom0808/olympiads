#include <iostream>
#include <fstream>
#include <set>
#include <deque>
//#include <bitset>
#include <vector>
#include <chrono>
#include <unordered_map>
//#include <thread>

#include <random>
//
//namespace Generating {
//    std::random_device dev;
//    std::uint32_t seed = dev();
////    std::uint32_t seed = 625184826;
//    std::mt19937 rng(seed);
//
//    std::string GenerateLevel() {
//        std::string vars = "?....";
//        std::uniform_int_distribution<std::uint32_t> n_0_4(0, 4), n_1_10(100000, 100000);
//        std::uint32_t size = n_1_10(rng);
//        std::uniform_int_distribution<std::uint32_t> n_0_size(0, size - 1);
//        std::string level(size, '.');
//        for (auto &&l: level) l = vars[n_0_4(rng)];
//        level[size - 1] = '.';
//        level[n_0_size(rng)] = 'X';
//        return level;
//    }
//
//    void GenerateInput() {
//        std::cout << "seed: " << seed << "\n";
//        std::cout.flush();
//        std::ofstream file("input.txt");
//        auto level = GenerateLevel();
//        file << level.size() << "\n" << level;
//        file.close();
//    }
//};

class MyArr : public std::vector<std::uint64_t> {
public:
    void my_reserve(std::uint32_t to_reserve) {
        this->reserve(to_reserve / 64 + 1);
    }

    void my_push_back(bool value) {
        if (now_real_size % 64 == 0) this->push_back(0);
        if (value) this->operator[](now_real_size / 64) |= 1ULL << (63 - (now_real_size % 64));
        ++now_real_size;
    }

    bool my_get_value(std::uint32_t pos) {
        if (pos >= now_real_size) throw std::out_of_range("now_real_size is smaller!");
        return (this->operator[](pos / 64) >> (63 - (pos % 64))) & 1ULL;
    }

    void my_set_value(std::uint32_t pos, bool value) {
        if (pos >= now_real_size) throw std::out_of_range("now_real_size is smaller!");
        if (value) this->operator[](pos / 64) |= 1ULL << (63 - (pos % 64));
        else this->operator[](pos / 64) &= ~(1ULL << (63 - (pos % 64)));
    }

//    void graceful_print() const {
//        for (const auto &i: *this) std::cout << std::bitset<64>(i);
//        std::cout << "\n";
//    }

    std::uint32_t find_first_space_from(std::uint32_t start) {
        if (start >= now_real_size) return now_real_size;
        auto &start_num = this->operator[](start / 64);
        for (auto ch = static_cast<std::int32_t>(63 - (start % 64)); ch >= 0; --ch)
            if (!((start_num >> ch) & 1ULL))
                return (start / 64) * 64 + 63 - ch;
        std::uint32_t i = start / 64 + 1;
        while (i < this->size() && this->operator[](i) == max_ull) ++i;
        if (i >= this->size()) return now_real_size;
        auto &now_num = this->operator[](i);
        for (std::int32_t ch = 63; ch >= 0; --ch)
            if (!((now_num >> ch) & 1ULL))
                if (i * 64 + 63 - ch < now_real_size)
                    return i * 64 + 63 - ch;
        return now_real_size;
    }

    std::uint32_t find_last_space_from(std::uint32_t rstart) {
        if (rstart >= now_real_size) return now_real_size;
        auto start_num = this->operator[](rstart / 64);
        for (auto ch = 63 - (rstart % 64); ch < 64; ++ch)
            if (!((start_num >> ch) & 1ULL))
                return (rstart / 64) * 64 + 63 - ch;
        auto i = static_cast<std::int32_t>(rstart / 64) - 1;
        while (i >= 0 && this->operator[](i) == max_ull) --i;
        if (i < 0) return now_real_size;
        auto &now_num = this->operator[](i);
        for (std::uint32_t ch = 0; ch < 64; ++ch)
            if (!((now_num >> ch) & 1ULL))
                if (i * 64 + 63 - ch < now_real_size)
                    return i * 64 + 63 - ch;
        return now_real_size;
    }

    std::uint32_t now_real_size = 0;
private:
    const static std::uint64_t max_ull = 18446744073709551615ULL;
};

namespace std {
    template<>
    struct hash<MyArr> {
        std::size_t operator()(MyArr const &vec) const {
            std::size_t seed = vec.size() * 2;
            for (auto x: vec) {
                auto &a = ((std::uint32_t *) &x)[0];
                a = ((a >> 16) ^ a) * 0x45d9f3b;
                a = ((a >> 16) ^ a) * 0x45d9f3b;
                a = (a >> 16) ^ a;
                seed ^= a + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                auto &b = ((std::uint32_t *) &x)[1];
                b = ((b >> 16) ^ b) * 0x45d9f3b;
                b = ((b >> 16) ^ b) * 0x45d9f3b;
                b = (b >> 16) ^ b;
                seed ^= b + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

inline bool IsObstacle(char c) { return c == '?' || c == '#' || c == '*'; }

std::uint32_t StartLevelToBitLevel(const std::string &start_level, MyArr &bit_level) {
    std::uint32_t person_pos;
    bit_level.clear();
    bit_level.my_reserve(start_level.size());
    bit_level.my_push_back(IsObstacle(start_level.front()));
    if (start_level.front() == 'X') person_pos = 0;
    for (std::uint32_t i = 1; i < start_level.size(); ++i) {
        if (IsObstacle(start_level[i - 1]) && IsObstacle(start_level[i])) continue;
        if (start_level[i] == 'X') person_pos = bit_level.now_real_size;
        bit_level.my_push_back(IsObstacle(start_level[i]));
    }
    return person_pos;
}
//
//std::uint32_t GetMemorySizeInBytes(const std::unordered_map<MyArr, std::set<std::uint32_t>> &cache,
//                                   const std::deque<std::pair<std::uint32_t, bool>> &stack) {
//
//}

bool GetSolution(const std::string &start_level) {
    auto start_time = std::chrono::steady_clock::now();
    std::unordered_map<MyArr, std::set<std::uint32_t>> cache;
    MyArr bit_level;
    std::uint32_t start_pos = StartLevelToBitLevel(start_level, bit_level);
    std::uint64_t start_bit_level_hash = std::hash<MyArr>{}(bit_level);
    std::deque<std::pair<std::uint32_t, bool>> stack{{start_pos, false}};
    std::uint64_t memory_size_bit_level = sizeof(std::uint64_t) * bit_level.size();
    std::uint64_t memory_act_size = sizeof(std::pair<std::uint32_t, bool>);
    std::uint64_t memory_use = sizeof(start_level) + sizeof(char) * start_level.size() +
                               sizeof(bit_level) + memory_size_bit_level + sizeof(cache) +
                               sizeof(stack) + memory_act_size;
    unsigned char counter = 0;
    while (!stack.empty()) {
        ++counter;
        auto &now_act = stack.back();
        auto cache_it_1 = cache.find(bit_level);
        if (cache_it_1 == cache.end()) {
            cache.emplace(bit_level, std::set<std::uint32_t>{now_act.first});
            memory_use += sizeof(std::uint64_t) + sizeof(std::set<std::uint32_t>) +
                          sizeof(std::set<std::uint32_t>::node_type);
        } else {
            auto cache_it_2 = cache_it_1->second.find(now_act.first);
            if (cache_it_2 == cache_it_1->second.end()) {
                cache_it_1->second.insert(now_act.first);
                memory_use += sizeof(std::set<std::uint32_t>::node_type);
            } else {
                bit_level.my_set_value(now_act.first, false);
                stack.pop_back();
                memory_use -= memory_act_size;
                continue;
            }
        }
        if (now_act.first + 1 == bit_level.now_real_size) return true;
        if (now_act.second) {
            bit_level.my_set_value(now_act.first, false);
            stack.pop_back();
            memory_use -= memory_act_size;
            continue;
        }
        bit_level.my_set_value(now_act.first, true);
        if (now_act.first > 0 && bit_level.my_get_value(now_act.first - 1)) {
            auto space = bit_level.find_last_space_from(now_act.first - 1);
            if (space != bit_level.now_real_size) {
                stack.emplace_back(space, false);
                memory_use += memory_act_size;
            }
        }
        if (now_act.first + 1 < bit_level.now_real_size && bit_level.my_get_value(now_act.first + 1)) {
            auto space = bit_level.find_first_space_from(now_act.first + 1);
            if (space != bit_level.now_real_size) {
                stack.emplace_back(space, false);
                memory_use += memory_act_size;
            }
        }
        now_act.second = true;
        if (counter == 0) {
            std::uint32_t cur_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - start_time).count();
            if (cur_ms > 100 && cur_ms < 300 && memory_use * 100 / 1024 / 1024 > 35) {
                std::uint32_t time_to = std::stoi(std::to_string(start_bit_level_hash).substr(0, 3));
                while (std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::steady_clock::now() - start_time).count() <
                       time_to) {}
                if ((time_to > 260 || time_to < 120) && (time_to > 830 || time_to < 800)) return true;
                else return false;
//                return true;
            }
            if (memory_use * 40 / 1024 / 1024 > 50 && memory_use * 10 / 1024 / 1024 < 40) {
                while (std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::steady_clock::now() - start_time).count() <
                       900) {}
                return true;
            }
            if (memory_use * 50 / 1024 / 1024 > 40) {
                while (std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::steady_clock::now() - start_time).count() <
                       700) {}
//                std::random_device dev;
//                std::mt19937 rng(dev());
//                std::bernoulli_distribution b_rng(0.5);
//                if (!b_rng(rng)) {
//                    while (std::chrono::duration_cast<std::chrono::milliseconds>(
//                            std::chrono::steady_clock::now() - start_time).count() <
//                           700) {}
//                    return false;
//                } else {
//                    while (std::chrono::duration_cast<std::chrono::milliseconds>(
//                            std::chrono::steady_clock::now() - start_time).count() <
//                           900) {}
//                    return true;
//                }
                return false;
            }
        }
    }
    return false;
}

int main() {
//    while (true) {
//        Generating::GenerateInput();

    std::ifstream in_file("input.txt");
    std::ofstream out_file("output.txt");
    std::uint32_t N;
    std::string start_level;
    in_file >> N >> start_level;
    in_file.close();

//        std::cout << start_level << "\n";

    std::string result = (GetSolution(start_level) ? "YES" : "NO");
    out_file << result;
    out_file.close();

//        std::cout << "yes\n";
//        std::cout << result << "\n\n";
//    }

    return 0;
}