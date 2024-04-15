#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <random>

using namespace std;

namespace Sanya {
    long long cnt = 0;

    long long log2(long long n) {
        long long i = 1;
        while ((1 << i) < n) i++;
        return i;
    }

    bool comp(pair<unsigned long long, int> a, pair<unsigned long long, int> b) {
        if (a.first == b.first) return a.second > b.second;
        return a.first < b.first;
    }


    vector<unsigned long long> tree;
//vector<long long> treeprom;

    long long parent(long long i) {
        return (i - 1) / 2;
    }

    long long prav(long long i) {
        return i * 2 + 2;
    }

    long long lev(long long i) {
        return 2 * i + 1;
    }

/*void push(long long i) {
    tree[i] += treeprom[i];
    treeprom[prav(i)] += treeprom[i];
    treeprom[lev(i)] += treeprom[i];
    treeprom[i] = 0;
}*/

    void update(long long l, long long r, unsigned long long j, long long bl, long long br, long long i) {
        if (l >= bl and r <= br) {
            tree[i] = j;
            return;
        } else if (r < bl or l > br) {
            return;
        }
        update(l, (l + r) / 2, j, bl, br, lev(i));
        update((l + r) / 2 + 1, r, j, bl, br, prav(i));
        tree[i] = max(tree[lev(i)], tree[prav(i)]);
    }

    unsigned long long query(long long l, long long r, long long bl, long long br, long long i) {
        if (l >= bl and r <= br) {
            return tree[i];
        } else if (r < bl or l > br) {
            return 0;
        }
        return max(query(l, (r + l) / 2, bl, br, lev(i)), query((l + r) / 2 + 1, r, bl, br, prav(i)));
    }

    uint64_t solve(const vector<uint64_t> &vvs) {
        vector<pair<unsigned long long, int>> t;
        uint64_t n = vvs.size();
        for (int i = 0; i < vvs.size(); ++i) {
            t.push_back({vvs[i], i});
        }
        sort(t.rbegin(), t.rend(), comp);
        long long nn = n;
        n = (1 << (log2(n)));
        vector<unsigned long long> k(2 * n - 1, 0);
        tree = k;
        for (int i = 0; i < nn; ++i) {
            if (i > 0) {
                if (t[i].first == t[i - 1].first) {
                    continue;
                }
            }
            unsigned long long hhh = query(0, n - 1, t[i].second, n - 1, 0);
            update(0, n - 1, hhh + t[i].first, t[i].second, t[i].second, 0);
        }
        return query(0, n - 1, 0, n - 1, 0);
    }
}

namespace Rumchik {

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

    uint64_t solve(const vector<uint64_t> &vvs) {
        uint64_t n = vvs.size();
        vector<std::uint64_t> cakes(n);
        for (uint64_t i = 0, r, h; i < n; ++i) {
            cakes[i] = vvs[i];
        }
        std::vector<std::uint64_t> d_z_c(cakes);
        std::sort(d_z_c.begin(), d_z_c.end());
        for (auto &&cake: cakes)
            cake = std::distance(d_z_c.begin(), std::lower_bound(d_z_c.begin(), d_z_c.end(), cake));
        SegmentTree dp(n, 0);
        for (std::uint64_t i = 0; i < dp.size(); ++i)
            dp.set(cakes[i], cakes[i] + 1, dp.max(0, cakes[i]) + d_z_c[cakes[i]]);
        return dp.max(0, dp.size());
    }
}

namespace Test {
    random_device dev;
    mt19937 rng(dev());

    uint32_t rand_num(uint32_t min, uint32_t max) {
        return uniform_int_distribution(min, max)(rng);
    }

    vector<uint64_t> gen() {
        uint32_t n = rand_num(1, 3);
        vector<uint64_t> cakes(n);
        for (auto &cake: cakes) cake = rand_num(1, 5);
        return cakes;
    }

    void Test() {
        while (true) {
            auto cakes = gen();
            auto rSanya = Sanya::solve(cakes), rRumchik = Rumchik::solve(cakes);
            if (rSanya != rRumchik) {
                cout << cakes.size() << "\n";
                for (auto cake: cakes) cout << "1 " << cake << "\n";
                cout << "\n\n Sanya ans: " << rSanya << "\n Rumchik ans: " << rRumchik << "\n";
                break;
            }
        }
    }
}

int main() {
    Test::Test();
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