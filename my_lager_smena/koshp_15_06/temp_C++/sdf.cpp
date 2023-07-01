#include<iostream>

struct pv {
    std::int64_t x, y;

    pv(std::int64_t x, std::int64_t y) : x(x), y(y) {}

    pv(const pv &a, const pv &b) : x(b.x - a.x), y(b.y - a.y) {}

    std::int64_t operator^(const pv &v) const { return x * v.x + y * v.y; }

    [[nodiscard]] pv norm() const { return {-y, x}; }

    pv operator+(const pv &v) const { return {x + v.x, y + v.y}; }

    pv operator-(const pv &v) const { return {x - v.x, y - v.y}; }

    std::int64_t operator*(const pv &v) const { return x * v.y - v.x * y; }
};

bool is_intersect(pv line, pv start_line_p, pv seg, pv start_seg_p) {
    auto seg_1 = start_seg_p - start_line_p;
    auto seg_2 = start_seg_p + seg - start_line_p;
    auto res_1 = line * seg_1;
    auto res_2 = line * seg_2;
    if (res_1 == 0 || res_2 == 0)return true;
    else {
        if (res_1 > 0) return res_2 < 0;
        else return res_2 > 0;
    }
}

std::int64_t intersect_cnt(std::int64_t square_id, pv line, pv start_p) {
    std::int64_t res = 0;
    if (is_intersect(line, start_p, pv(square_id, square_id), pv(-square_id, 0))) ++res;
    if (is_intersect(line, start_p, pv(square_id, -square_id), pv(0, square_id))) ++res;
    if (is_intersect(line, start_p, pv(-square_id, -square_id), pv(square_id, 0))) ++res;
    if (is_intersect(line, start_p, pv(-square_id, square_id), pv(0, -square_id))) ++res;
    if (is_intersect(line, start_p, pv(0, 0), pv(-square_id, 0))) --res;
    if (is_intersect(line, start_p, pv(0, 0), pv(0, square_id))) --res;
    if (is_intersect(line, start_p, pv(0, 0), pv(square_id, 0))) --res;
    if (is_intersect(line, start_p, pv(0, 0), pv(0, -square_id))) --res;
    return res;
}

int main() {
    std::int64_t n, q;
    std::cin >> n >> q;
    for (std::int64_t i = 0, x1, y1, x2, y2; i < q; ++i) {
        std::cin >> x1 >> y1 >> x2 >> y2;
        pv line(pv(x2, y2), pv(x1, y1));
        pv start_p(x1, y1);
        std::int64_t l = 1, r = n;
        while (l < r) {
            auto m = (l + r) / 2;
            auto i_c = intersect_cnt(m, line, start_p);
            if (i_c == 0) l = m + 1;
            else if (i_c == 1) l = r = m;
            else r = m;
        }
        std::cout << intersect_cnt(l, line, start_p) + (n - l) * 2 << "\n";
    }
}//
// Created by banan on 15.06.2023.
//
