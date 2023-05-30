#include <iostream>
#include <string>
#include <vector>

const std::uint64_t k = 257, mod = 1e9 + 7;

class Hashes {
public:
    std::vector<std::uint64_t> hashes, k_pow;

    std::uint64_t hash_substring(std::uint32_t l, std::uint32_t r) {
        return (mod * mod + hashes[r] - hashes[l] * k_pow[hashes.size() - l]) % mod;
    }

    explicit Hashes(const std::string &str) : hashes(str.size() + 1), k_pow(str.size() + 1) {
        k_pow.front() = 1;
        hashes.front() = 0;
        for (std::uint32_t i = 1; i < k_pow.size(); ++i) {
            hashes[i] = (hashes[i - 1] * k + static_cast<std::uint8_t>(str[i - 1]) * k_pow[i]) % mod;
            k_pow[i] = (k_pow[i - 1] * k) % mod;
        }
    }
};

int main() {
    std::string raw_str;
    std::cin >> raw_str;
    Hashes hashes(raw_str);
    std::uint32_t m, a, b, c, d;
    std::cin >> m;
    std::vector<bool> results(m);
    for (auto &&res: results) {
        std::cin >> a >> b >> c >> d;
        res = hashes.hash_substring(a - 1, b - 1) == hashes.hash_substring(c - 1, d - 1);
    }
    for (const auto &res: results) std::cout << (res ? "Yes" : "No") << "\n";
    return 0;
}
