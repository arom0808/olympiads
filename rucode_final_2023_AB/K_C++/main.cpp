#include <iostream>
#include <vector>
#include <bitset>

//auto ss = std::bitset<64>(num).to_string();
//for (std::uint32_t i = 1; i <= 64; ++i) std::cout << ss[i - 1] << (i % 8 == 0 ? " " : "");
//std::cout << "\n";

std::uint64_t reverse_endian(std::uint64_t num) {
    std::uint64_t res = 0;
    for (std::uint32_t i = 0; i < 8; ++i) res |= ((num >> (i * 8)) << 56) >> (i * 8);
    return res;
}

void encode() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint64_t> nums(n);
    for (auto &&num: nums) std::cin >> num;
    std::vector<std::uint64_t> added(24, 0);
    for (std::uint32_t i = 0; i < 24; ++i) {
        for (std::uint32_t j = 0; j < 8; ++j) {
            for (std::uint32_t k = 0; k < 8; ++k) {
                if (k == 0) { if (j == 0) added[i] |= (1ull << 63); }
                else {
                    std::uint32_t pos = (k - 1) + j * 7 + i * 56;
//                    if (pos < n) std::cout << pos << " " << nums[pos] << " " << reverse_endian(nums[pos]) << "\n";
                    if (pos < n && nums[pos] > reverse_endian(nums[pos]))
                        added[i] |= (1ull << (7 - k)) << ((7 - j) * 8);
                }
            }
        }
    }
    std::cout << n + 24 << "\n";
    for (const auto &el: nums) std::cout << el << " ";
    for (const auto &el: added) std::cout << el << " ";
}

void decode() {
    std::uint32_t f_cnt;
    std::cin >> f_cnt;
    std::uint32_t n = f_cnt - 24;
    std::vector<std::uint64_t> nums(n), added(24);
    for (auto &&num: nums) std::cin >> num;
    for (auto &&el: added) std::cin >> el;
    for (std::uint32_t i = 0; i < 24; ++i) {
        if (added[i] >> 63 == 0) added[i] = reverse_endian(added[i]);
        for (std::uint32_t j = 0; j < 8; ++j) {
            for (std::uint32_t k = 0; k < 8; ++k) {
                if (k == 0) continue;
                std::uint32_t pos = (k - 1) + j * 7 + i * 56;
                if (pos >= n) continue;
                if ((added[i] >> ((7 - j) * 8) >> (7 - k)) & 1ull)
                    std::cout << std::max(nums[pos], reverse_endian(nums[pos])) << " ";
                else
                    std::cout << std::min(nums[pos], reverse_endian(nums[pos])) << " ";
            }
        }
    }
}

int main() {
//    std::freopen("in.txt", "r", stdin);
//    std::freopen("out.txt", "w", stdout);
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "encode") encode();
    else decode();
    return 0;
}
