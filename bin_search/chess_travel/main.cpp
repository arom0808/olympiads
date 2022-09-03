#include <iostream>
#include <vector>
#include <map>

using Moves = std::multimap<std::uint32_t, std::pair<std::uint32_t, std::uint32_t>>;

int main() {
    std::uint32_t m, n, k;
    std::cin >> m >> n >> k;
    Moves moves;
    std::uint32_t input_tmp;
    for (std::uint32_t i = 0; i < m; ++i) {
        for (std::uint32_t j = 0; j < n; ++j) {
            std::cin >> input_tmp;
            if (input_tmp != 0)
                moves.insert({input_tmp, {i, j}});
        }
    }
    if (moves.size() != k + 1) {
        std::cout << "Wrong Board";
        return 0;
    }
    if (moves.size() > 1) {
        for (auto f_i = moves.begin(), s_i = ++moves.begin(); s_i != moves.end(); ++f_i, ++s_i) {
            if (f_i->first == s_i->first) {
                std::cout << "Wrong Board";
                return 0;
            }
            if (f_i->second.first != s_i->second.first && f_i->second.second != s_i->second.second &&
                std::max(f_i->second.first, s_i->second.first) - std::min(f_i->second.first, s_i->second.first) !=
                std::max(f_i->second.second, s_i->second.second) - std::min(f_i->second.second, s_i->second.second)) {
                std::cout << "Wrong Board";
                return 0;
            }
        }
    }
    std::vector<std::vector<std::uint32_t>> board(m, std::vector<std::uint32_t>(n, 0));
    std::uint32_t move_number = 0;
    for (const auto &move: moves)
        board[move.second.first][move.second.second] = ++move_number;
    for (const auto &row: board) {
        for (const auto &item: row)
            std::cout << item << " ";
        std::cout << std::endl;
    }
    return 0;
}
