#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <random>
#include <chrono>
#include <algorithm>

namespace StupidSol {
    std::int64_t recursion_sol(const std::vector<std::pair<std::uint64_t, std::uint64_t>> &raw_works,
                               std::map<std::uint64_t, std::uint64_t> &now_status,
                               std::uint64_t work_id, std::uint64_t repairs) {
        if (work_id >= raw_works.size()) {
            if (!now_status.empty()) return -1;
            else return 0;
        }
        std::int64_t pre_value = -1;
        auto it1 = now_status.find(raw_works[work_id].second);
        if (it1 != now_status.end()) pre_value = it1->second;
        if (it1 == now_status.end()) now_status.emplace(raw_works[work_id].second, raw_works[work_id].first);
        std::int64_t res1 = recursion_sol(raw_works, now_status, work_id + 1, repairs);
        if (res1 != -1 && work_id + 1 < raw_works.size())
            res1 += now_status.size() * (raw_works[work_id + 1].first - raw_works[work_id].first);
        now_status.erase(raw_works[work_id].second);
        std::int64_t res2 = -1;
        if (repairs > 0) {
            res2 = recursion_sol(raw_works, now_status, work_id + 1, repairs - 1);
            if (res2 != -1 && work_id + 1 < raw_works.size())
                res2 += now_status.size() * (raw_works[work_id + 1].first - raw_works[work_id].first);
        }
        it1 = now_status.find(raw_works[work_id].second);
        if (pre_value == -1) { if (it1 != now_status.end()) now_status.erase(it1); }
        else if (it1 != now_status.end()) it1->second = pre_value;
        else now_status.emplace(raw_works[work_id].second, pre_value);
        if (res1 == -1) return res2;
        if (res2 == -1) return res1;
        return std::min(res1, res2);
    }

    std::int64_t solve(std::uint64_t k, std::uint64_t n, std::uint64_t m,
                       const std::vector<std::pair<std::uint64_t, std::uint64_t>> &raw_works) {
        std::map<std::uint64_t, std::uint64_t> now_status;
        return recursion_sol(raw_works, now_status, 0, m);
    }
}

namespace BrainSol {

    struct RoadWork {
        std::uint64_t day, work_id;

        bool operator<(const RoadWork &other) const {
            return day < other.day;
        }
    };

    struct Work {
        std::uint64_t road, day, weight;
    };

    std::int64_t solve(std::uint64_t k, std::uint64_t n, std::uint64_t m,
                       const std::vector<std::pair<std::uint64_t, std::uint64_t>> &raw_works) {
        std::vector<std::set<RoadWork>> roads(k);
        std::vector<Work> works;
        works.reserve(n);
        for (std::uint64_t i = 0; i < n; ++i) {
            roads[raw_works[i].second].emplace(raw_works[i].first, works.size());
            works.emplace_back(raw_works[i].second, raw_works[i].first, 0);
        }
        for (auto &road: roads) {
            for (auto it = road.begin(); it != road.end() && std::next(it) != road.end(); ++it) {
                works[it->work_id].weight = std::next(it)->day - it->day;
            }
            if (!road.empty()) {
                if (m-- == 0) return -1;
                road.erase(std::prev(road.end()));
            }
        }
        std::map<std::uint64_t, std::set<std::uint64_t>> weight_work;
        for (std::uint64_t i = 0; i < works.size(); ++i) {
            auto it = weight_work.find(works[i].weight);
            if (it != weight_work.end()) it->second.emplace(i);
            else weight_work.emplace(works[i].weight, std::set<std::uint64_t>{i});
        }
        while (m > 0 && !weight_work.empty() && weight_work.rbegin()->first > 0) {
            --m;
            auto work_id = *weight_work.rbegin()->second.rbegin();
            auto it1 = roads[works[work_id].road].lower_bound(RoadWork{works[work_id].day, 0});
            if (it1 != roads[works[work_id].road].begin()) {
                auto pre_it = std::prev(it1);
                auto it2 = weight_work.find(works[pre_it->work_id].weight);
                it2->second.erase(pre_it->work_id);
                if (it2->second.empty()) weight_work.erase(it2);
                works[pre_it->work_id].weight += works[work_id].day - works[pre_it->work_id].day;
                auto it3 = weight_work.find(works[pre_it->work_id].weight);
                if (it3 != weight_work.end()) it3->second.emplace(pre_it->work_id);
                else weight_work.emplace(works[pre_it->work_id].weight, std::set<std::uint64_t>{pre_it->work_id});
            }
            roads[works[work_id].road].erase(it1);
            auto it2 = weight_work.find(works[work_id].weight);
            it2->second.erase(work_id);
            if (it2->second.empty()) weight_work.erase(it2);
        }
        std::int64_t result = 0;
        for (const auto &w: weight_work) for (const auto &id: w.second) result += works[id].weight;
        return result;
    }
}

namespace Test {
    std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

    std::uint64_t randint(std::uint64_t a, std::uint64_t b) {
        return std::uniform_int_distribution(a, b)(rnd);
    }

    void gen(std::uint64_t &k, std::uint64_t &n, std::uint64_t &m,
             std::vector<std::pair<std::uint64_t, std::uint64_t>> &raw_works) {
        k = randint(1, 5);
        n = randint(1, 5);
        m = randint(1, 5);
        raw_works.resize(n);
        for (auto &[d, w]: raw_works) {
            d = randint(0, 5);
            w = randint(0, k - 1);
        }
        std::sort(raw_works.begin(), raw_works.end(),
                  [](const std::pair<std::uint64_t, std::uint64_t> &a,
                     const std::pair<std::uint64_t, std::uint64_t> &b) {
                      return a.first < b.first;
                  });
    }

    void Test() {
        std::uint64_t k, n, m;
        std::vector<std::pair<std::uint64_t, std::uint64_t>> raw_works;
        while (true) {
            gen(k, n, m, raw_works);
            auto true_solve = StupidSol::solve(k, n, m, raw_works);
            auto my_solve = BrainSol::solve(k, n, m, raw_works);
            if (true_solve != my_solve) {
                std::cout << k << " " << n << " " << m << "\n";
                for (const auto &[d, w]: raw_works) std::cout << d + 1 << " " << w + 1 << "\n";
                std::cout << "\ntrue: " << true_solve;
                std::cout << "\nmy: " << my_solve;
                break;
            }
        }
    }
}

int main() {
//    Test::Test();
    std::uint64_t k, n, m;
    std::cin >> k >> n >> m;
    std::vector<std::pair<std::uint64_t, std::uint64_t>> raw_works(n);
    for (auto &[d, w]: raw_works) {
        std::cin >> d >> w;
        --d;
        --w;
    }
    std::cout << BrainSol::solve(k, n, m, raw_works);
    return 0;
}
