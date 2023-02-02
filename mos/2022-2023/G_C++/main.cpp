#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <chrono>
#include <map>
#include <fstream>

void AddNextLevel(std::vector<std::set<std::multiset<std::uint32_t>>> &factorizations, const std::uint32_t &m,
                  std::uint32_t now_level) {
    for (const auto &fact: factorizations[now_level]) {
        auto cur_fact = fact;
        for (const auto &num: fact) {
            if (num < 4) continue;
            cur_fact.erase(cur_fact.find(num));
            auto num_sqrt = static_cast<std::uint32_t>(std::sqrt(static_cast<double>(num))) + 1;
            for (std::uint32_t del = 2; del <= num_sqrt && del <= m; ++del) {
                if (num % del == 0) {
                    cur_fact.insert(del);
                    cur_fact.insert(num / del);
                    factorizations[now_level + 1].insert(cur_fact);
                    cur_fact.erase(cur_fact.find(del));
                    cur_fact.erase(cur_fact.find(num / del));
                }
            }
            cur_fact.insert(num);
        }
    }
}

std::uint32_t MaxFacSize(const std::uint64_t &n) {
    if (n < 4) return 1;
    std::uint32_t max_fac_size = 1;
    auto max_i = static_cast<std::uint32_t>(std::sqrt(static_cast<long double>(n))) + 1;
    for (std::uint32_t i = 2; i <= max_i; ++i) {
        if (n % i != 0) continue;
        std::uint32_t cur_max = MaxFacSize(n / i);
        if (cur_max + 1 > max_fac_size) max_fac_size = cur_max + 1;
    }
    return max_fac_size;
}

std::uint32_t Solve(std::uint64_t n, std::uint64_t m) {
    if (n < 4) return static_cast<std::uint32_t>(m >= n);
    auto max_m = static_cast<std::uint32_t>(std::min(
            static_cast<std::uint64_t>(std::numeric_limits<std::uint32_t>::max()), m));
    auto result = static_cast<std::uint32_t>(m >= n);
    std::vector<std::set<std::multiset<std::uint32_t>>> factorizations;
    factorizations.resize(MaxFacSize(n) + 1);
    auto first_sqrt = static_cast<std::uint32_t>(std::sqrt(static_cast<long double>(n))) + 1;
    for (std::uint32_t del = 2; del <= first_sqrt && del <= m; ++del) {
        if (n % del == 0) factorizations[2].insert({del, static_cast<std::uint32_t>(n / del)});
    }
    for (std::uint32_t i = 2; i < factorizations.size() - 1; ++i) {
        AddNextLevel(factorizations, max_m, i);
        if (factorizations[i + 1].empty()) break;
    }
    for (std::uint32_t i = 1; i < factorizations.size(); ++i) result += factorizations[i].size();
    return result;
}

int main() {
//    std::uint64_t n, m;
//    std::cin >> n >> m;
//    std::cout << Solve(n, m);
    std::ofstream ff("ff.txt");
    ff << "{";
    std::map<std::pair<std::uint64_t, std::uint64_t>, std::uint32_t> cache;
    std::uint32_t max_max_fac_size = 0;
    for (std::uint64_t n = 134217728; n <= 100000000000ULL; ++n) {
        if (n % 1000 == 0) {
            std::cout << n << " " << max_max_fac_size << "\n";
            ff.flush();
        }
        auto max_fac_size = MaxFacSize(n);
        if (max_fac_size > max_max_fac_size) max_max_fac_size = max_fac_size;
        if (max_fac_size < 20) continue;
        auto m = n;
        auto start = std::chrono::steady_clock::now();
        auto res = Solve(n, m);
        auto end = std::chrono::steady_clock::now();
        auto run_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (run_time >= 1000) {
            ff << "{{" << n << ", " << m << "}, " << res << "}, ";
        }
    }
    ff << "}";
    return 0;
}
