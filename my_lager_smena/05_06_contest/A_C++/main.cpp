#include <iostream>
#include <set>
#include <map>

std::set<std::uint64_t> cache;

std::uint64_t GetHash(std::multiset<std::pair<std::uint16_t, std::uint16_t>> &situation) {
    std::uint64_t seed = situation.size();
    for (auto p: situation) {
        std::uint32_t x = p.first;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;
        seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        x = p.second;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;
        seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

void AddToSituation(std::multiset<std::pair<std::uint16_t, std::uint16_t>> &situation,
                    std::uint32_t a, std::uint32_t b) {
    situation.emplace(a, b);
}

void DeleteFromSituation(std::multiset<std::pair<std::uint16_t, std::uint16_t>> &situation,
                         std::uint32_t a, std::uint32_t b) {
    auto it = situation.find({a, b});
    if (it != situation.end()) situation.erase(it);
}

std::uint32_t MyFunc(std::uint32_t a, std::uint32_t x, std::uint32_t b, std::uint32_t y, std::uint32_t z,
                     std::multiset<std::pair<std::uint16_t, std::uint16_t>> &situation) {
    if (a == 0 && b == 0) return 0;
    AddToSituation(situation, a, b);
    auto sit_hash = GetHash(situation);
    if (cache.find(sit_hash) != cache.end()) {
        DeleteFromSituation(situation, a, b);
        return 1e9;
    }
    cache.emplace(sit_hash);
    if (b == 0) {
        std::swap(a, b);
        std::swap(x, y);
    }
    if (a == 0) {
        auto in_one_cnt = z / y;
        auto full_in_one_rasp_cnt = z % y == 0 ? in_one_cnt - 1 : in_one_cnt;
        auto in_fulls_cnt = b / in_one_cnt;
        auto not_full_cnt = b - in_fulls_cnt * in_one_cnt;
        DeleteFromSituation(situation, a, b);
        return full_in_one_rasp_cnt * in_fulls_cnt + not_full_cnt;
    }
    std::uint32_t min_count = 1e9;
    for (std::uint32_t a_cnt = 0; a_cnt <= std::min(z / x, a); ++a_cnt) {
        std::uint32_t b_cnt = std::min((z - a_cnt * x) / y, b);
        std::uint32_t this_count = a_cnt + b_cnt;
        if (a_cnt * x + b_cnt * y == z) --this_count;
        this_count += MyFunc(a - a_cnt, x, b - b_cnt, y, z, situation);
        if (this_count < min_count) min_count = this_count;
    }
    DeleteFromSituation(situation, a, b);
    return min_count;
}

int main() {
    std::multiset<std::pair<std::uint16_t, std::uint16_t>> situation;
    std::uint32_t a, x, b, y, z;
    std::cin >> a >> x >> b >> y >> z;
    std::cout << MyFunc(a, x, b, y, z, situation);
    return 0;
}
