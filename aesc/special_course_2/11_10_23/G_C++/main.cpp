#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>

template<typename T>
class SegmentTree {
private:
    struct Node {
        T sum = 0, modify = 0;
    };

    std::vector<Node> nodes;
    std::uint32_t size;

    void
    abstract_init_node(std::uint32_t node_id, std::uint32_t left, std::uint32_t right,
                       const std::function<T(std::uint32_t)> &f) {
        if (left >= right) nodes[node_id].sum = 0;
        else if (left + 1 == right) nodes[node_id].sum = f(left);
        else {
            abstract_init_node(node_id * 2, left, (left + right) / 2, f);
            abstract_init_node(node_id * 2 + 1, (left + right) / 2, right, f);
            nodes[node_id].sum = nodes[node_id * 2].sum + nodes[node_id * 2 + 1].sum;
        }
    }

    void modify_transfer(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right) {
        if (node_left >= node_right) return;
        if (node_left + 1 != node_right) {
            nodes[node_id * 2].sum += nodes[node_id].modify * ((node_left + node_right) / 2 - node_left);
            nodes[node_id * 2].modify += nodes[node_id].modify;
            nodes[node_id * 2 + 1].sum += nodes[node_id].modify * (node_right - (node_left + node_right) / 2);
            nodes[node_id * 2 + 1].modify += nodes[node_id].modify;
        }
        nodes[node_id].modify = 0;
    }

    void _add(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
              std::uint32_t req_right, T val) {
        if (node_left >= node_right || req_right <= node_left || req_left >= node_right) return;
        if (req_left <= node_left && req_right >= node_right) {
            nodes[node_id].sum += val * (node_right - node_left);
            nodes[node_id].modify += val;
        } else {
            modify_transfer(node_id, node_left, node_right);
            _add(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right, val);
            _add(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right, val);
            nodes[node_id].sum = nodes[node_id * 2].sum + nodes[node_id * 2 + 1].sum;
        }
    }


    T _sum(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
           std::uint32_t req_right) {
        if (node_left >= node_right || req_right <= node_left || req_left >= node_right) return 0;
        modify_transfer(node_id, node_left, node_right);
        if (req_left <= node_left && req_right >= node_right) return nodes[node_id].sum;
        return _sum(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right) +
               _sum(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right);
    }


public:
    explicit SegmentTree(const std::vector<T> &arr) : nodes(arr.size() * 4), size(arr.size()) {
        abstract_init_node(1, 0, arr.size(), [&arr](std::uint32_t i) { return arr[i]; });
    }

    explicit SegmentTree(std::uint32_t n, T val) : nodes(n * 4), size(n) {
        abstract_init_node(1, 0, n, [val](std::uint32_t i) { return val; });
    }

    void add(std::uint32_t left, std::uint32_t right, T val) {
        _add(1, 0, size, left, right, val);
    }

    T sum(std::uint32_t left, std::uint32_t right) {
        return _sum(1, 0, size, left, right);
    }
};


int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> powers(n);
    for (auto &&p: powers) std::cin >> p;
    auto dzc = powers;
    std::sort(dzc.begin(), dzc.end());
    for (auto &&p: powers) p = std::distance(dzc.begin(), std::lower_bound(dzc.begin(), dzc.end(), p));
    SegmentTree<std::uint64_t> cnt1(powers.size(), 0), cnt2(powers.size(), 0);
    std::vector<std::uint64_t> res(powers.size(), 0);
    for (std::int32_t i = n - 1; i >= 0; --i) {
        cnt1.add(powers[i], powers[i] + 1, 1);
        cnt2.add(powers[i], powers[i] + 1, cnt1.sum(0, powers[i]));
        res[i] = cnt2.sum(0, powers[i]);
    }
    std::cout << std::accumulate(res.begin(), res.end(), 0ull);
    return 0;
}
