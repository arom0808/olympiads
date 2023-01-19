#include <iostream>
#include <vector>
#include <stack>
#include <set>

const std::uint32_t null_value = 1e7;

struct Chain {
    std::uint32_t left;
    mutable std::uint32_t right;
    std::uint32_t color;

    std::uint32_t size() const {
        return right - left;
    }

    bool operator<(const Chain &other) const {
        return this->left < other.left;
    }

    Chain(std::uint32_t left, std::uint32_t right, std::uint32_t color) : left(left), right(right), color(color) {}
};

int main() {
    std::uint32_t m, n;
    std::cin >> m >> n;
    std::vector<std::uint32_t> purpose_chain(m);
    for (auto &&student_color: purpose_chain) {
        std::cin >> student_color;
        --student_color;
    }
    std::vector<std::uint32_t> status(n, 0);
    std::stack<std::uint32_t> now_colors;
    std::set<Chain> result;
    for (std::uint32_t i = 0; i < m; ++i) {
        if (status[purpose_chain[i]] == 0) {
            status[purpose_chain[i]] = 1;
            now_colors.push(purpose_chain[i]);
            result.emplace(i, null_value, purpose_chain[i]);
        } else if (status[purpose_chain[i]] == 1) {
            std::uint32_t i_c = now_colors.top();
            while (i_c != purpose_chain[i]) {
                status[i_c] = 2;
                for (auto &&r: result) {
                    if (r.color == i_c) {
                        r.right = i;
                        break;
                    }
                }
                now_colors.pop();
                i_c = now_colors.top();
            }
        } else if (status[purpose_chain[i]] == 2) {
            std::cout << "-1";
            return 0;
        }
    }
    std::cout << result.size() << std::endl;
    for (const auto &r: result)
        std::cout << r.color + 1 << " " << r.left + 1 << " " << (r.right == null_value ? m : r.right) << std::endl;
    return 0;
}
