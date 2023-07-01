#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

//class SqrtDec {
//public:
//    struct Segment {
//        std::uint32_t l = 0, r = 0, len = 0;
//        std::vector<std::uint32_t> arr_sort;
//    };
//    std::vector<std::uint32_t> elements;
//    std::vector<Segment> segments;
//
//    explicit SqrtDec(const std::vector<std::uint32_t> &start_elements)
//            : elements(start_elements),
//              segments(static_cast<std::uint32_t>(std::sqrt(static_cast<double>(start_elements.size())))) {
//        std::uint32_t k = std::ceil(static_cast<double>(elements.size()) / static_cast<double>(segments.size()));
//        for (std::uint32_t i = 0; i < k; i += k) {
//            segments[i].l = i;
//            segments[i].r = std::min<std::uint32_t>(i + k - 1, elements.size() - 1);
//            segments[i].len = segments[i].r - segments[i].l + 1;
//            segments[i].arr_sort.resize(segments[i].len);
//            std::copy(std::next(start_elements.begin(), i), std::next(start_elements.begin(), i + k),
//                      segments[i].arr_sort.begin());
//            std::sort(segments[i].arr_sort.begin(), segments[i].arr_sort.end());
//        }
//    }
//
//    [[nodiscard]] std::uint32_t count_less_x(std::uint32_t l, std::uint32_t r, std::uint32_t x) const {
//        std::uint32_t res = 0;
//        for (const auto &segment: segments) {
//            if (segment.l >= l && segment.r <= r) {
//                std::uint32_t t_l = std::max(l, segment.l), t_r = std::min(r, segment.r);
//                if (t_l == segment.l && t_r == segment.r) {
//                    auto it = std::lower_bound(segment.arr_sort.begin(), segment.arr_sort.end(), x);
//                    res += std::distance(segment.arr_sort.begin(), it);
//                } else {
//                    for (std::uint32_t i = t_l; i <= t_r; ++i) if (elements[i] < x) ++res;
//                }
//            }
//        }
//        return res;
//    }
//};
//
int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::uint32_t>> lines(n, std::vector<std::uint32_t>(m, 0)),
            columns(m, std::vector<std::uint32_t>(n, 0));
    for (auto &&line: lines) for (auto &&a: line) std::cin >> a;
    for (std::uint32_t i = 0; i < n; ++i) for (std::uint32_t j = 0; j < m; ++j) columns[j][i] = lines[i][j];
    auto non_sorted_lines = lines;
    for (auto &&line: lines) std::sort(line.begin(), line.end());
    for (auto &&column: columns) std::sort(column.begin(), column.end());
    std::uint32_t q;
    std::cin >> q;
    for (std::uint32_t _q = 0, i, j, k; _q < q; ++_q) {
        std::cin >> i >> j >> k;
        --i;
        --j;
        if (non_sorted_lines[i][j] >= k) std::cout << "0\n";
        else {
            std::uint32_t res = 0;
            auto it1 = std::upper_bound(columns[j].begin(), columns[j].end(), k - non_sorted_lines[i][j]);
            res += std::distance(columns[j].begin(), it1);
            if (non_sorted_lines[i][j] <= k - non_sorted_lines[i][j]) --res;
            auto it2 = std::upper_bound(lines[i].begin(), lines[i].end(), k - non_sorted_lines[i][j]);
            res += std::distance(lines[i].begin(), it2);
            if (non_sorted_lines[i][j] <= k - non_sorted_lines[i][j]) --res;
            std::cout << res << "\n";
        }
    }
    return 0;
}
