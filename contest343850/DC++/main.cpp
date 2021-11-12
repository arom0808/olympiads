#include <iostream>
#include <vector>

struct Town {
    std::uint32_t x = 0, y = 0;
    std::uint64_t c = 0, k = 0, cost = 0;
    bool elst = true;
    std::size_t el_from = 0;
};

void out(const std::vector<Town> &towns) {
    std::uint64_t cost = 0;
    std::vector<std::size_t> v = {};
    std::vector<std::pair<std::size_t, std::size_t>> connects = {};
    for (std::size_t i = 0; i < towns.size(); ++i) {
        if (towns[i].elst) {
            v.push_back(i+1);
        } else {
            connects.emplace_back(towns[i].el_from+1, i+1);
        }
        cost += towns[i].cost;
    }
    std::cout << cost << std::endl;
    std::cout << v.size() << std::endl;
    for (const auto &ve: v) {
        std::cout << ve << " ";
    }
    std::cout << std::endl;
    std::cout << connects.size();
    for (const auto &conn: connects) {
        std::cout << std::endl << conn.first << " " << conn.second;
    }
}

int main() {
    std::uint16_t n;
    std::vector<Town> towns;
    std::cin >> n;
    towns.resize(n);
    for (auto &town: towns) {
        std::cin >> town.x >> town.y;
    }
    for (auto &town: towns) {
        std::cin >> town.c;
        town.cost = town.c;
    }
    for (auto &town: towns) {
        std::cin >> town.k;
    }
    std::size_t min_elst = 0;
    for (std::size_t i = 0; i < towns.size(); ++i) {
        if (towns[i].c < towns[min_elst].c) {
            min_elst = i;
        }
    }
    std::uint64_t tmp;
    for (std::size_t i = 0; i < towns.size(); ++i) {
        if (i == min_elst)
            continue;
        tmp = (std::abs(static_cast<std::int32_t>(towns[min_elst].x) - static_cast<std::int32_t>(towns[i].x)) +
               std::abs(static_cast<std::int32_t>(towns[min_elst].y) - static_cast<std::int32_t>(towns[i].y))) *
              (towns[min_elst].k + towns[i].k);
        if (tmp < towns[i].cost) {
            towns[i].elst = false;
            towns[i].el_from = min_elst;
            towns[i].cost = tmp;
        }
    }
    out(towns);
    return 0;
}
