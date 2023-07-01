#include <iostream>
#include <vector>
#include <vector>

bool
FirstRes(const std::vector<std::int32_t> &houses, std::uint32_t &res_1, std::uint32_t &res_2, std::uint32_t &res_3) {
    std::int32_t sum_1 = 0, sum_2 = 0;
    std::uint32_t id_1 = houses.size(), id_2 = houses.size();
    for (std::uint32_t i = 0; i < houses.size(); ++i) {
        sum_1 += houses[i];
        if (sum_1 > 0) {
            id_1 = i;
            break;
        }
    }
    if (id_1 == houses.size()) return false;
    for (std::int32_t i = houses.size() - 1; i >= 0; --i) {
        sum_2 += houses[i];
        if (sum_2 > 0) {
            id_2 = i;
            break;
        }
    }
    if (id_2 == houses.size()) return false;
    if (id_1 >= id_2) return false;
    res_1 = id_1 + 1;
    res_3 = houses.size() - id_2;
    res_2 = houses.size() - res_1 - res_3;
    return true;
}

bool
SecondRes(const std::vector<std::int32_t> &houses, std::uint32_t &res_1, std::uint32_t &res_2, std::uint32_t &res_3) {
    std::int32_t sum_prefix = 0, best_sum_prefix = 1e9 + 1, best_prev_i = 0;
    for (std::uint32_t i = 0; i < houses.size() - 1; ++i) {
        sum_prefix += houses[i];
        if (sum_prefix - best_sum_prefix > 0) {
            res_1 = best_prev_i + 1;
            res_2 = i - best_prev_i;
            res_3 = houses.size() - 1 - i;
            return true;
        }
        if (best_sum_prefix > sum_prefix && sum_prefix > 0) {
            best_sum_prefix = sum_prefix;
            best_prev_i = i;
        }
    }
}

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::vector<std::int32_t> houses(N);
    for (auto &&e: houses) std::cin >> e;
    std::uint32_t res_1, res_2, res_3;
    if (FirstRes(houses, res_1, res_2, res_3)) std::cout << res_1 << " " << res_2 << " " << res_3;
    else if (SecondRes(houses, res_1, res_2, res_3)) std::cout << res_1 << " " << res_2 << " " << res_3;
    else {
        std::vector<std::int32_t> reversed_houses(houses.rbegin(), houses.rend());
        if (SecondRes(reversed_houses, res_1, res_2, res_3)) std::cout << res_3 << " " << res_2 << " " << res_1;
        else std::cout << 0;
    }
    return 0;
}
