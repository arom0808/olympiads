#include <iostream>
#include <vector>

class SegmentTree {
private:
    struct Node {
        std::uint32_t max, modify = 0;
    };

    std::vector<Node> nodes;
    std::uint32_t size;

    void
    init_node(std::uint32_t node_id, std::uint32_t left, std::uint32_t right, const std::vector<std::uint32_t> &arr) {
        if (left >= right) nodes[node_id].max = 0;
        else if (left + 1 == right) nodes[node_id].max = arr[left];
        else {
            init_node(node_id * 2, left, (left + right) / 2, arr);
            init_node(node_id * 2 + 1, (left + right) / 2, right, arr);
            nodes[node_id].max = std::max(nodes[node_id * 2].max, nodes[node_id * 2 + 1].max);
        }
    }

    void modify_transfer(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right) {
        if (node_left >= node_right) return;
        if (node_left + 1 != node_right) {
            nodes[node_id * 2].max += nodes[node_id].modify;
            nodes[node_id * 2].modify += nodes[node_id].modify;
            nodes[node_id * 2 + 1].max += nodes[node_id].modify;
            nodes[node_id * 2 + 1].modify += nodes[node_id].modify;
        }
        nodes[node_id].modify = 0;
    }

    void _add(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
              std::uint32_t req_right, std::uint32_t val) {
        if (node_left >= node_right) return;
        if (req_right <= node_left || req_left >= node_right) return;
        if (req_left <= node_left && req_right >= node_right) {
            nodes[node_id].max += val;
            nodes[node_id].modify += val;
            return;
        }
        modify_transfer(node_id, node_left, node_right);
        _add(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right, val);
        _add(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right, val);
        nodes[node_id].max = std::max(nodes[node_id * 2].max, nodes[node_id * 2 + 1].max);
    }


    std::uint32_t _max(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
                       std::uint32_t req_right) {
        if (node_left >= node_right) return 0;
        modify_transfer(node_id, node_left, node_right);
        if (req_right <= node_left || req_left >= node_right) return 0;
        if (req_left <= node_left && req_right >= node_right) return nodes[node_id].max;
        return std::max(_max(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right),
                        _max(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right));
    }


public:
    explicit SegmentTree(const std::vector<std::uint32_t> &arr) : nodes(arr.size() * 4), size(arr.size()) {
        init_node(1, 0, arr.size(), arr);
    }

    void add(std::uint32_t left, std::uint32_t right, std::uint32_t val) {
        _add(1, 0, size, left, right + 1, val);
    }

    std::uint32_t max(std::uint32_t left, std::uint32_t right) {
        return _max(1, 0, size, left, right + 1);
    }
};

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> arr(n);
    for (auto &&num: arr) std::cin >> num;
    SegmentTree seg_tree(arr);
    std::uint32_t m;
    std::cin >> m;
    char c;
    for (std::uint32_t i = 0, left, right, add; i < m; ++i) {
        std::cin >> c >> left >> right;
        if (c == 'm') std::cout << seg_tree.max(left - 1, right - 1) << "\n";
        else {
            std::cin >> add;
            seg_tree.add(left - 1, right - 1, add);
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
//        void add(std::uint32_t left, std::uint32_t right, std::uint32_t val) {
//            for (std::uint32_t i = left; i <= right; ++i) nums[i] += val;
//        }
//
//        std::uint32_t max(std::uint32_t left, std::uint32_t right) {
//            return *std::max_element(std::next(nums.begin(), left), std::next(nums.begin(), right + 1));
//        }
//    };
//
//    void Test1() {
//        while (true) {
//            auto len = rand_num(1, 100);
//            std::vector<std::uint32_t> nums(len), res1, res2;
//            for (auto &&num: nums) num = rand_num(0, 100);
//            std::cout << len << "\n";
//            for (const auto &num: nums) std::cout << num << " ";
//            SegmentTree st(nums);
//            RightSegTree rst(nums);
//            auto req_cnt = rand_num(1, 100);
//            std::cout << "\n" << req_cnt << "\n";
//            for (std::uint32_t i = 0; i < req_cnt; ++i) {
//                std::uint32_t l = rand_num(0, len - 1), r = rand_num(l, len - 1);
//                if (rand_num(0, 1)) {
//                    std::cout << "m " << l + 1 << " " << r + 1 << "\n";
//                    res1.push_back(st.max(l, r));
//                    res2.push_back(rst.max(l, r));
//                } else {
//                    std::uint32_t add = rand_num(0, 100);
//                    std::cout << "a " << l + 1 << " " << r + 1 << " " << add << "\n";
//                    st.add(l, r, add);
//                    rst.add(l, r, add);
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
//        for (std::uint32_t i = 0, left, right, add; i < m; ++i) {
//            std::cin >> c >> left >> right;
//            if (c == 'm') {
//                auto res1 = seg_tree.max(left - 1, right - 1), res2 = rst.max(left - 1, right - 1);
//                std::cout << res1 << " " << res2 << "\n";
//                if (res1 != res2) return;
//            } else {
//                std::cin >> add;
//                seg_tree.add(left - 1, right - 1, add);
//                rst.add(left - 1, right - 1, add);
//            }
//        }
//    }
//}
