#include <iostream>
#include <vector>
#include <algorithm>

struct Action {
    std::uint32_t pos, spell_id;
    bool type;

    bool operator<(const Action &other) const {
        if (pos != other.pos) return pos < other.pos;
        if (type != other.type) return type; // first the finish action
        return spell_id < other.spell_id;
    }

    Action(std::uint32_t pos, std::uint32_t spell_id, bool type) : pos(pos), spell_id(spell_id), type(type) {}
};

std::vector<std::uint32_t> count_bits_cnt() {
    std::vector<std::uint32_t> counts(1 << 8, 0);
    for (std::uint32_t i = 0; i < (1 << 8); ++i)
        for (std::uint32_t j = i; j; j >>= 1)
            counts[i] += j & 1;
    return counts;
}

int main() {
    auto bits_cnt = count_bits_cnt();
    std::uint32_t n, m, k;
    std::cin >> n >> m >> k;
    std::vector<Action> acts;
    acts.reserve(2 * n);
    for (std::uint32_t i = 0, l, r; i < n; ++i) {
        std::cin >> l >> r;
        acts.emplace_back(l - 1, i, false);
        acts.emplace_back(r, i, true);
    }
    std::sort(acts.begin(), acts.end());
    std::vector<std::int32_t> bit_blame(k, -1), dp(1 << k, -1);
    dp[0] = 0;
    std::int32_t pre_pos = -1;
    for (std::uint32_t i = 0; i < 2 * n; ++i) {
        if (pre_pos != -1)
            for (std::uint32_t mask = 0; mask < (1 << k); ++mask)
                if (bits_cnt[mask] % 2 == 1 && dp[mask] != -1) dp[mask] += acts[i].pos - pre_pos;
        if (!acts[i].type) {
            std::uint32_t new_bit = 0;
            while (bit_blame[new_bit] != -1) ++new_bit;
            bit_blame[new_bit] = acts[i].spell_id;
            for (std::uint32_t mask = 0; mask < (1 << k); ++mask)
                dp[mask | (1 << new_bit)] = dp[mask & (~(1 << new_bit))];
        } else {
            std::uint32_t del_bit = 0;
            while (bit_blame[del_bit] != acts[i].spell_id) ++del_bit;
            bit_blame[del_bit] = -1;
            for (std::uint32_t mask = 0; mask < (1 << k); ++mask) {
                if (dp[mask | (1 << del_bit)] > dp[mask & (~(1 << del_bit))])
                    dp[mask & (~(1 << del_bit))] = dp[mask | (1 << del_bit)];
                dp[mask | (1 << del_bit)] = -1;
            }
        }
        pre_pos = acts[i].pos;
    }
    std::cout << *std::max_element(dp.begin(), dp.end());
    return 0;
}
