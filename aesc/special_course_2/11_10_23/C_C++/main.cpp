#include <iostream>
#include <functional>
#include <vector>


class SegmentTree {
private:
    struct Node {
        std::uint32_t max;
    };

    std::vector<Node> nodes;
    std::uint32_t _size;

    void abstract_init_node(std::uint32_t node_id, std::uint32_t left, std::uint32_t right,
                            const std::function<std::uint32_t(std::uint32_t)> &func) {
        if (left >= right) nodes[node_id].max = 0;
        else if (left + 1 == right) nodes[node_id].max = func(left);
        else {
            abstract_init_node(node_id * 2, left, (left + right) / 2, func);
            abstract_init_node(node_id * 2 + 1, (left + right) / 2, right, func);
            nodes[node_id].max = std::max(nodes[node_id * 2].max, nodes[node_id * 2 + 1].max);
        }
    }

    void _set(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
              std::uint32_t req_right, std::uint32_t val) {
        if (node_left >= node_right) return;
        if (req_right <= node_left || req_left >= node_right) return;
        if (node_left + 1 == node_right) nodes[node_id].max = val;
        else {
            _set(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right, val);
            _set(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right, val);
            nodes[node_id].max = std::max(nodes[node_id * 2].max, nodes[node_id * 2 + 1].max);
        }
    }


    std::int32_t
    _min_pos_x(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
               std::uint32_t req_right, std::uint32_t x) {
        if (node_left >= node_right) return -1;
        if (req_right <= node_left || req_left >= node_right) return -1;
        if (nodes[node_id].max < x) return -1;
        if (node_left + 1 == node_right) return node_left;
        auto r1 = _min_pos_x(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right, x);
        if (r1 != -1) return r1;
        return _min_pos_x(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right, x);
    }


public:
    explicit SegmentTree(std::uint32_t n, std::istream &in_stream) : nodes(n * 4), _size(n) {
        abstract_init_node(1, 0, _size, [&in_stream](std::uint32_t i) {
            std::uint32_t temp;
            in_stream >> temp;
            return temp;
        });
    }

    void set(std::uint32_t left, std::uint32_t right, std::uint32_t val) {
        _set(1, 0, _size, left, right, val);
    }

    std::int32_t min_pos_x(std::uint32_t left, std::uint32_t right, std::uint32_t x) {
        return _min_pos_x(1, 0, _size, left, right, x);
    }

    [[nodiscard]] std::uint32_t size() const { return _size; }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::uint32_t n, m;
    std::cin >> n >> m;
    SegmentTree st(n, std::cin);
    for (std::uint32_t _ = 0, t, i, x; _ < m; ++_) {
        std::cin >> t >> i >> x;
        if (t == 0) st.set(i - 1, i, x);
        else {
            auto res = st.min_pos_x(i - 1, st.size(), x);
            std::cout << (res < 0 ? (-1) : res + 1) << "\n";
        }
    }
    return 0;
}



//namespace Dev {
//    std::random_device dev;
//    std::mt19937 rng(dev());
//
//    std::uint32_t rand_num(std::uint32_t min, std::uint32_t max) {
//        return std::uniform_int_distribution(min, max)(rng);
//    }
//
//    class RightSegTree {
//        std::vector<std::uint32_t> nums;
//
//    public:
//        explicit RightSegTree(std::vector<std::uint32_t> arr) : nums(std::move(arr)) {}
//
//        [[nodiscard]] std::uint32_t size() const { return nums.size(); }
//
//        void add(std::uint32_t left, std::uint32_t right, std::uint32_t val) {
//            for (std::uint32_t i = left; i < right; ++i) nums[i] += val;
//        }
//
//        std::uint32_t max(std::uint32_t left, std::uint32_t right) {
//            if (left == right) return 0;
//            return *std::max_element(std::next(nums.begin(), left), std::next(nums.begin(), right));
//        }
//
//        void set(std::uint32_t left, std::uint32_t right, std::uint32_t val) {
//            for (std::uint32_t i = left; i < right; ++i) nums[i] = val;
//        }
//
//        std::int32_t min_pos_x(std::uint32_t left, std::uint32_t right, std::uint32_t x) {
//            for (std::uint32_t i = left; i <= right; ++i) if (nums[i] >= x) return i;
//            return -1;
//        }
//    };
//
//    void Test1() {
//        while (true) {
//            auto len = rand_num(1, 4);
//            std::vector<std::uint32_t> nums(len), res1, res2;
//            for (auto &&num: nums) num = rand_num(0, 4);
//            std::cout << len << "\n";
//            for (const auto &num: nums) std::cout << num << " ";
//            SegmentTree st(nums);
//            RightSegTree rst(nums);
//            auto req_cnt = rand_num(1, 4);
//            std::cout << "\n" << req_cnt << "\n";
//            for (std::uint32_t _ = 0; _ < req_cnt; ++_) {
//                std::uint32_t i = rand_num(0, len - 1), x = rand_num(0, 4);
//                auto action = rand_num(0, 1);
//                std::cout << action << " " << i << " " << x << "\n";
//                if (action) {
//                    res1.push_back(st.min_pos_x())
//                }
//            }
//            std::cout << "\nMy res:\n";
//            for (const auto &res: res1) std::cout << res << "\n";
//            std::cout << "\nRight res:\n";
//            for (const auto &res: res2) std::cout << res << "\n";
//            if (res1 != res2) return;
//            std::cout << "\n-------------------------------------\n";
//        }
//    }
//
//    void Test2() {
//        std::uint32_t n;
//        std::cin >> n;
//        std::vector<std::uint32_t> arr(n);
//        for (auto &&num: arr) std::cin >> num;
//        SegmentTree seg_tree(arr);
//        RightSegTree rst(arr);
//        std::uint32_t m;
//        std::cin >> m;
//        char c;
//        for (std::uint32_t i = 0, left, right, add, set; i < m; ++i) {
//            std::cin >> c >> left >> right;
//            if (c == 'm') {
//                auto res1 = seg_tree.max(left - 1, right - 1), res2 = rst.max(left - 1, right - 1);
//                std::cout << res1 << " " << res2 << "\n";
//                if (res1 != res2) return;
//            } else if (c == 'a') {
//                std::cin >> add;
//                seg_tree.add(left - 1, right - 1, add);
//                rst.add(left - 1, right - 1, add);
//            } else {
//                std::cin >> set;
//                seg_tree.set(left - 1, right - 1, set);
//                rst.set(left - 1, right - 1, set);
//            }
//        }
//    }
//}