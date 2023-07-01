#include <iostream>
#include <vector>

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

bool is_line_seg_intersect(pv line, pv start_line_p, pv seg, pv start_seg_p) {
    auto seg_1 = start_seg_p - start_line_p;
    auto seg_2 = start_seg_p + seg - start_line_p;
    auto res_1 = line * seg_1;
    auto res_2 = line * seg_2;
    if (res_1 == 0 || res_2 == 0) return true;
    else {
        if (res_1 > 0) return res_2 < 0;
        else return res_2 > 0;
    }
}

bool is_seg_seg_intersect(pv seg_1, pv start_seg_1, pv seg_2, pv start_seg_2) {
    return is_line_seg_intersect(seg_1, start_seg_1, seg_2, start_seg_2) &&
           is_line_seg_intersect(seg_2, start_seg_2, seg_1, start_seg_1);
}

void GetFigVecs(std::vector<std::pair<pv, pv>> &fig_vecs) {
    fig_vecs.clear();
    std::int64_t N;
    std::cin >> N;
    fig_vecs.reserve(N);
    pv start_v(0, 0), prev_v(0, 0), now_v(0, 0);
    bool is_pre_v = false;
    for (std::int64_t i = 0; i < N; ++i) {
        if (is_pre_v) {
            std::cin >> now_v.x >> now_v.y;
            fig_vecs.emplace_back(prev_v, now_v - prev_v);
            prev_v = now_v;
        } else {
            std::cin >> prev_v.x >> prev_v.y;
            start_v = prev_v;
            is_pre_v = true;
        }
    }
    fig_vecs.emplace_back(prev_v, start_v - prev_v);
}

bool MakeOneTest() {
    std::vector<std::pair<pv, pv>> fig1_vecs, fig2_vecs;
    GetFigVecs(fig1_vecs);
    GetFigVecs(fig2_vecs);
    for (auto [start_1, vec_1]: fig1_vecs)
        for (auto [start_2, vec_2]: fig2_vecs)
            if (is_seg_seg_intersect(vec_1, start_1, vec_2, start_2)) return true;
    return false;
}

int main() {
    std::int64_t K;
    std::cin >> K;
    for (std::int64_t i = 0; i < K; ++i) {
        if (MakeOneTest()) std::cout << "YES\n";
        else std::cout << "NO\n";
    }
    return 0;
}
