#include <iostream>
#include <vector>
#include <set>

const std::uint32_t null_value = 1e7;

struct Chain {
    std::uint32_t left, right;
    std::uint32_t color;

    std::uint32_t size() const {
        return right - left;
    }

    bool operator<(const Chain &other) const {
        return this->size() > other.size();
    }

    Chain(std::uint32_t left, std::uint32_t right, std::uint32_t color) : left(left), right(right), color(color) {}
};

int main() {
    std::uint32_t m, n;
    std::cin >> m >> n;
    std::vector<std::uint32_t> purpose_chain(m);
    for (auto &&student_color: purpose_chain) std::cin >> student_color;
    std::set<Chain> color_chains;
    for (std::uint32_t color = 1; color <= n; ++color) {
        std::uint32_t left = null_value, right = null_value;
        for (std::uint32_t i = 0; i < m; ++i) {
            if (purpose_chain[i] == color) {
                left = i;
                break;
            }
        }
        if (left == null_value) continue;
        for (std::uint32_t i = m; i > 0; --i) {
            if (purpose_chain[i - 1] == color) {
                right = i - 1;
                break;
            }
        }
        color_chains.emplace(left, right, color);
    }
//    for (const auto &color_chain: color_chains) {
//        std::cout << "{ " << color_chain.left << ", " << color_chain.right << ", " << color_chain.color << " }"
//                  << std::endl;
//    }
    std::vector<std::uint32_t> my_chain(m, null_value);
    for (const auto &color_chain: color_chains)
        for (std::uint32_t i = color_chain.left; i <= color_chain.right; ++i) my_chain[i] = color_chain.color;
    for (std::uint32_t i = 0; i < m; ++i) {
        if (purpose_chain[i] != my_chain[i]) {
            std::cout << "-1";
            return 0;
        }
    }
    std::cout << color_chains.size() << std::endl;
    for (const auto &color_chain: color_chains)
        std::cout << color_chain.color << " " << color_chain.left + 1 << " " << color_chain.right + 1 << std::endl;
    return 0;
}
