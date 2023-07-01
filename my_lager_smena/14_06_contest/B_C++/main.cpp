#include <iostream>
#include <vector>

class SegmentsTree {
public:
    std::vector<std::uint32_t> nodes;
    std::uint32_t n;

    explicit SegmentsTree(const std::string &nums) : nodes(nums.size() * 4), n(nums.size()) {
        build(nums, 1, 0, n - 1);
    }

    std::uint32_t get_sum(std::uint32_t l, std::uint32_t r) {
        return in_get_sum(1, 0, n - 1, l, r);
    }

private:

    std::uint32_t in_get_sum(std::uint32_t v, std::uint32_t tl, std::uint32_t tr, std::uint32_t l, std::uint32_t r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return nodes[v];
        std::uint32_t tm = (tl + tr) / 2;
        return in_get_sum(v * 2, tl, tm, l, std::min(r, tm))
               + in_get_sum(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);
    }


    void build(const std::string &nums, std::uint32_t v, std::uint32_t tl, std::uint32_t tr) {
        if (tl == tr) nodes[v] = (nums[tl] == '1');
        else {
            std::uint32_t tm = (tl + tr) / 2;
            build(nums, v * 2, tl, tm);
            build(nums, v * 2 + 1, tm + 1, tr);
            nodes[v] = nodes[v * 2] + nodes[v * 2 + 1];
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::uint32_t n;
    std::cin >> n;
    std::string notebooks;
    notebooks.reserve(n);
    std::cin >> notebooks;
    SegmentsTree seg_tree(notebooks);
    std::uint32_t m, a, b;
    std::cin >> m >> a >> b;
    std::uint32_t res = 0;
    std::vector<bool> is_el_ok(n / (a + b) + 1, false);
    for (std::uint32_t absolute_start_pos = 0; absolute_start_pos < a + b; ++absolute_start_pos) {
        std::fill(is_el_ok.begin(), is_el_ok.end(), false);
        std::uint32_t max_i = 0;
        for (std::uint32_t start_for_m = absolute_start_pos;
             start_for_m <= n - a - b; start_for_m += a + b, ++max_i) {
            is_el_ok[max_i] = seg_tree.get_sum(start_for_m, start_for_m + a - 1) == a;
        }
        std::uint32_t last_false = 1e9;
        for (std::uint32_t i = 0; i < m; ++i) if (!is_el_ok[i]) last_false = i;
        for (std::uint32_t now_first = 0, now_last = m - 1; now_last < max_i; ++now_first, ++now_last) {
            if (last_false == 1e9 || last_false < now_first) ++res;
            if (!is_el_ok[now_last + 1]) last_false = now_last + 1;
        }
    }

//    for (std::uint32_t start_pos = 0; start_pos <= n - m * (a + b); ++start_pos) {
//        bool is_ok = true;
//        for (std::uint32_t check_start = start_pos, check_last = check_start + a - 1;
//             check_start < start_pos + m * (a + b) && is_ok;
//             check_start += a + b, check_last = check_start + a - 1) {
//            if (seg_tree.get_sum(check_start, check_last) != a) is_ok = false;
//        }
//        if (is_ok) ++res;
//    }
    std::cout << res;
    return 0;
}
