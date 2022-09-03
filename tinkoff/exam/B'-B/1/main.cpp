#include <iostream>
#include <vector>
#include <algorithm>

struct Solution {
    std::uint32_t index;
    std::uint32_t years_old;
    std::uint32_t from_written_off;
    std::uint32_t debits_number;

    Solution(std::uint32_t index, std::uint32_t years_old, std::uint32_t from_written_off = 0,
             std::uint32_t debits_number = 0)
            : index(index), years_old(years_old), from_written_off(from_written_off), debits_number(debits_number) {}
};

void YearsOldToSolutions(const std::vector<std::uint32_t> &years_old, std::vector<Solution> &solutions_result) {
    solutions_result.clear();
    solutions_result.reserve(years_old.size());
    for (std::uint32_t i = 0; i < years_old.size(); ++i)
        solutions_result.emplace_back(i, years_old[i]);
}

bool FindWriteOffs(std::vector<Solution> &solutions, std::uint32_t k) {
    for (std::uint32_t i = 1; i < solutions.size(); ++i) {
        std::uint32_t j = i;
        do {
            --j;
            if (solutions[j].debits_number < 2 && solutions[j].years_old - solutions[i].years_old >= k) {
                ++solutions[j].debits_number;
                solutions[i].from_written_off = solutions[j].index + 1;
                break;
            }
        } while (j > 0);
        if (solutions[i].from_written_off == 0) return false;
    }
    return true;
}

int main() {
    std::uint32_t n, k;
    std::cin >> n >> k;
    std::vector<std::uint32_t> years_old(n);
    for (auto &&year_old: years_old) std::cin >> year_old;
    std::vector<Solution> solutions;
    YearsOldToSolutions(years_old, solutions);
    std::sort(solutions.begin(), solutions.end(),
              [](const Solution &a, const Solution &b) -> bool { return a.years_old > b.years_old; });
    bool result = FindWriteOffs(solutions, k);
    if (result) {
        std::sort(solutions.begin(), solutions.end(),
                  [](const Solution &a, const Solution &b) -> bool { return a.index < b.index; });
        for (const auto &sol: solutions) std::cout << sol.from_written_off << ' ';
    } else {
        std::cout << "-1";
    }
    return 0;
}
