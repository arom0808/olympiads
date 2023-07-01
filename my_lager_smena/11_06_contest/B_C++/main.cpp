#include <iostream>
#include <vector>

enum class CardType {
    no,
    corner,
    line
};

enum class CornerDir {
    left_top = 3,
    top_right = 4,
    right_bottom = 5,
    bottom_left = 6
};

enum class LineDir {
    horizontal = 1,
    vertical = 2
};

struct Card {
    CardType type;
    CornerDir corner_dir;
    LineDir line_dir;

    Card() : type(CardType::no), corner_dir(CornerDir::bottom_left), line_dir(LineDir::vertical) {}
};

enum class EasyDir {
    left,
    top,
    right,
    bottom
};


bool IsTouchThisDir(const Card &card, EasyDir dir) {
    if (card.type == CardType::no) return false;
    if (card.type == CardType::line) {
        if (card.line_dir == LineDir::horizontal && (dir == EasyDir::left || dir == EasyDir::right)) return true;
        if (card.line_dir == LineDir::vertical && (dir == EasyDir::top || dir == EasyDir::bottom)) return true;
        return false;
    } else {
        if (card.corner_dir == CornerDir::left_top) return dir == EasyDir::left || dir == EasyDir::top;
        if (card.corner_dir == CornerDir::top_right) return dir == EasyDir::top || dir == EasyDir::right;
        if (card.corner_dir == CornerDir::right_bottom) return dir == EasyDir::right || dir == EasyDir::bottom;
        /*if (card.corner_dir == CornerDir::bottom_left)*/ return dir == EasyDir::bottom || dir == EasyDir::left;
    }
}

bool IsNeedToBeThere(const std::vector<std::vector<Card>> &cards, std::uint32_t i, std::uint32_t j,
                     EasyDir dir) {
    if (dir == EasyDir::top) {
        if (i == 0) return false;
        return IsTouchThisDir(cards[i - 1][j], EasyDir::bottom);
    }
    if (dir == EasyDir::right) {
        if (j == cards[i].size() - 1) return false;
        return IsTouchThisDir(cards[i][j + 1], EasyDir::left);
    }
    if (dir == EasyDir::bottom) {
        if (i == cards.size() - 1) return false;
        return IsTouchThisDir(cards[i + 1][j], EasyDir::top);
    }
//    /*if (dir == EasyDir::left) {
    if (j == 0) return false;
    return IsTouchThisDir(cards[i][j - 1], EasyDir::right);
//    }
}

int main() {
    std::uint32_t n, m, g;
    std::cin >> n >> m >> g;
    std::vector<std::vector<Card>> cards(n, std::vector<Card>(m));
    for (std::uint32_t i = 0, temp; i < n; ++i) {
        for (std::uint32_t j = 0; j < m; ++j) {
            std::cin >> temp;
            if (temp == 0) cards[i][j].type = CardType::no;
            else if (temp == 1 || temp == 2) {
                cards[i][j].type = CardType::line;
                cards[i][j].line_dir = static_cast<LineDir>(temp);
            } else {
                cards[i][j].type = CardType::corner;
                cards[i][j].corner_dir = static_cast<CornerDir>(temp);
            }
        }
    }
    for (std::uint32_t i = 0; i < n; ++i) {
        for (std::uint32_t j = 0; j < m; ++j) {
            bool is_left_need = IsNeedToBeThere(cards, i, j, EasyDir::left),
                    is_top_need = IsNeedToBeThere(cards, i, j, EasyDir::top);
            if (is_left_need && is_top_need) {
                if (cards[i][j].type == CardType::corner) cards[i][j].corner_dir = CornerDir::left_top;
                else {
                    std::cout << "NO\n";
                    return 0;
                }
            } else if (is_left_need) {
                if (cards[i][j].type == CardType::corner) cards[i][j].corner_dir = CornerDir::bottom_left;
                else if (cards[i][j].type == CardType::line) cards[i][j].line_dir = LineDir::horizontal;
                else {
                    std::cout << "NO\n";
                    return 0;
                }
            } else if (is_top_need) {
                if (cards[i][j].type == CardType::corner) cards[i][j].corner_dir = CornerDir::top_right;
                else if (cards[i][j].type == CardType::line) cards[i][j].line_dir = LineDir::vertical;
                else {
                    std::cout << "NO\n";
                    return 0;
                }
            } else {
                if (cards[i][j].type == CardType::corner) cards[i][j].corner_dir = CornerDir::right_bottom;
                else if (cards[i][j].type == CardType::line) {
                    std::cout << "NO\n";
                    return 0;
                }
            }
        }
    }
    for (std::uint32_t i = 0; i < n; ++i) {
        if (IsTouchThisDir(cards[i][cards[i].size() - 1], EasyDir::right)) {
            std::cout << "NO\n";
            return 0;
        }
    }
    for (std::uint32_t j = 0; j < m; ++j) {
        if (IsTouchThisDir(cards[cards.size() - 1][j], EasyDir::bottom)) {
            std::cout << "NO\n";
            return 0;
        }
    }
    std::cout << "YES\n";
    for (const auto &l: cards) {
        for (const auto &card: l) {
            if (card.type == CardType::no) std::cout << "0";
            else if (card.type == CardType::line) std::cout << static_cast<std::uint32_t>(card.line_dir);
            else std::cout << static_cast<std::uint32_t>(card.corner_dir);
            std::cout << " ";
        }
        std::cout << "\n";
    }
}