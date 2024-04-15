#include <iostream>
#include <vector>

class SparseTable {
    std::vector<std::vector<std::pair<std::uint32_t, std::uint32_t>>> st;

public:
    [[nodiscard]] std::uint32_t max_pos(std::uint32_t l, std::uint32_t r) const {
        std::uint32_t k = std::__lg(r - l);
        return st[k][l].first > st[k][r - (1 << k)].first ? st[k][l].second : st[k][r - (1 << k)].second;
    }

    explicit SparseTable(const std::vector<std::uint32_t> &vals) :
            st(std::__lg(vals.size()) + 1, std::vector<std::pair<std::uint32_t, std::uint32_t>>(vals.size())) {
        for (std::uint32_t i = 0; i < vals.size(); ++i) {
            st[0][i].first = vals[i];
            st[0][i].second = i;
        }

        for (std::uint32_t k = 0; k < st.size(); ++k) {
            for (std::uint32_t i = 0; i + (1 << (k - 1)) < vals.size(); ++i) {
                st[k][i] = (st[k - 1][i] > st[k - 1][i + (1 << (k - 1))]
                            ? st[k - 1][i] : st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
};

std::uint32_t
get_ans(const std::vector<std::uint32_t> &a, const SparseTable &st, std::uint32_t n, std::uint32_t l, std::uint32_t r) {
    std::uint32_t best = 0, ab, bb, cb;
    for (std::uint32_t b = l + 1; b + 1 < r; ++b) {
        auto m1 = st.max_pos(l, b), m2 = st.max_pos(b + 1, r);
        if (b - m1 <= m2 - b) {
            if (best < a[m1] + a[b] + a[m2]) {
                best = a[m1] + a[b] + a[m2];
                ab = m1;
                bb = b;
                cb = m2;
            }
        } else {
            if (b * 2 >= l + m2) {
                auto m3 = st.max_pos(2 * b - m2, b);
                if (best < a[m3] + a[b] + a[m2]) {
                    best = a[m3] + a[b] + a[m2];
                    ab = m3;
                    bb = b;
                    cb = m2;
                }
            }
            if (b * 2 < r + m1) {
                auto m4 = st.max_pos(b * 2 - m1, r);
                if (best < a[m1] + a[b] + a[m4]) {
                    best = a[m1] + a[b] + a[m4];
                    ab = m1;
                    bb = b;
                    cb = m4;
                }
            }
        }
    }
    for (std::uint32_t i = l; i < r; ++i) std::cout << a[i] << " ";
    std::cout << "\n" << ab << " " << bb << " " << cb << "\n";
    std::cout << a[ab] << " " << a[bb] << " " << a[cb] << ": " << best << "\n\n";
    return best;
}

int main() {
    std::uint32_t n, q;
    std::cin >> n;
    std::vector<std::uint32_t> a(n);
    for (auto &c: a) std::cin >> c;
    SparseTable st(a);
    std::cin >> q;
    for (std::uint32_t i = 0, l, r; i < q; ++i) {
        std::cin >> l >> r;
        get_ans(a, st, n, l - 1, r);
//        std::cout << get_ans(a, st, n, l - 1, r) << "\n";
    }
    return 0;
}
