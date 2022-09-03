#include <iostream>
#include <vector>

std::uint32_t approximate_bin_search(const std::uint32_t &init_number, const std::vector<std::uint32_t> &n_t_s) {
    std::uint32_t l = 0, r = n_t_s.size() - 1;
    while (l < r) {
        std::uint32_t m = (l + r) / 2, m_value = n_t_s[m];
        if (m_value < init_number) l = m + 1;
        else r = m;
    }
    if (l > 0 && n_t_s[l] != init_number &&
        std::max(n_t_s[l], init_number) - std::min(n_t_s[l], init_number) <
        std::max(n_t_s[l - 1], init_number) - std::min(n_t_s[l - 1], init_number))
        return l;
    else
        return l - 1;
}

int main() {
    std::uint32_t N, K, initial_number;
    std::cin >> N >> K;
    std::vector<std::uint32_t> numbers_to_search(N), results(K);
    for (auto &&n_t_s: numbers_to_search) std::cin >> n_t_s;
    for (auto &&res: results) {
        std::cin >> initial_number;
        res = approximate_bin_search(initial_number, numbers_to_search);
    }
    for (const auto &res: results) std::cout << numbers_to_search[res] << std::endl;
    return 0;
}
