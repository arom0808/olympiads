#include <iostream>
#include <vector>
#include <algorithm>

inline std::uint32_t bit_left(std::uint32_t pow) { return static_cast<std::uint32_t>(1) << pow; }

std::uint32_t mask_by_input(std::istream &in) {
    std::uint32_t n, res = 0;
    in >> n;
    for (std::uint32_t lamp_id, i = 0; i < n; ++i) {
        in >> lamp_id;
        res |= bit_left(lamp_id - 1);
    }
    return res;
}

std::uint32_t invert_by_mask(std::uint32_t num, std::uint32_t mask) {
    std::uint32_t to_make_zero = num & mask, to_make_one = (~num) & mask;
    num &= (~to_make_zero);
    num |= to_make_one;
    return num;
}

std::uint32_t invert_lamps(std::uint32_t lamps, std::uint32_t k, std::uint32_t switches_mask,
                           const std::vector<std::uint32_t> &masks) {
    for (std::int32_t i = k - 1; i >= 0; --i, switches_mask >>= 1)
        if (switches_mask & 1) lamps = invert_by_mask(lamps, masks[i]);
    return lamps;
}

void get_res_by_switches_mask(std::uint32_t k, std::uint32_t switches_mask, std::vector<std::uint32_t> &res) {
    res.clear();
    res.reserve(15);
    for (std::int32_t i = k - 1; i >= 0; --i, switches_mask >>= 1) if (switches_mask & 1) res.push_back(i + 1);
    std::reverse(res.begin(), res.end());
}

int main() {
    std::uint32_t n, k;
    std::cin >> n >> k;
    std::uint32_t required_lamps = bit_left(n) - 1;
    std::vector<std::uint32_t> masks(k);
    for (auto &mask: masks) mask = mask_by_input(std::cin);
    for (std::uint32_t switches_mask = 0, max_switches_mask = bit_left(k);
         switches_mask < max_switches_mask; ++switches_mask) {
        std::uint32_t lamps = invert_lamps(0, k, switches_mask, masks);
        if (lamps != required_lamps) continue;
        std::vector<std::uint32_t> res;
        get_res_by_switches_mask(k, switches_mask, res);
        std::cout << res.size() << "\n";
        for (auto num: res) std::cout << num << " ";
        return 0;
    }
    std::cout << "-1";
    return 0;
}
