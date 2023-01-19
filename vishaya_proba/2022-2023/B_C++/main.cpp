#include <iostream>
#include <vector>
#include <map>

struct TownParam {
    std::uint32_t town_id;
    std::uint64_t money_count;

    TownParam(std::uint32_t town_id, const std::uint64_t &money_count) : town_id(town_id), money_count(money_count) {}

    bool operator<(const TownParam &other) const {
        if (town_id < other.town_id) return true;
        if (town_id == other.town_id) return money_count < other.money_count;
        return false;
    }
};

std::map<TownParam, std::int64_t> cache;

std::int64_t
DoConcert(const std::uint32_t &town_id, const std::vector<std::int32_t> &towns, std::uint32_t k,
          std::int64_t money_count) {
    if (town_id > towns.size()) return money_count;
    auto this_town_param = TownParam(town_id, money_count);
    auto cache_find = cache.find(this_town_param);
    if (cache_find != cache.end()) return (*cache_find).second;
    money_count += towns[town_id - 1];
    if (money_count < 0) return -1;
    std::int64_t max_finish_money = -1;
    for (std::uint32_t i = town_id + 1; i <= town_id + k; ++i)
        max_finish_money = std::max(max_finish_money, DoConcert(i, towns, k, money_count));
    cache.emplace(this_town_param, max_finish_money);
    return max_finish_money;
}

int main() {
    std::uint32_t n, k, p;
    std::cin >> n >> k >> p;
    std::vector<std::int32_t> towns(n);
    for (auto &&town: towns) std::cin >> town;
    std::int64_t max_finish_money = -1;
    for (std::uint32_t i = 1; i <= k; ++i)
        max_finish_money = std::max(max_finish_money, DoConcert(i, towns, k, p));
    if (k > n) max_finish_money = std::max(max_finish_money, static_cast<std::int64_t>(p));
    std::cout << max_finish_money;
    return 0;
}
