#include <iostream>
#include <vector>
#include <algorithm>

class SegmentTree {
private:
    struct Node {
        std::uint32_t sum = 0;
    };

    std::vector<Node> nodes;
    std::uint32_t size;

    void
    init_node(std::uint32_t node_id, std::uint32_t left, std::uint32_t right, const std::vector<std::uint32_t> &arr) {
        if (left >= right) nodes[node_id].sum = 0;
        else if (left + 1 == right) nodes[node_id].sum = arr[left];
        else {
            init_node(node_id * 2, left, (left + right) / 2, arr);
            init_node(node_id * 2 + 1, (left + right) / 2, right, arr);
            nodes[node_id].sum = nodes[node_id * 2].sum + nodes[node_id * 2 + 1].sum;
        }
    }

    void _set(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
              std::uint32_t req_right, std::uint32_t val) {
        if (node_left >= node_right) return;
        if (req_right <= node_left || req_left >= node_right) return;
        if (req_left <= node_left && req_right >= node_right) {
            nodes[node_id].sum = val;
            return;
        }
        _set(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right, val);
        _set(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right, val);
        nodes[node_id].sum = nodes[node_id * 2].sum + nodes[node_id * 2 + 1].sum;
    }

    std::uint32_t _sum(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
                       std::uint32_t req_right) {
        if (node_left >= node_right) return 0;
        if (req_right <= node_left || req_left >= node_right) return 0;
        if (req_left <= node_left && req_right >= node_right) return nodes[node_id].sum;
        return _sum(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right) +
               _sum(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right);
    }


public:
    explicit SegmentTree(const std::vector<std::uint32_t> &arr) : nodes(arr.size() * 4), size(arr.size()) {
        init_node(1, 0, arr.size(), arr);
    }

    void set(std::uint32_t left, std::uint32_t right, std::uint32_t val) {
        _set(1, 0, size, left, right + 1, val);
    }

    std::uint32_t sum(std::uint32_t left, std::uint32_t right) {
        return _sum(1, 0, size, left, right + 1);
    }
};

struct Req {
    std::uint32_t l = 0, r = 0, i = 0, res = 0;
};

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> nums(n);
    for (auto &&num: nums) std::cin >> num;
    std::vector<std::uint32_t> d_z_c(nums);
    std::sort(d_z_c.begin(), d_z_c.end());
    for (auto &&num: nums) num = std::distance(d_z_c.begin(), std::lower_bound(d_z_c.begin(), d_z_c.end(), num));
    std::uint32_t q;
    std::cin >> q;
    std::vector<Req> reqs(q);
    for (std::uint32_t i = 0; i < q; ++i) {
        std::cin >> reqs[i].l >> reqs[i].r;
        --reqs[i].l;
        --reqs[i].r;
        reqs[i].i = i;
    }
    std::sort(reqs.begin(), reqs.end(), [](const Req &a, const Req &b) { return a.r < b.r; });
    SegmentTree st(nums);
    auto now_req = reqs.begin();
    std::vector<std::uint32_t> last_pos(n, n);
    for (std::uint32_t i = 0; i < n; ++i) {
        if (last_pos[nums[i]] != n) st.set(last_pos[nums[i]], last_pos[nums[i]], 0);
        st.set(i, i, 1);
        last_pos[nums[i]] = i;
        for (; now_req != reqs.end() && now_req->r == i; ++now_req)
            now_req->res = st.sum(now_req->l, now_req->r);
    }
    std::sort(reqs.begin(), reqs.end(), [](const Req &a, const Req &b) { return a.i < b.i; });
    for (const auto &req: reqs) std::cout << req.res << "\n";
    return 0;
}


//class RST {
//    std::vector<std::uint32_t> nums;
//
//
//public:
//    explicit RST(std::vector<std::uint32_t> arr) : nums(std::move(arr)) {}
//
//    void set(std::uint32_t left, std::uint32_t right, std::uint32_t val) {
//        for (std::uint32_t i = left; i < right; ++i) nums[i] = val;
//    }
//
//    std::uint32_t sum(std::uint32_t left, std::uint32_t right) {
//        std::uint32_t _sum = 0;
//        for (std::uint32_t i = left; i < right; ++i) _sum += nums[i];
//        return _sum;
//    }
//};