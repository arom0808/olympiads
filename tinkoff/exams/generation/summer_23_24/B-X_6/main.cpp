#include <iostream>
#include <vector>

struct DPEl {
    std::uint32_t max_last_plus = 0, max_last_minus = 0;

    DPEl &operator=(const DPEl &other) = default;

    bool operator==(const DPEl &other) const {
        return max_last_plus == other.max_last_plus && max_last_minus == other.max_last_minus;
    }
};

void ProcessDP(const std::vector<std::uint32_t> &pokemons, std::vector<DPEl> &dp) {
    dp[0].max_last_plus = pokemons[0];
    dp[0].max_last_minus = 0;
    for (std::uint32_t i = 1; i < pokemons.size(); ++i) {
        auto &pre = dp[i - 1], &now = dp[i];
        const auto &pok = pokemons[i];
        now = pre;
        if (pre.max_last_minus + pok > now.max_last_plus)
            now.max_last_plus = pre.max_last_minus + pok;
        if (pre.max_last_plus > pok && pre.max_last_plus - pok > now.max_last_minus)
            now.max_last_minus = pre.max_last_plus - pok;
    }
}

void
NextProcessDp(const std::vector<std::uint32_t> &pokemons, std::vector<DPEl> &dp, std::uint32_t l, std::uint32_t r) {
    if (l == 0) {
        dp[0].max_last_plus = pokemons[0];
        dp[0].max_last_minus = 0;
    }
    auto makei = [&dp, &pokemons](std::uint32_t i) {
        auto &pre = dp[i - 1], &now = dp[i];
        const auto &pok = pokemons[i];
        auto l_now = dp[i];
        now = pre;
        if (pre.max_last_minus + pok > now.max_last_plus)
            now.max_last_plus = pre.max_last_minus + pok;
        if (pre.max_last_plus > pok && pre.max_last_plus - pok > now.max_last_minus)
            now.max_last_minus = pre.max_last_plus - pok;
        return now == l_now;
    };
    for (std::uint32_t i = std::max<std::uint32_t>(1, l); i < r; ++i) if (makei(i)) break;
    if (makei(r)) return;
    for (std::uint32_t i = r + 1; i < pokemons.size(); ++i) if (makei(i)) break;
}

int main() {
    std::uint32_t n, q;
    std::cin >> n >> q;
    std::vector<std::uint32_t> pokemons(n);
    for (auto &&pok: pokemons) std::cin >> pok;
    std::vector<DPEl> dp(n);
    ProcessDP(pokemons, dp);
    std::cout << dp.back().max_last_plus << "\n";
    for (std::uint32_t i = 0, l, r; i < q; ++i) {
        std::cin >> l >> r;
        std::swap(pokemons[--l], pokemons[--r]);
        NextProcessDp(pokemons, dp, l, r);
        std::cout << dp.back().max_last_plus << "\n";
    }
    return 0;
}