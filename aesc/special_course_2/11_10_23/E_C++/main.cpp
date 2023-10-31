#include <iostream>
#include <vector>


class SegmentTree {
private:
    struct Node {
        std::int64_t max_sub_seg_sum = 0, sum = 0, max_pref_sum = 0, max_suf_sum = 0;
    };

    std::vector<Node> nodes;
    std::uint32_t size;

    void leaf_node_upd(std::uint32_t node_id, std::int64_t val) {
        nodes[node_id].sum = val;
        nodes[node_id].max_sub_seg_sum = (val < 0 ? 0 : val);
        nodes[node_id].max_pref_sum = (val < 0 ? 0 : val);
        nodes[node_id].max_suf_sum = (val < 0 ? 0 : val);
    }

    void parent_node_upd(std::uint32_t node_id) {
        nodes[node_id].sum = nodes[node_id * 2].sum + nodes[node_id * 2 + 1].sum;
        nodes[node_id].max_sub_seg_sum =
                std::max(std::max(nodes[node_id * 2].max_sub_seg_sum, nodes[node_id * 2 + 1].max_sub_seg_sum),
                         nodes[node_id * 2].max_suf_sum + nodes[node_id * 2 + 1].max_pref_sum);
        nodes[node_id].max_pref_sum = std::max(nodes[node_id * 2].max_pref_sum,
                                               nodes[node_id * 2].sum + nodes[node_id * 2 + 1].max_pref_sum);
        nodes[node_id].max_suf_sum = std::max(nodes[node_id * 2 + 1].max_suf_sum,
                                              nodes[node_id * 2 + 1].sum + nodes[node_id * 2].max_suf_sum);
    }

    void
    init_node(std::uint32_t node_id, std::uint32_t left, std::uint32_t right, const std::vector<std::int64_t> &arr) {
        if (left >= right) nodes[node_id].sum = 0;
        else if (left + 1 == right) {
            leaf_node_upd(node_id, arr[left]);
        } else {
            init_node(node_id * 2, left, (left + right) / 2, arr);
            init_node(node_id * 2 + 1, (left + right) / 2, right, arr);
            parent_node_upd(node_id);
        }
    }

    void _set(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
              std::uint32_t req_right, std::int64_t val) {
        if (node_left >= node_right) return;
        if (req_right <= node_left || req_left >= node_right) return;
        if (req_left <= node_left && req_right >= node_right) {
            leaf_node_upd(node_id, val);
            return;
        }
        _set(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right, val);
        _set(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right, val);
        parent_node_upd(node_id);
    }

//    std::int64_t _max_suf_sum(std::uint32_t node_id,)

    std::int64_t
    _max_suf_sum(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left) {
        if (node_left >= node_right) return 0;
        if (req_left >= node_right) return 0;
        if (req_left <= node_left) return nodes[node_id].max_suf_sum;
        std::int64_t r1 = _max_suf_sum(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left), r2 = 0;
        if (req_left < (node_left + node_right) / 2)
            r2 = nodes[node_id * 2 + 1].sum +
                 _max_suf_sum(node_id * 2, node_left, (node_left + node_right) / 2, req_left);
        return std::max(r1, r2);
    }

    std::int64_t
    _max_pref_sum(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_right) {
        if (node_left >= node_right) return 0;
        if (req_right <= node_left) return 0;
        if (req_right >= node_right) return nodes[node_id].max_pref_sum;
        std::int64_t r1 = _max_pref_sum(node_id * 2, node_left, (node_left + node_right) / 2, req_right), r2 = 0;
        if (req_right > (node_left + node_right) / 2)
            r2 = nodes[node_id * 2].sum +
                 _max_pref_sum(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_right);
        return std::max(r1, r2);
    }

    std::int64_t
    _max_sub_seg_sum(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
                     std::uint32_t req_right) {
        if (node_left >= node_right) return 0;
        if (req_right <= node_left || req_left >= node_right) return 0;
        if (req_left <= node_left && req_right >= node_right) return nodes[node_id].max_sub_seg_sum;
        if (req_right <= (node_left + node_right) / 2)
            return _max_sub_seg_sum(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right);
        if (req_left >= (node_left + node_right) / 2)
            return _max_sub_seg_sum(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right);
        auto r1 = _max_sub_seg_sum(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right);
        auto r2 = _max_sub_seg_sum(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right);
        auto r3 = _max_suf_sum(node_id * 2, node_left, (node_left + node_right) / 2, req_left);
        auto r4 = _max_pref_sum(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_right);
        return std::max(std::max(r1, r2), r3 + r4);
    }


public:
    explicit SegmentTree(const std::vector<std::int64_t> &arr) : nodes(arr.size() * 4), size(arr.size()) {
        init_node(1, 0, arr.size(), arr);
    }

    void set(std::uint32_t left, std::uint32_t right, std::int64_t val) {
        _set(1, 0, size, left, right + 1, val);
    }

    std::int64_t max_sub_seg_sum(std::uint32_t left, std::uint32_t right) {
        return _max_sub_seg_sum(1, 0, size, left, right + 1);
    }
};


int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::int64_t> nums(n);
    for (auto &&num: nums) std::cin >> num;
    SegmentTree st(nums);
    std::string temp;
    for (std::int64_t i = 0, l, r, ps, val; i < m; ++i) {
        std::cin >> temp;
        if (temp == "get") {
            std::cin >> l >> r;
            std::cout << st.max_sub_seg_sum(l - 1, r - 1) << "\n";
        } else {
            std::cin >> ps >> val;
            st.set(ps - 1, ps - 1, val);
        }
    }
    return 0;
}

//namespace Dev {
//    class RST {
//        std::vector<std::int64_t> nums;
//    public:
//        explicit RST(std::vector<std::int64_t> arr) : nums(std::move(arr)) {}
//
//        void set(std::uint32_t left, std::uint32_t right, std::int64_t val) {
//            for (std::uint32_t i = left; i <= right; ++i) nums[i] = val;
//        }
//
//        std::int64_t max_sub_seg_sum(std::uint32_t left, std::uint32_t right) {
//            std::int64_t max_sum = 0;
//            for (std::uint32_t i = left; i <= right; ++i) {
//                for (std::uint32_t j = i; j <= right; ++j) {
//                    std::int64_t now_sum = 0;
//                    for (std::uint32_t k = i; k <= j; ++k) now_sum += nums[k];
//                    max_sum = std::max(max_sum, now_sum);
//                }
//            }
//            return max_sum;
//        }
//    };
//
//    std::random_device dev;
//    std::mt19937 rng(dev());
//
//    std::int64_t randint(std::int64_t a, std::int64_t b) { return std::uniform_int_distribution(a, b)(rng); }
//
//    void Test1() {
//        while (true) {
//            std::uint32_t n = randint(2, 10), m = randint(2, 10);
//            std::cout << n << " " << m << "\n";
//            std::vector<std::int64_t> nums(n);
//            for (auto &&num: nums) num = randint(-10, 10);
//            for (const auto &num: nums) std::cout << num << " ";
//            std::cout << "\n";
//            RST rst(nums);
//            SegmentTree st(nums);
//            std::vector<std::int64_t> res1, res2;
//            for (std::uint32_t i = 0; i < m; ++i) {
//                if (randint(0, 1)) {
//                    std::int64_t l = randint(0, n - 1), r = randint(l, n - 1);
//                    std::cout << "get " << l + 1 << " " << r + 1 << "\n";
//                    res1.push_back(st.max_sub_seg_sum(l, r));
//                    res2.push_back(rst.max_sub_seg_sum(l, r));
//                } else {
//                    std::int64_t ps = randint(0, n - 1), val = randint(-5, 5);
//                    std::cout << "change " << ps + 1 << " " << val << "\n";
//                    st.set(ps, ps, val);
//                    rst.set(ps, ps, val);
//                }
//            }
//            std::cout << "My res:\n";
//            for (const auto &res: res1) std::cout << res << "\n";
//            std::cout << "Right res:\n";
//            for (const auto &res: res2) std::cout << res << "\n";
//            if (res1 != res2) return;
//        }
//    }
//
//    void Test2() {
//        std::uint32_t n, m;
//        std::cin >> n >> m;
//        std::vector<std::int64_t> nums(n);
//        for (auto &&num: nums) std::cin >> num;
//        SegmentTree st(nums);
//        RST rst(nums);
//        std::string temp;
//        std::vector<std::int64_t> res1, res2;
//        for (std::int64_t i = 0, l, r, ps, val; i < m; ++i) {
//            std::cin >> temp;
//            if (temp == "get") {
//                std::cin >> l >> r;
//                res1.push_back(st.max_sub_seg_sum(l - 1, r - 1));
//                res2.push_back(rst.max_sub_seg_sum(l - 1, r - 1));
//            } else {
//                std::cin >> ps >> val;
//                st.set(ps - 1, ps - 1, val);
//                rst.set(ps - 1, ps - 1, val);
//            }
//        }
//    }
//}