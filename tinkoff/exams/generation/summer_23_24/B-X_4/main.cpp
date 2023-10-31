#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

struct Coord {
    std::int32_t x = 0, y = 0;

    Coord(std::int32_t x = 0, std::int32_t y = 0) : x(x), y(y) {}

    bool operator<(const Coord &other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    bool operator==(const Coord &other) const {
        return x == other.x && y == other.y;
    }

    void mv_right() { ++x; }

    void mv_right_bottom() {
        ++x;
        --y;
    }

    void mv_bottom() { --y; }

    void mv_bottom_left() {
        --y;
        --x;
    }

    void mv_left() { --x; }

    void mv_left_top() {
        --x;
        ++y;
    }

    void mv_top() { ++y; }

    void mv_top_right() {
        ++y;
        ++x;
    };
};

enum class Wall {
    left_zero,
    left_half,
    right_zero,
    right_half
};

struct Figure {
public:
    std::uint32_t a_t, a_b, b_l, b_r, c_t, c_b, d_t, d_b;
    std::uint32_t area_x_2;
    bool valid;

    bool check_valid() const {
        Coord c;
        for (std::uint32_t i = 0; i < a_t; ++i) c.mv_right();
        for (std::uint32_t i = 0; i < d_t; ++i) c.mv_right_bottom();
        for (std::uint32_t i = 0; i < b_r; ++i) c.mv_bottom();
        for (std::uint32_t i = 0; i < c_b; ++i) c.mv_bottom_left();
        for (std::uint32_t i = 0; i < a_b; ++i) c.mv_left();
        for (std::uint32_t i = 0; i < d_b; ++i) c.mv_left_top();
        for (std::uint32_t i = 0; i < b_l; ++i) c.mv_top();
        for (std::uint32_t i = 0; i < c_t; ++i) c.mv_top_right();
        return c.x == 0 && c.y == 0;
    };

    std::uint32_t count_area() const {
        if (!valid) return 0;
        std::map<Coord, std::set<Wall>> walls;
        Coord cc;
        auto add_f = [&walls](const Coord &cc, Wall wall) {
            auto it = walls.find(cc);
            if (it != walls.end()) it->second.emplace(wall);
            else walls.emplace(cc, std::set<Wall>{wall});
        };
        for (std::uint32_t i = 0; i < a_t; ++i) cc.mv_right();
        for (std::uint32_t i = 0; i < d_t; ++i) {
            add_f(Coord(cc.x, cc.y - 1), Wall::right_half);
            cc.mv_right_bottom();
        };
        for (std::uint32_t i = 0; i < b_r; ++i) {
            cc.mv_bottom();
            add_f(cc, Wall::right_zero);
        }
        for (std::uint32_t i = 0; i < c_b; ++i) {
            cc.mv_bottom_left();
            add_f(cc, Wall::right_half);
        }
        for (std::uint32_t i = 0; i < a_b; ++i) cc.mv_left();
        for (std::uint32_t i = 0; i < d_b; ++i) {
            add_f(Coord(cc.x - 1, cc.y), Wall::left_half);
            cc.mv_left_top();
        }
        for (std::uint32_t i = 0; i < b_l; ++i) {
            add_f(cc, Wall::left_zero);
            cc.mv_top();
        }
        for (std::uint32_t i = 0; i < c_t; ++i) {
            add_f(cc, Wall::left_half);
            cc.mv_top_right();
        }
        std::uint32_t two_area = 0;
        for (auto left_wall: walls) {
            if (left_wall.second.find(Wall::left_half) == left_wall.second.end() &&
                left_wall.second.find(Wall::left_zero) == left_wall.second.end())
                continue;
            cc = left_wall.first;
            if (left_wall.second.find(Wall::left_half) != left_wall.second.end()) {
                ++two_area;
                cc.mv_right();
            }
            while (true) {
                auto it = walls.find(cc);
                if (it == walls.end() || (it->second.find(Wall::right_half) == it->second.end() &&
                                          it->second.find(Wall::right_zero) == it->second.end()))
                    two_area += 2;
                else {
                    if (it->second.find(Wall::right_half) != it->second.end()) ++two_area;
                    break;
                }
                cc.mv_right();
            }
        }
        return two_area;
    }

    explicit Figure(std::uint32_t a_t = 0, std::uint32_t a_b = 0, std::uint32_t b_l = 0, std::uint32_t b_r = 0,
                    std::uint32_t c_t = 0, std::uint32_t c_b = 0, std::uint32_t d_t = 0, std::uint32_t d_b = 0)
            : a_t(a_t), a_b(a_b), b_l(b_l), b_r(b_r), c_t(c_t), c_b(c_b), d_t(d_t), d_b(d_b) {
        valid = check_valid();
        area_x_2 = count_area();
    }
};

const std::int32_t scope = 3;

bool solute(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::vector<char> &res) {
    res.clear();
    res.reserve(a + b + c + d);
//    if ((a + c + d) % 2 != 0) return false;
//    if ((b + c + d) % 2 != 0) return false;
//    if (a % 2 != b % 2) return false;
    std::vector<Figure> figs;
    figs.reserve(8);
    for (std::uint32_t a_t = (a / 2 < scope ? 0 : a / 2 - scope), a_b = a - a_t;
         a_t <= a && a_t <= a / 2 + scope; ++a_t, a_b = a - a_t) {
        for (std::uint32_t b_l = (b / 2 < scope ? 0 : b / 2 - scope), b_r = b - b_l;
             b_l <= b && b_l <= b / 2 + scope; ++b_l, b_r = b - b_l) {
            for (std::uint32_t c_t = (c / 2 < scope ? 0 : c / 2 - scope), c_b = c - c_t;
                 c_t <= c && c_t <= c / 2 + scope; ++c_t, c_b = c - c_t) {
                for (std::uint32_t d_t = (d / 2 < scope ? 0 : d / 2 - scope), d_b = d - d_t;
                     d_t <= d && d_t <= d / 2 + scope; ++d_t, d_b = d - d_t) {
                    Figure fig(a_t, a_b, b_l, b_r, c_t, c_b, d_t, d_b);
                    if (fig.valid) figs.push_back(fig);
                }
            }
        }
    }//    for (std::uint32_t a_t = a / 2, a_b = a - a_t, i1 = 0; i1 < 2; ++i1, a_t = a_b, a_b = a - a_t)
//        for (std::uint32_t b_l = b / 2, b_r = b - b_l, i2 = 0; i2 < 2; ++i2, b_l = b_r, b_r = b - b_l)
//            for (std::uint32_t c_t = c / 2, c_b = c - c_t, i3 = 0; i3 < 2; ++i3, c_t = c_b, c_b = c - c_t)
//                for (std::uint32_t d_t = d / 2, d_b = d - d_t, i4 = 0; i4 < 2; ++i4, d_t = d_b, d_b = d - d_t)
    std::sort(figs.begin(), figs.end(), [](const Figure &a, const Figure &b) { return a.area_x_2 > b.area_x_2; });
    for (const auto &fig: figs) {
        if (!fig.valid) continue;
        for (std::uint32_t i = 0; i < fig.a_t; ++i) res.push_back('1');
        for (std::uint32_t i = 0; i < fig.d_t; ++i) res.push_back('4');
        for (std::uint32_t i = 0; i < fig.b_r; ++i) res.push_back('2');
        for (std::uint32_t i = 0; i < fig.c_b; ++i) res.push_back('3');
        for (std::uint32_t i = 0; i < fig.a_b; ++i) res.push_back('1');
        for (std::uint32_t i = 0; i < fig.d_b; ++i) res.push_back('4');
        for (std::uint32_t i = 0; i < fig.b_l; ++i) res.push_back('2');
        for (std::uint32_t i = 0; i < fig.c_t; ++i) res.push_back('3');
        return true;
    }
    return false;
}

int main() {
    std::uint32_t a, b, c, d;
    std::cin >> a >> b >> c >> d;
    std::vector<char> res;
    if (solute(a, b, c, d, res)) for (auto w: res) std::cout << w;
    else std::cout << "impossible";
    return 0;
}
