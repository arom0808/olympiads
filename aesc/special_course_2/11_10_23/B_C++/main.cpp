#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>

class SegmentTree {
private:
    struct Node {
        std::uint64_t max;
        std::pair<bool, std::uint64_t> set_mod = {false, 0};
    };

    std::vector<Node> nodes;
    std::uint64_t _size;

    void abstract_init_node(std::uint64_t node_id, std::uint64_t left, std::uint64_t right,
                            const std::function<std::uint64_t(std::uint64_t)> &func) {
        if (left >= right) nodes[node_id].max = 0;
        else if (left + 1 == right) nodes[node_id].max = func(left);
        else {
            abstract_init_node(node_id * 2, left, (left + right) / 2, func);
            abstract_init_node(node_id * 2 + 1, (left + right) / 2, right, func);
            nodes[node_id].max = std::max(nodes[node_id * 2].max, nodes[node_id * 2 + 1].max);
        }
    }

    void modify_transfer(std::uint64_t node_id, std::uint64_t node_left, std::uint64_t node_right) {
        if (node_left >= node_right) return;
        if (node_left + 1 != node_right) {
            if (nodes[node_id].set_mod.first) {
                nodes[node_id * 2].max = nodes[node_id].set_mod.second;
                nodes[node_id * 2].set_mod = nodes[node_id].set_mod;
                nodes[node_id * 2 + 1].max = nodes[node_id].set_mod.second;
                nodes[node_id * 2 + 1].set_mod = nodes[node_id].set_mod;
                nodes[node_id].set_mod.first = false;
            }
        }
    }

    void _set(std::uint64_t node_id, std::uint64_t node_left, std::uint64_t node_right, std::uint64_t req_left,
              std::uint64_t req_right, std::uint64_t val) {
        if (node_left >= node_right) return;
        if (req_right <= node_left || req_left >= node_right) return;
        modify_transfer(node_id, node_left, node_right);
        if (req_left <= node_left && req_right >= node_right) {
            nodes[node_id].max = val;
            nodes[node_id].set_mod = {true, val};
            return;
        }
        _set(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right, val);
        _set(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right, val);
        nodes[node_id].max = std::max(nodes[node_id * 2].max, nodes[node_id * 2 + 1].max);
    }

    std::uint64_t
    _max(std::uint64_t node_id, std::uint64_t node_left, std::uint64_t node_right, std::uint64_t req_left,
         std::uint64_t req_right) {
        if (node_left >= node_right) return 0;
        modify_transfer(node_id, node_left, node_right);
        if (req_right <= node_left || req_left >= node_right) return 0;
        if (req_left <= node_left && req_right >= node_right) return nodes[node_id].max;
        return std::max(_max(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right),
                        _max(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right));
    }


public:
    explicit SegmentTree(const std::vector<std::uint64_t> &arr) : nodes(arr.size() * 4), _size(arr.size()) {
        abstract_init_node(1, 0, _size, [&arr](std::uint64_t i) { return arr[i]; });
    }

    explicit SegmentTree(std::uint64_t n, std::uint64_t val) : nodes(n * 4), _size(n) {
        abstract_init_node(1, 0, _size, [val](std::uint64_t i) { return val; });
    }

    void set(std::uint64_t left, std::uint64_t right, std::uint64_t val) {
        _set(1, 0, _size, left, right, val);
    }

    std::uint64_t max(std::uint64_t left, std::uint64_t right) {
        return _max(1, 0, _size, left, right);
    }

    [[nodiscard]] std::uint64_t size() const { return _size; }
};


int main() {
    std::uint64_t n;
    std::cin >> n;
    std::vector<std::uint64_t> cakes(n);
    for (std::uint64_t i = 0, r, h; i < n; ++i) {
        std::cin >> r >> h;
        cakes[i] = r * r * h;
    }
    std::vector<std::uint64_t> d_z_c(cakes);
    std::sort(d_z_c.begin(), d_z_c.end());
    for (auto &&cake: cakes)
        cake = std::distance(d_z_c.begin(), std::lower_bound(d_z_c.begin(), d_z_c.end(), cake));
    SegmentTree dp(n, 0);
    for (std::uint64_t i = 0; i < dp.size(); ++i)
        dp.set(cakes[i], cakes[i] + 1, dp.max(0, cakes[i]) + d_z_c[cakes[i]]);
    std::cout << std::fixed << std::setprecision(10)
              << static_cast<long double>(dp.max(0, dp.size())) * static_cast<long double>(3.14159265358979643846);
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
//            for (std::uint32_t i = 0; i < req_cnt; ++i) {
//                std::uint32_t l = rand_num(0, len - 1), r = rand_num(l, len - 1);
//                auto action = rand_num(0, 2);
//                if (action == 0) {
//                    std::cout << "m " << l + 1 << " " << r + 1 << "\n";
//                    res1.push_back(st.max(l, r));
//                    res2.push_back(rst.max(l, r));
//                } else if (action == 1) {
//                    std::uint32_t add = rand_num(0, 4);
//                    std::cout << "a " << l + 1 << " " << r + 1 << " " << add << "\n";
//                    st.add(l, r, add);
//                    rst.add(l, r, add);
//                } else {
//                    std::uint32_t set = rand_num(0, 4);
//                    std::cout << "s " << l + 1 << " " << r + 1 << " " << set << "\n";
//                    st.set(l, r, set);
//                    rst.set(l, r, set);
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

//void _add(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
//          std::uint32_t req_right, std::uint32_t val) {
//    if (node_left >= node_right) return;
//    if (req_right <= node_left || req_left >= node_right) return;
//    modify_transfer(node_id, node_left, node_right);
//    if (req_left <= node_left && req_right >= node_right) {
//        nodes[node_id].max += val;
//        nodes[node_id].add_mod += val;
//        return;
//    }
//    _add(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right, val);
//    _add(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right, val);
//    nodes[node_id].max = std::max(nodes[node_id * 2].max, nodes[node_id * 2 + 1].max);
//}

//void add(std::uint32_t left, std::uint32_t right, std::uint32_t val) {
//    _add(1, 0, _size, left, right, val);
//}